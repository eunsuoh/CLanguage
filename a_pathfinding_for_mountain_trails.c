#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define INF 1e9
#define MAX_NODES 100

// Define Node structure
typedef struct {
    int x, y; // Node coordinates
    int height; // Node elevation
} Node;

// Define Priority Queue Node
typedef struct {
    int node;
    double cost;
} PQNode;

typedef struct {
    PQNode heap[MAX_NODES];
    int size;
} PriorityQueue;

void pq_push(PriorityQueue *pq, int node, double cost) {
    pq->heap[pq->size].node = node;
    pq->heap[pq->size].cost = cost;
    int i = pq->size++;
    while (i > 0 && pq->heap[i].cost < pq->heap[(i - 1) / 2].cost) {
        PQNode temp = pq->heap[i];
        pq->heap[i] = pq->heap[(i - 1) / 2];
        pq->heap[(i - 1) / 2] = temp;
        i = (i - 1) / 2;
    }
}

int pq_pop(PriorityQueue *pq) {
    int node = pq->heap[0].node;
    pq->heap[0] = pq->heap[--pq->size];
    int i = 0;
    while (1) {
        int left = 2 * i + 1, right = 2 * i + 2, smallest = i;
        if (left < pq->size && pq->heap[left].cost < pq->heap[smallest].cost) smallest = left;
        if (right < pq->size && pq->heap[right].cost < pq->heap[smallest].cost) smallest = right;
        if (smallest == i) break;
        PQNode temp = pq->heap[i];
        pq->heap[i] = pq->heap[smallest];
        pq->heap[smallest] = temp;
        i = smallest;
    }
    return node;
}

int pq_empty(PriorityQueue *pq) {
    return pq->size == 0;
}

// Heuristic function: Calculates Euclidean distance
double heuristic(Node a, Node b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

// A* Algorithm function
void a_star(int start, int goal, Node nodes[], int graph[MAX_NODES][MAX_NODES], int n) {
    double g[MAX_NODES], f[MAX_NODES];
    int came_from[MAX_NODES];
    PriorityQueue open_set;
    open_set.size = 0;

    for (int i = 0; i < n; i++) {
        g[i] = INF;
        f[i] = INF;
        came_from[i] = -1;
    }

    g[start] = 0;
    f[start] = heuristic(nodes[start], nodes[goal]);
    pq_push(&open_set, start, f[start]);

    while (!pq_empty(&open_set)) {
        int current = pq_pop(&open_set);

        if (current == goal) {
            printf("Path: ");
            int path[MAX_NODES], path_size = 0;
            for (int node = goal; node != -1; node = came_from[node]) {
                path[path_size++] = node;
            }
            for (int i = path_size - 1; i >= 0; i--) {
                printf("%d ", path[i]);
            }
            printf("\n");
            return;
        }

        for (int neighbor = 0; neighbor < n; neighbor++) {
            if (graph[current][neighbor] > 0) {
                double tentative_g = g[current] + graph[current][neighbor];

                if (tentative_g < g[neighbor]) {
                    came_from[neighbor] = current;
                    g[neighbor] = tentative_g;
                    f[neighbor] = g[neighbor] + heuristic(nodes[neighbor], nodes[goal]);
                    pq_push(&open_set, neighbor, f[neighbor]);
                }
            }
        }
    }
    printf("No path found.\n");
}

int main() {
    int n, start, goal;
    Node nodes[MAX_NODES];
    int graph[MAX_NODES][MAX_NODES];

    // Input nodes and graph
    printf("Enter the number of nodes: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        printf("Enter the x, y coordinates and height of node %d: ", i);
        scanf("%d %d %d", &nodes[i].x, &nodes[i].y, &nodes[i].height);
    }

    printf("Enter the start and goal nodes: ");
    scanf("%d %d", &start, &goal);

    printf("Enter the adjacency matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    a_star(start, goal, nodes, graph, n);

    return 0;
}
