// robinson_cruise.h
#ifndef ROBINSON_CRUISE_H
#define ROBINSON_CRUISE_H

#include <stdio.h>

#define MAX_PLANETS 50
#define MAX_FUEL 200
#define MAX_TIME 10000
#define MAX_MANEUVERS 5
#define MAX_PATH_LEN 100

// Структуры для входа
typedef struct {
    int id;
    char name[20];
    double mass;
    int num_radii;
    double radii[MAX_MANEUVERS];
} PlanetData;

typedef struct {
    int from, to;
    double distance;
} EdgeData;

// Структура для выхода
typedef struct {
    int success;
    int time_used;
    int path[MAX_PATH_LEN];   // последовательность планет
    int path_len;
    int fuel_left;
} Solution;

// Основная функция
Solution solve_mission(
    int n_planets,
    PlanetData planets[],
    int n_edges,
    EdgeData edges[],
    int rescue_point,
    int oxygen_limit,
    double initial_mass,
    int initial_fuel
);

#endif