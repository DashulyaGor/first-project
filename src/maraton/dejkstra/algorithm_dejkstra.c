#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_V 100  // Максимальное количество вершин

// Ребро графа: из 'to' с весом 'weight'
typedef struct {
    int to;
    int weight;
} Edge;

// Список смежности
typedef struct {
    Edge edges[MAX_V];
    int count;
} AdjList;

// Граф
typedef struct {
    AdjList adj[MAX_V];
    int n;  // количество вершин
} Graph;

// Элемент мин-кучи (пирамиды)
typedef struct {
    int vertex;
    int dist;
} HeapNode;

// Мин-куча
typedef struct {
    HeapNode data[MAX_V];
    int size;
} MinHeap;

// Инициализация кучи
void init_heap(MinHeap* heap) {
    heap->size = 0;
}

// Вспомогательные функции кучи
void push_heap(MinHeap* heap, int v, int d) {
    int i = heap->size++;
    while (i > 0 && heap->data[(i-1)/2].dist > d) {
        heap->data[i] = heap->data[(i-1)/2];
        i = (i-1)/2;
    }
    heap->data[i].vertex = v;
    heap->data[i].dist = d;
}

int pop_heap(MinHeap* heap, int* dist) {
    if (heap->size == 0) return -1;
    int min_vertex = heap->data[0].vertex;
    *dist = heap->data[0].dist;

    HeapNode last = heap->data[--heap->size];
    int i = 0;
    while (2*i+1 < heap->size) {
        int child = 2*i+1;
        if (child+1 < heap->size && heap->data[child+1].dist < heap->data[child].dist)
            child++;
        if (heap->data[child].dist >= last.dist) break;
        heap->data[i] = heap->data[child];
        i = child;
    }
    heap->data[i] = last;
    return min_vertex;
}

// Алгоритм Дейкстры
void dijkstra(Graph* graph, int s, int d[]) {
    // d = [s = 0, остальные +inf]
    for (int i = 0; i < graph->n; i++) {
        d[i] = INT_MAX;
    }
    d[s] = 0;

    // heap = пирамида(s = 0, остальные +inf)
    MinHeap heap;
    init_heap(&heap);
    push_heap(&heap, s, 0);

    // marked = пустой ассоциативный массив (реализуем как массив dist)
    // repeat V раз
    int visited[MAX_V] = {0};  // чтобы не обрабатывать вершину дважды

    for (int i = 0; i < graph->n; i++) {
        // cur = извлекаем минимум из heap
        int cur_dist;
        int cur = pop_heap(&heap, &cur_dist);
        if (cur == -1 || visited[cur]) continue;
        visited[cur] = 1;

        // marked[cur] = d[cur] — можно считать, что d[cur] уже хранит кратчайшее расстояние
        // Обновляем соседей
        AdjList* adj = &graph->adj[cur];
        for (int j = 0; j < adj->count; j++) {
            int v = adj->edges[j].to;
            int w = adj->edges[j].weight;
            if (d[cur] + w < d[v]) {
                d[v] = d[cur] + w;
                push_heap(&heap, v, d[v]);
            }
        }
    }
}

// Вспомогательные функции
Graph* create_graph(int n) {
    Graph* g = (Graph*)malloc(sizeof(Graph));
    g->n = n;
    for (int i = 0; i < n; i++) {
        g->adj[i].count = 0;
    }
    return g;
}

void add_edge(Graph* g, int from, int to, int weight) {
    Edge* e = &g->adj[from].edges[g->adj[from].count++];
    e->to = to;
    e->weight = weight;
}

// Пример использования
int main() {
    int n = 5;
    Graph* g = create_graph(n);

    // Добавим рёбра
    add_edge(g, 0, 1, 10);
    add_edge(g, 0, 2, 3);
    add_edge(g, 1, 2, 1);
    add_edge(g, 1, 3, 2);
    add_edge(g, 2, 1, 4);
    add_edge(g, 2, 3, 8);
    add_edge(g, 2, 4, 2);
    add_edge(g, 3, 4, 7);
    add_edge(g, 4, 3, 9);

    int d[MAX_V];  // расстояния
    dijkstra(g, 0, d);

    printf("Кратчайшие расстояния от вершины 0:\n");
    for (int i = 0; i < n; i++) {
        printf("до %d: %d\n", i, d[i] == INT_MAX ? -1 : d[i]);
    }

    free(g);
    return 0;
}