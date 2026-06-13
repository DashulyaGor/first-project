#include <stdio.h>
#include <stdlib.h>

#define MAX_V 100  // Максимальное количество вершин

// Граф как список смежности
typedef struct {
    int edges[MAX_V][MAX_V];  // adjacency matrix or count + list can be used
    int n;                    // количество вершин
} Graph;

// Стек для хранения порядка (вместо "вставки в начало")
int order[MAX_V];
int order_idx;

// Массив посещений
int visited[MAX_V];

// Инициализация графа
Graph* create_graph(int n) {
    Graph* g = (Graph*)malloc(sizeof(Graph));
    g->n = n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            g->edges[i][j] = 0;
        }
    }
    return g;
}

// Добавить ребро from → to
void add_edge(Graph* g, int from, int to) {
    g->edges[from][to] = 1;
}

// DFS с добавлением вершины в стек (вместо "вставить в начало order")
void dfs(Graph* g, int vertex) {
    visited[vertex] = 1;  // помечаем как посещённую

    // Перебираем все смежные вершины
    for (int v = 0; v < g->n; v++) {
        if (g->edges[vertex][v] == 1) {  // есть ребро vertex → v
            if (!visited[v]) {
                dfs(g, v);
            }
        }
    }

    // Вставляем vertex в начало order → делаем это через стек: push в конец
    order[order_idx++] = vertex;
}

// Топологическая сортировка
void top_sort(Graph* g) {
    order_idx = 0;  // сброс индекса результата
    for (int i = 0; i < g->n; i++) {
        visited[i] = 0;  // инициализируем visited как "не посещена"
    }

    // Обходим все вершины
    for (int v = 0; v < g->n; v++) {
        if (!visited[v]) {
            dfs(g, v);
        }
    }

    // Разворачиваем order? Нет! Мы добавляли в обратном порядке
    // Порядок уже правильный: от листьев к корням → при выводе читаем с конца
}

// Вывод результата
void print_order() {
    printf("Топологический порядок:\n");
    for (int i = order_idx - 1; i >= 0; i--) {
        printf("%d ", order[i]);
    }
    printf("\n");
}

// Пример использования
int main() {
    int n = 6;
    Graph* g = create_graph(n);

    // Пример графа: 5→2, 5→0, 4→0, 4→1, 2→3, 3→1
    add_edge(g, 5, 2);
    add_edge(g, 5, 0);
    add_edge(g, 4, 0);
    add_edge(g, 4, 1);
    add_edge(g, 2, 3);
    add_edge(g, 3, 1);

    top_sort(g);
    print_order();  // Ожидаем: 5 4 2 3 1 0 или другой допустимый порядок

    free(g);
    return 0;
}