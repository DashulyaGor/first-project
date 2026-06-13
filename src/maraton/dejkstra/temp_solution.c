// robinson_cruise_optimized.c
#include "robinson_cruise.h"
#include <string.h>
#include <math.h>
#include <stdlib.h>

// === Физические константы ===
const double G = 6.67430e-11;
const double SCALE_G = 1e10;
const double BASE_THRUST = 1.0;

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
    int prev;  // для восстановления пути
} State;

// === Глобальные данные ===
typedef struct {
    int id;
    char name[20];
    double mass;
    int num_radii;
    double radii[MAX_MANEUVERS];
} Planet;

Planet planets[MAX_PLANETS];

typedef struct {
    int from, to;
    double distance;
} Edge;

typedef struct {
    Edge edges[MAX_PLANETS];
    int count;
} EdgeList;

EdgeList graph[MAX_PLANETS];
int n_planets_g;
int rescue_point_g;
int oxygen_limit_g;
double initial_mass_g;
int initial_fuel_g;

// === Мин-куча для Дейкстры ===
#define HEAP_SIZE 100000
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

// === dist[p][f][t] — минимальное время ===
int dist[MAX_PLANETS][MAX_FUEL][MAX_TIME];

// === Применить манёвр ===
ManeuverResult apply_maneuver(int planet_id, double speed_in, int fuel_before) {
    ManeuverResult best = {speed_in, fuel_before, 0};
    Planet* p = &planets[planet_id];

    for (int i = 0; i < p->num_radii; i++) {
        double r = p->radii[i];
        double escape_velocity = sqrt((SCALE_G * G * p->mass) / r);
        double delta_v = 1.8 * escape_velocity;
        double fuel_cost = 2.0 + (10.0 / r);
        double time_cost = 1.0 + (5.0 / r);

        if (fuel_before >= fuel_cost) {
            double new_speed = speed_in + delta_v;
            int new_fuel = fuel_before - (int)ceil(fuel_cost);
            int time_add = (int)ceil(time_cost);

            if (new_speed > best.speed_out) {
                best.speed_out = new_speed;
                best.fuel_after = new_fuel;
                best.time_added = time_add;
            }
        }
    }
    return best;
}

// === Моделирование перелёта ===
double simulate_leg(double distance, int *fuel_used, int fuel, double dry_mass, double initial_speed) {
    double current_mass = dry_mass + fuel;
    double speed = initial_speed;
    double dist_traveled = 0.0;
    int time = 0;

    int boost_phase = fuel / 2;
    for (int i = 0; i < boost_phase; i++) {
        if (dist_traveled >= distance * 0.5 || current_mass <= dry_mass) break;
        double acc = BASE_THRUST / current_mass;
        dist_traveled += speed + 0.5 * acc;
        speed += acc;
        current_mass -= 1.0;
        time++;
        if (--fuel <= 0) break;
    }

    double remaining = distance - dist_traveled;
    if (speed > 1e-6 && remaining > 0) {
        int coast_time = (int)(remaining / speed);
        time += coast_time;
        dist_traveled += speed * coast_time;
        remaining -= speed * coast_time;
    }

    while (fuel > 0 && remaining > 1e-6 && speed > 1e-6) {
        double acc = BASE_THRUST / current_mass;
        if (acc >= speed) { time++; fuel--; break; }
        dist_traveled += speed - 0.5 * acc;
        remaining -= (speed - 0.5 * acc);
        speed -= acc;
        current_mass -= 1.0;
        time++;
        fuel--;
    }

    if (speed > 1e-6) return -1;
    *fuel_used = (initial_fuel_g - fuel);
    return time;
}

// === Основная функция ===
Solution solve_mission(
    int n_planets,
    PlanetData planets_in[],
    int n_edges,
    EdgeData edges_in[],
    int rescue_point,
    int oxygen_limit,
    double initial_mass,
    int initial_fuel
) {
    // Инициализация
    n_planets_g = n_planets;
    rescue_point_g = rescue_point;
    oxygen_limit_g = oxygen_limit;
    initial_mass_g = initial_mass;
    initial_fuel_g = initial_fuel;

    memset(dist, -1, sizeof(dist));
    heap_size = 0;

    for (int i = 0; i < MAX_PLANETS; i++) graph[i].count = 0;

    for (int i = 0; i < n_planets; i++) {
        planets[i] = (Planet){
            .id = planets_in[i].id,
            .mass = planets_in[i].mass,
            .num_radii = planets_in[i].num_radii
        };
        strcpy(planets[i].name, planets_in[i].name);
        for (int j = 0; j < planets_in[i].num_radii; j++) {
            planets[i].radii[j] = planets_in[i].radii[j];
        }
    }

    for (int i = 0; i < n_edges; i++) {
        add_edge(edges_in[i].from, edges_in[i].to, edges_in[i].distance);
    }

    // Поиск
    Solution solution = {0};

    State start = {0, initial_fuel, 0.0, 0, -1};
    push_heap(start);
    dist[0][initial_fuel][0] = 0;

    State states[100000];
    int state_count = 0;
    int parent[100000];
    memset(parent, -1, sizeof(parent));

    while (!is_empty()) {
        State s = pop_heap();
        if (s.time_used != dist[s.planet][s.fuel][s.time_used]) continue;

        ManeuverResult mr = apply_maneuver(s.planet, s.speed, s.fuel);
        State after = {s.planet, mr.fuel_after, mr.speed_out, s.time_used + mr.time_added, s.prev};

        if (s.planet == rescue_point) {
            solution.success = 1;
            solution.time_used = after.time_used;
            solution.fuel_left = after.fuel;

            // Восстанавливаем путь
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

        if (after.time_used >= oxygen_limit) continue;

        EdgeList* el = &graph[s.planet];
        for (int i = 0; i < el->count; i++) {
            Edge e = el->edges[i];
            int fuel_needed;
            double leg_time = simulate_leg(e.distance, &fuel_needed, after.fuel, initial_mass, after.speed);
            if (leg_time < 0) continue;

            int total_time = after.time_used + (int)leg_time;
            int fuel_after = after.fuel - fuel_needed;
            if (fuel_after < 0 || total_time >= MAX_TIME) continue;

            State next = {e.to, fuel_after, 0.0, total_time, state_count - 1};

            if (dist[next.planet][next.fuel][next.time_used] == -1 ||
                dist[next.planet][next.fuel][next.time_used] > next.time_used) {

                dist[next.planet][next.fuel][next.time_used] = next.time_used;
                states[state_count] = next;
                parent[state_count] = s.planet == next.planet ? parent[state_count - 1] : (state_count - 1);
                state_count++;
                push_heap(next);
            }
        }
    }

    return solution;
}