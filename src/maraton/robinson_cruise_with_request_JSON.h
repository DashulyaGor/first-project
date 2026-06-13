#ifndef ROBINSON_CRUISE_WITH_REQUEST_JSON_H
#define ROBINSON_CRUISE_WITH_REQUEST_JSON_H

#include <stdio.h>
#include <string.h>

#define MAX_NAME_LEN 50
#define MAX_BODIES 50
#define MAX_EDGES 100
#define MAX_ASSISTS 10
#define MAX_PATH_LEN 100
#define MAX_FUEL 1000
#define MAX_TIME 5000
#define HEAP_SIZE 100000

// === Глобальные данные (для доступа из Cython) ===
extern char vertex_names[MAX_BODIES * 2][MAX_NAME_LEN];
extern int vertex_count;


typedef struct {
    double velocity_gain;
    double fuel_consumption;
    int time_to_execute;
} GravityAssist;

// Входные данные
typedef struct {
    char id[MAX_NAME_LEN];
    int num_assists;
    GravityAssist gravity_assists[MAX_ASSISTS];
} Body;

typedef struct {
    char from_point[MAX_NAME_LEN];
    char to[MAX_NAME_LEN];
    double distance;
} Edge;

// Результат
typedef struct {
    int success;
    int time_used;
    int fuel_left;
    int path[MAX_PATH_LEN];
    int path_len;
} Solution;

// Основная функция
Solution solve_mission(
    Body bodies[],
    int n_bodies,
    Edge edges[],
    int n_edges,
    const char* start_point,
    const char* rescue_point,
    int oxygen_time,
    double mass_shuttle,
    double mass_fuel_unit,
    double power_per_unit,
    int total_fuel,
    double fuel_consumption_per_sec
);

#endif