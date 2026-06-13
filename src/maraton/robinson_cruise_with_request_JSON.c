#include "robinson_cruise_with_request_JSON.h"
#include <string.h>
#include <math.h>
#include <stdlib.h>

// === Глобальные данные ===
char vertex_names[MAX_BODIES * 2][MAX_NAME_LEN];  // Все уникальные имена
int vertex_count = 0;

// Карта: имя -> индекс
int get_vertex_index(const char* name) {
    for (int i = 0; i < vertex_count; i++) {
        if (strcmp(vertex_names[i], name) == 0) return i;
    }
    if (vertex_count >= MAX_BODIES * 2 - 1) return -1;
    strcpy(vertex_names[vertex_count], name);
    return vertex_count++;
}

// === Структуры ===
typedef struct {
    double speed_out;
    int fuel_after;
    int time_added;
} ManeuverResult;

typedef struct {
    int planet;
    int fuel;
    double speed;
    int time_used;
    int prev;
} State;

typedef struct {
    int from_point, to;
    double distance;
} GraphEdge;

GraphEdge graph_edges[100];
int graph_count = 0;

// === Мин-куча ===

typedef struct {
    State state;
    int priority;
} HeapNode;

HeapNode heap[HEAP_SIZE];
int heap_size = 0;

void push_heap(State s) {
    if (heap_size >= HEAP_SIZE - 1) return;
    int i = heap_size++;
    heap[i].state = s;
    heap[i].priority = s.time_used;

    while (i > 0) {
        int parent = (i - 1) / 2;
        if (heap[parent].priority <= heap[i].priority) break;
        HeapNode tmp = heap[i]; heap[i] = heap[parent]; heap[parent] = tmp;
        i = parent;
    }
}

State pop_heap() {
    State result = heap[0].state;
    heap[0] = heap[--heap_size];

    int i = 0;
    while (1) {
        int left = 2*i+1, right = 2*i+2, smallest = i;
        if (left < heap_size && heap[left].priority < heap[smallest].priority) smallest = left;
        if (right < heap_size && heap[right].priority < heap[smallest].priority) smallest = right;
        if (smallest == i) break;
        HeapNode tmp = heap[i]; heap[i] = heap[smallest]; heap[smallest] = tmp;
        i = smallest;
    }
    return result;
}

int is_empty() { return heap_size == 0; }

// === dist[p][f][t] ===
int dist[MAX_BODIES * 2][MAX_FUEL][MAX_TIME];

// === Маппинг имени → индекс ===
int get_index(const char* name, const char names[][MAX_NAME_LEN], int n) {
    for (int i = 0; i < n; i++) {
        if (strcmp(name, names[i]) == 0) return i;
    }
    return -1;
}

// === Применить манёвр ===
ManeuverResult apply_maneuver_if_possible(int planet_idx, double speed_in, int fuel_before, Body bodies_in[], int n_bodies) {
    ManeuverResult best = {speed_in, fuel_before, 0};
    const char* name = vertex_names[planet_idx];

    // Ищем, есть ли такая точка в bodies
    for (int i = 0; i < n_bodies; i++) {
        if (strcmp(bodies_in[i].id, name) == 0) {
            for (int j = 0; j < bodies_in[i].num_assists; j++) {
                double gain = bodies_in[i].gravity_assists[j].velocity_gain;
                double fuel_cost = bodies_in[i].gravity_assists[j].fuel_consumption;
                int time_add = bodies_in[i].gravity_assists[j].time_to_execute;

                if (fuel_before >= fuel_cost) {
                    double new_speed = speed_in + gain;
                    int new_fuel = fuel_before - (int)ceil(fuel_cost);
                    if (new_speed > best.speed_out) {
                        best.speed_out = new_speed;
                        best.fuel_after = new_fuel;
                        best.time_added = time_add;
                    }
                }
            }
            return best;
        }
    }
    return best;  // нет манёвра
}


// === Моделирование перелёта ===
double simulate_leg(double distance, int *fuel_used, int fuel,
                    double mass_shuttle, double mass_fuel_unit,
                    double power_per_unit, double fuel_consumption_per_sec,
                    double initial_speed) {
    double dry_mass = mass_shuttle;
    double current_mass = dry_mass + fuel * mass_fuel_unit;
    double speed = initial_speed;
    double dist_traveled = 0.0;
    int time = 0;
    int initial_fuel = fuel;

    // Разгон
    while (fuel > 0 && dist_traveled < distance * 0.5) {
        double force = power_per_unit * fuel_consumption_per_sec / (speed + 1.0);
        double acc = force / current_mass;
        dist_traveled += speed + 0.5 * acc;
        speed += acc;
        current_mass -= mass_fuel_unit;
        time++;
        fuel--;
        if (current_mass <= dry_mass) break;
    }

    // Полёт по инерции
    double remaining = distance - dist_traveled;
    if (speed > 1e-6 && remaining > 0) {
        int coast_time = (int)(remaining / speed);
        time += coast_time;
        dist_traveled += speed * coast_time;
        remaining -= speed * coast_time;
    }

    // Торможение
    while (fuel > 0 && remaining > 1e-6 && speed > 1e-6) {
        double force = power_per_unit * fuel_consumption_per_sec / (speed + 1.0);
        double acc = force / current_mass;
        if (acc >= speed) { time++; fuel--; break; }
        dist_traveled += speed - 0.5 * acc;
        remaining -= (speed - 0.5 * acc);
        speed -= acc;
        current_mass -= mass_fuel_unit;
        time++;
        fuel--;
    }

    if (speed > 1e-6) return -1;
    *fuel_used = (initial_fuel - fuel);
    return time;
}

// === Основная функция ===
Solution solve_mission(
    Body bodies_in[],
    int n_bodies,
    Edge edges_in[],
    int n_edges,
    const char* start_point,
    const char* rescue_point,
    int oxygen_time,
    double mass_shuttle,
    double mass_fuel_unit,
    double power_per_unit,
    int total_fuel,
    double fuel_consumption_per_sec
) {
    printf("=== C: solve_mission called ===\n");
    printf("  n_bodies=%d, n_edges=%d\n", n_bodies, n_edges);
    printf("  start_point=%s, rescue_point=%s\n", start_point, rescue_point);
    printf("  oxygen_time=%d, mass_shuttle=%f, total_fuel=%d\n", oxygen_time, mass_shuttle, total_fuel);
    printf("  fuel_consumption_per_sec=%f\n", fuel_consumption_per_sec);
    
    // === Собираем все вершины ===
    vertex_count = 0;
    get_vertex_index(start_point);
    get_vertex_index(rescue_point);

    for (int i = 0; i < n_edges; i++) {
        get_vertex_index(edges_in[i].from_point);
        get_vertex_index(edges_in[i].to);
    }

    int start_idx = get_vertex_index(start_point);
    int rescue_idx = get_vertex_index(rescue_point);

    if (start_idx == -1 || rescue_idx == -1) {
        Solution sol = {0}; return sol;
    }

    // === Строим граф ===
    graph_count = 0;
    for (int i = 0; i < n_edges; i++) {
        int from = get_vertex_index(edges_in[i].from_point);
        int to = get_vertex_index(edges_in[i].to);
        if (from != -1 && to != -1) {
            graph_edges[graph_count].from_point = from;
            graph_edges[graph_count].to = to;
            graph_edges[graph_count].distance = edges_in[i].distance;
            graph_count++;
        }
    }

    // === Инициализация ===
    memset(dist, -1, sizeof(dist));
    heap_size = 0;

    State start_state = {start_idx, total_fuel, 0.0, 0, -1};
    push_heap(start_state);
    dist[start_idx][total_fuel][0] = 0;

    State states[100000];
    int state_count = 0;
    int parent[100000];
    memset(parent, -1, sizeof(parent));

    Solution solution = {0};

    while (!is_empty()) {
        State s = pop_heap();
        if (s.time_used != dist[s.planet][s.fuel][s.time_used]) continue;

        ManeuverResult mr = apply_maneuver_if_possible(s.planet, s.speed, s.fuel, bodies_in, n_bodies);
        State after = {s.planet, mr.fuel_after, mr.speed_out, s.time_used + mr.time_added, s.prev};

        if (s.planet == rescue_idx) {
            solution.success = 1;
            solution.time_used = after.time_used;
            solution.fuel_left = after.fuel;

            int path[MAX_PATH_LEN], len = 0;
            int cur = state_count - 1;
            while (cur != -1) {
                path[len++] = states[cur].planet;
                cur = parent[cur];
            }
            for (int i = 0; i < len; i++) {
                solution.path[i] = path[len - 1 - i];
            }
            solution.path_len = len;
            break;
        }

        if (after.time_used >= oxygen_time) continue;

        for (int i = 0; i < graph_count; i++) {
            GraphEdge* e = &graph_edges[i];
            if (e->from_point != s.planet) continue;

            int fuel_needed;
            double leg_time = simulate_leg(
                e->distance, &fuel_needed, after.fuel,
                mass_shuttle, mass_fuel_unit, power_per_unit, fuel_consumption_per_sec,
                after.speed
            );
            if (leg_time < 0) continue;

            int total_time = after.time_used + (int)leg_time;
            int fuel_after = after.fuel - fuel_needed;

            if (total_time >= oxygen_time) continue;
            if (fuel_after < 0 || total_time >= MAX_TIME) continue;

            State next = {e->to, fuel_after, 0.0, total_time, state_count - 1};

            if (dist[next.planet][next.fuel][next.time_used] == -1 ||
                dist[next.planet][next.fuel][next.time_used] > next.time_used) {
                if (state_count >= 99999) {
                continue;  // или break; — слишком много состояний
                }

                dist[next.planet][next.fuel][next.time_used] = next.time_used;
                states[state_count] = next;
                parent[state_count] = (state_count == 0) ? -1 : (state_count - 1);
                state_count++;
                push_heap(next);
            }
        }
    }

    return solution;
}