# cython: language_level=3

# Импортируем модель запроса и ответа для ЭТОЙ КОНКРЕТНОЙ задачи
from maraton.models import (
    Body as PyBody,
    Edge as PyEdge,
    SpaceMissionRequest,
    SuccessResponse,
    FailResponse
)
from libc.stdint cimport int32_t, int64_t
from libc.stdlib cimport malloc, free
import json
import numpy as np
cimport numpy as cnp
from libc.string cimport strcpy

# Подключаем C-функцию
cdef extern from "robinson_cruise_with_request_JSON.h":

    ctypedef struct GravityAssist:
        double velocity_gain
        double fuel_consumption
        int time_to_execute

    ctypedef struct Body:
        char id[50]
        int num_assists
        GravityAssist gravity_assists[10]

    ctypedef struct Edge:
        char from_point[50]
        char to[50]
        double distance

    ctypedef struct Solution:
        int success
        int time_used
        int fuel_left
        int path[100]
        int path_len

    char vertex_names[100][50]  # MAX_VERTICES=100, MAX_NAME_LEN=50
    int vertex_count

    Solution solve_mission(
        Body* bodies,
        int n_bodies,
        Edge* edges,
        int n_edges,
        const char* start_point,
        const char* rescue_point,
        int oxygen_time,
        double mass_shuttle,
        double mass_fuel_unit,
        double power_per_unit,
        int total_fuel,
        double fuel_consumption_per_sec
    )

def solve_mission_from_request(request):
    if len(request.bodies) == 0 or len(request.edges) == 0:
        return FailResponse(can_reach=False)

    cdef int n_bodies = len(request.bodies)
    cdef int n_edges = len(request.edges)

    cdef Body* bodies_arr = <Body*>malloc(n_bodies * sizeof(Body))
    cdef Edge* edges_arr = <Edge*>malloc(n_edges * sizeof(Edge))

    cdef int i, j
    cdef Solution result

    if not bodies_arr or not edges_arr:
        free(bodies_arr)
        free(edges_arr)
        return FailResponse(can_reach=False)
    try:
    # Заполняем bodies
        for i, py_body in enumerate(request.bodies):
        # Копируем id
            id_bytes = py_body.id.encode('utf-8')
            strcpy(bodies_arr[i].id, id_bytes)
            bodies_arr[i].num_assists = min(len(py_body.gravity_assists), 10)
            for j, assist in enumerate(py_body.gravity_assists[:10]):
                bodies_arr[i].gravity_assists[j].velocity_gain = assist.velocity_gain
                bodies_arr[i].gravity_assists[j].fuel_consumption = assist.fuel_consumption
                bodies_arr[i].gravity_assists[j].time_to_execute = assist.time_to_execute

    # Заполняем edges
        for i, py_edge in enumerate(request.edges):
            from_bytes = py_edge.from_point.encode('utf-8')
            to_bytes = py_edge.to.encode('utf-8')
            strcpy(edges_arr[i].from_point, from_bytes)
            strcpy(edges_arr[i].to, to_bytes)
            edges_arr[i].distance = py_edge.distance


        print("=== Debug: Input to solve_mission ===")
        print("Start_point:", request.start_point.encode('utf-8'))
        print("Rescue_point:", request.rescue_point.encode('utf-8'))
        print("Edges count:", n_edges)
        for i in range(n_edges):
            e = edges_arr[i]
            print(f"Edge {i}: {e.from_point.decode()} -> {e.to.decode()}, dist={e.distance}")
        print("Bodies count:", n_bodies)
        for i in range(n_bodies):
            b = bodies_arr[i]
            print(f"Body {i} ID: {b.id.decode()}")
            for j in range(b.num_assists):
                a = b.gravity_assists[j]
                print(f"  Assist {j}: vel_gain={a.velocity_gain}, fuel={a.fuel_consumption}, time={a.time_to_execute}")

    # Вызов
        result = solve_mission(
            bodies_arr, n_bodies,
            edges_arr, n_edges,
            request.start_point.encode('utf-8'),
            request.rescue_point.encode('utf-8'),
            request.oxygen_time,
            request.mass_shuttle,
            request.mass_fuel_unit,
            request.power_per_unit,
            request.total_fuel,
            request.fuel_consumption_per_sec
        )
    finally:
        free(bodies_arr)
        free(edges_arr)

    print("=== Result from solve_mission ===")
    print("result.success:", result.success)
    print("result.time_used:", result.time_used)
    print("result.fuel_left:", result.fuel_left)
    print("result.path_len:", result.path_len)
    print("result.path:", [result.path[i] for i in range(result.path_len)])

    if result.success:
        route = []
        for i in range(result.path_len):
            idx = result.path[i]
            if 0 <= idx < vertex_count:
                # Конвертируем C-string → Python str
                py_name = vertex_names[idx].decode('utf-8')
                route.append(py_name)
            else:
                return FailResponse(can_reach=False)

        return SuccessResponse(
            can_reach=True,
            min_flight_time=float(result.time_used),
            route=route
        )
    else:
        return FailResponse(can_reach=False)