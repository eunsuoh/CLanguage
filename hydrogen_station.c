#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define BOARD_SIZE 10
#define INF INT_MAX

typedef struct {
    int row, col;
} Point;

typedef struct {
    Point point;
    int priority;
} Node;

typedef struct {
    Node *data;
    int capacity;
    int size;
} PriorityQueue;

PriorityQueue *create_priority_queue(int capacity) {
    PriorityQueue *pq = (PriorityQueue *)malloc(sizeof(PriorityQueue));
    pq->data = (Node *)malloc(sizeof(Node) * capacity);
    pq->capacity = capacity;
    pq->size = 0;
    return pq;
}

void swap(Node *a, Node *b) {
    Node temp = *a;
    *a = *b;
    *b = temp;
}

void push(PriorityQueue *pq, Point point, int priority) {
    if (pq->size == pq->capacity) return;
    pq->data[pq->size].point = point;
    pq->data[pq->size].priority = priority;
    int i = pq->size;
    pq->size++;
    
    while (i > 0 && pq->data[(i - 1) / 2].priority > pq->data[i].priority) {
        swap(&pq->data[i], &pq->data[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

Node pop(PriorityQueue *pq) {
    Node root = pq->data[0];
    pq->data[0] = pq->data[pq->size - 1];
    pq->size--;
    
    int i = 0;
    while (i * 2 + 1 < pq->size) {
        int smallest = i * 2 + 1;
        if (i * 2 + 2 < pq->size && pq->data[i * 2 + 2].priority < pq->data[smallest].priority) {
            smallest = i * 2 + 2;
        }
        if (pq->data[i].priority < pq->data[smallest].priority) break;
        swap(&pq->data[i], &pq->data[smallest]);
        i = smallest;
    }
    return root;
}

bool is_empty(PriorityQueue *pq) {
    return pq->size == 0;
}

int heuristic(Point a, Point b) {
    return abs(a.row - b.row) + abs(a.col - b.col);
}

void a_star(int grid[BOARD_SIZE][BOARD_SIZE], Point start, Point goal, bool hydrogen_stations[BOARD_SIZE][BOARD_SIZE]) {
    int cost[BOARD_SIZE][BOARD_SIZE];
    Point came_from[BOARD_SIZE][BOARD_SIZE];
    
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            cost[i][j] = INF;
            came_from[i][j] = (Point){-1, -1};
        }
    }
    
    PriorityQueue *pq = create_priority_queue(BOARD_SIZE * BOARD_SIZE);
    push(pq, start, 0);
    cost[start.row][start.col] = 0;
    
    int directions[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    
    while (!is_empty(pq)) {
        Node current_node = pop(pq);
        Point current = current_node.point;
        
        if (current.row == goal.row && current.col == goal.col) break;
        
        for (int i = 0; i < 4; i++) {
            int new_row = current.row + directions[i][0];
            int new_col = current.col + directions[i][1];
            
            if (new_row >= 0 && new_row < BOARD_SIZE && new_col >= 0 && new_col < BOARD_SIZE) {
                int new_cost = cost[current.row][current.col] + grid[new_row][new_col];
                if (new_cost < cost[new_row][new_col]) {
                    cost[new_row][new_col] = new_cost;
                    int priority = new_cost + heuristic((Point){new_row, new_col}, goal);
                    push(pq, (Point){new_row, new_col}, priority);
                    came_from[new_row][new_col] = current;
                }
            }
        }
    }
    
    Point path[BOARD_SIZE * BOARD_SIZE];
    int path_length = 0;
    Point current = goal;
    while (current.row != -1 && current.col != -1) {
        path[path_length++] = current;
        current = came_from[current.row][current.col];
    }
    
    printf("Path:\n");
    for (int i = path_length - 1; i >= 0; i--) {
        printf("(%d, %d)", path[i].row, path[i].col);
        if (hydrogen_stations[path[i].row][path[i].col]) {
            printf(" (Hydrogen Station)");
        }
        printf("\n");
    }
    
    free(pq->data);
    free(pq);
}

int main() {
    int grid[BOARD_SIZE][BOARD_SIZE] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 2, 2, 2, 1, 1, 1, 1, 1, 1},
        {1, 2, 1, 1, 1, 2, 1, 1, 1, 1},
        {1, 1, 1, 2, 1, 2, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 2, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 2, 2, 1},
        {1, 1, 1, 1, 1, 1, 1, 2, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };
    
    bool hydrogen_stations[BOARD_SIZE][BOARD_SIZE] = {false};
    hydrogen_stations[2][5] = true;
    hydrogen_stations[7][7] = true;
    
    Point start = {0, 0};
    Point goal = {9, 9};
    
    a_star(grid, start, goal, hydrogen_stations);
    
    return 0;
}
