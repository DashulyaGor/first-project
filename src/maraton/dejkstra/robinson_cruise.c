#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>

#define MAX_PLANETS 100
#define MAX_MANEUVERS 10
#define MAX_FUEL 1000
#define MAX_TIME 10000

// Физические константы (в условных единицах)
const double G = 6.67430e-11;   // гравитационная постоянная (для масштаба)
const double SCALE_G = 1e10;    // масштабируем, чтобы числа были удобными
const double BASE_THRUST = 1.0; // условная сила двигателя

typedef struct {
    double delta_v;     // прирост скорости
    double fuel_cost;   // топливо на коррекцию
    double time_cost;   // время выполнения
} ComputedManeuver;

typedef struct {
    double speed_out;   // выходная скорость
    int fuel_after;     // топливо после манёвра
    int time_added;     // дополнительное время
    int success;        // удалось ли?
} ManeuverResult;

// Планета
typedef struct {
    int id;
    char name[20];
    double mass;                    // масса тела
    int num_radii;
    double radii[MAX_MANEUVERS];    // допустимые радиусы облета
} Body;

// Ребро графа
typedef struct {
    int from, to;
    double distance;  // метры
} Edge;

typedef struct {
    Edge edges[MAX_PLANETS];
    int count;
} EdgeList;

// Состояние шаттла
typedef struct {
    int body;       // текущая планета
    int fuel;         // остаток топлива
    double speed;     // текущая скорость
    int time_used;    // затраченное время
} State;

// Глобальные данные
Body bodies[MAX_PLANETS];
EdgeList graph[MAX_PLANETS];
int n_bodies;
int rescue_point;
int oxygen_limit;   // максимальное время полёта
double initial_mass; // масса шаттла без топлива
int initial_fuel;             // начальный запас топлива

// Очередь для BFS
State queue[100000];
int dist[MAX_PLANETS][MAX_FUEL][MAX_TIME];  // dist[p][f][t] = минимальное время
int front, rear;

// Инициализация очереди
void init_bfs() {
    front = rear = 0;
    memset(dist, -1, sizeof(dist));
}

// Добавить состояние в очередь
void enqueue(State s) {
    queue[rear++] = s;
}

// Извлечь состояние
State dequeue() {
    return queue[front++];
}

// Проверка, пуста ли очередь
int is_empty() {
    return front >= rear;
}

ManeuverResult apply_maneuver(int body_id, double speed_in, int fuel_before) {
    Body* p = &bodies[body_id];
    ManeuverResult best = { 0 };  // по умолчанию — не делать манёвр

    // Вариант 1: пролететь без манёвра
    best.speed_out = speed_in;
    best.fuel_after = fuel_before;
    best.time_added = 0;
    best.success = 1;

    // Перебираем все возможные манёвры
    for (int i = 0; i < p->num_radii; i++) {
        double r = p->radii[i]; // радиус облёта

        // 1. Прирост скорости от гравитационного манёвра
        // Упрощённая модель: Δv ≈ 2 * v_escape * sin(θ/2)
        // Но здесь: Δv ∝ sqrt(G*M / r)
        double escape_velocity = sqrt((SCALE_G * G * p->mass) / r);
        double delta_v = 1.8 * escape_velocity;  // коэффициент зависит от угла подхода

        // 2. Затраты топлива на коррекцию курса
        // Чем ближе — тем сложнее корректировать
        double fuel_cost = 2.0 + (10.0 / r);  // минимум 2 единицы

        // 3. Время выполнения манёвра
        double time_cost = 1.0 + (5.0 / r);   // ~1–6 сек

        if (fuel_before >= fuel_cost) {
            double new_speed = speed_in + delta_v;
            int new_fuel = fuel_before - (int)ceil(fuel_cost);
            int time_add = (int)ceil(time_cost);

            // Если этот манёвр даёт лучшую скорость — выбираем его
            // (можно менять критерий: min time, max speed, etc.)
            if (new_speed > best.speed_out) {
                best.speed_out = new_speed;
                best.fuel_after = new_fuel;
                best.time_added = time_add;
            }
        }
    }

    return best;
}

// Расчет времени и топлива на разгон и торможение
// Возвращает: общее время движения (разгон + инерция + торможение)
// или -1, если невозможно
double simulate_leg(double distance, int *fuel_used, int fuel, double dry_mass, double initial_speed) {
    double speed = initial_speed;
    double current_mass = dry_mass + fuel; // начальная масса шаттла
    double dist_traveled = 0.0;
    int time = 0;

     // === Разгон (если есть топливо и нужно ускоряться) ===
    int boost_phase = fuel / 2;  // половина топлива на разгон
    for (int i = 0; i < boost_phase; i++) {
        if (dist_traveled >= distance * 0.5) break;  // не больше половины
        if (current_mass <= dry_mass) break;

        double acc = BASE_THRUST / current_mass;  // a = F/m
        dist_traveled += speed + 0.5 * acc;       // s = v*t + ½*a*t²
        speed += acc;
        current_mass -= 1.0;  // сжигаем 1 ед. топлива
        time++;
        if (--fuel <= 0) break;
    }

    // === Полёт по инерции ===
    double remaining = distance - dist_traveled;
    if (speed > 1e-6 && remaining > 0) {
        int coast_time = (int)(remaining / speed);
        time += coast_time;
        dist_traveled += speed * coast_time;
        remaining -= speed * coast_time;
    }

    // === Торможение до нуля ===
    while (fuel > 0 && remaining > 1e-6 && speed > 1e-6) {
        double acc = BASE_THRUST / current_mass;
        if (acc >= speed) {
            // Последняя секунда: останавливаемся точно
            time++;
            fuel--;
            break;
        }
        dist_traveled += speed - 0.5 * acc;
        remaining -= (speed - 0.5 * acc);
        speed -= acc;
        current_mass -= 1.0;
        time++;
        fuel--;
    }

    // Проверка: полностью остановились?
    if (speed > 1e-6) return -1;  // не удалось затормозить

    *fuel_used = (initial_fuel - fuel);
    return time;
}

// Простой BFS по состояниям (можно заменить на A*)
int find_fastest_path(int start) {
    init_bfs();
    int best_time = INT_MAX;

    State start_state = {start, initial_fuel, 0.0, 0};
    enqueue(start_state);
    dist[start][initial_fuel][0] = 0;

    while (!is_empty()) {
        State s = dequeue();

        // Применяем манёвр на текущей планете
        ManeuverResult mr = apply_maneuver(s.body, s.speed, s.fuel);
        State after = {
            .body = s.body,
            .fuel = mr.fuel_after,
            .speed = mr.speed_out,
            .time_used = s.time_used + mr.time_added
        };

        // Проверка цели
        if (s.body == rescue_point) {
            if (after.time_used < best_time) {
                best_time = after.time_used;
            }
            continue;
        }

        if (after.time_used >= oxygen_limit) continue;

        // Перебираем рёбра
        EdgeList* el = &graph[s.body];
        for (int i = 0; i < el->count; i++) {
            Edge e = el->edges[i];

            int fuel_needed;
            double leg_time = simulate_leg(e.distance, &fuel_needed, after.fuel, initial_mass, after.speed);
            if (leg_time < 0 || after.time_used + leg_time >= best_time) continue;

            int total_time = after.time_used + (int)leg_time;
            int fuel_after = after.fuel - fuel_needed;

            if (fuel_after < 0 || total_time >= MAX_TIME) continue;

            State next = {e.to, fuel_after, 0.0, total_time};

            if (dist[next.body][next.fuel][next.time_used] == -1 ||
                dist[next.body][next.fuel][next.time_used] > next.time_used) {
                dist[next.body][next.fuel][next.time_used] = next.time_used;
                enqueue(next);
            }
        }
    }

    return best_time == INT_MAX ? -1 : best_time;
}

// Вспомогательные
void add_edge(int from, int to, double d) {
    Edge* e = &graph[from].edges[graph[from].count++];
    e->from = from; e->to = to; e->distance = d;
}

void init_example() {
    n_bodies = 4;
    initial_mass = 10.0;
    initial_fuel = 100;
    oxygen_limit = 1000;
    rescue_point = 3;

    // Планеты
    strcpy(bodies[0].name, "Earth");
    bodies[0].id = 0;
    bodies[0].mass = 500.0;
    bodies[0].num_radii = 0;

    strcpy(bodies[1].name, "Jupiter");
    bodies[1].id = 1;
    bodies[1].mass = 1500.0;
    bodies[1].num_radii = 3;
    bodies[1].radii[0] = 5.0;   // близко → сильный разгон
    bodies[1].radii[1] = 10.0;
    bodies[1].radii[2] = 20.0;

    strcpy(bodies[2].name, "Mars");
    bodies[2].id = 2;
    bodies[2].mass = 300.0;
    bodies[2].num_radii = 2;
    bodies[2].radii[0] = 6.0;
    bodies[2].radii[1] = 12.0;

    strcpy(bodies[3].name, "Rescue");
    bodies[3].id = 3;
    bodies[3].mass = 100.0;           // небольшая масса
    bodies[3].num_radii = 0;

    // Добавляем возможные перелёты
    add_edge(0, 1, 700.0);   // Earth → Jupiter
    add_edge(1, 2, 400.0);   // Jupiter → Mars
    add_edge(2, 3, 300.0);   // Mars → Rescue
    add_edge(0, 2, 900.0);   // Earth → Mars (обходной)
    add_edge(0, 3, 1200.0);  // Earth → Rescue (прямой, но долгий)
}

int main() {
    init_example();

    int min_time = find_fastest_path(0);

    if (min_time == -1) {
        printf("NO\n");
    } else {
        printf("YES\n%d\n", min_time);
    }

    return 0;
}