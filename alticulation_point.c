#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 100

int graph[MAX_VERTICES][MAX_VERTICES];  // 인접 행렬로 그래프 표현
int visited[MAX_VERTICES];
int dfn[MAX_VERTICES], low[MAX_VERTICES];
int parent[MAX_VERTICES];
bool articulation_points[MAX_VERTICES];
int time_counter = 0;

void add_edge(int u, int v) {
    graph[u][v] = 1;
    graph[v][u] = 1;
}

void dfs(int u, int vertices) {
    visited[u] = 1;
    dfn[u] = low[u] = ++time_counter;
    int children = 0;

    for (int v = 0; v < vertices; v++) {
        if (graph[u][v]) {  // u와 v가 연결되어 있는 경우
            if (!visited[v]) {
                parent[v] = u;
                children++;
                dfs(v, vertices);

                low[u] = (low[u] < low[v]) ? low[u] : low[v];  // low[u] 갱신

                // 단절점 조건 확인
                if (parent[u] == -1 && children > 1)  // 루트 노드의 경우
                    articulation_points[u] = true;
                
                if (parent[u] != -1 && low[v] >= dfn[u])  // 비루트 노드의 경우
                    articulation_points[u] = true;
            }
            else if (v != parent[u]) {  // 역방향 간선인 경우
                low[u] = (low[u] < dfn[v]) ? low[u] : dfn[v];
            }
        }
    }
}

void find_articulation_points(int vertices) {
    for (int i = 0; i < vertices; i++) {
        visited[i] = 0;
        parent[i] = -1;
        articulation_points[i] = false;
    }
    time_counter = 0;

    for (int i = 0; i < vertices; i++) {
        if (!visited[i]) {
            dfs(i, vertices);
        }
    }

    printf("Articulation points: ");
    for (int i = 0; i < vertices; i++) {
        if (articulation_points[i]) {
            printf("%d ", i);
        }
    }
    printf("\n");
}

int main() {
    int vertices = 5;

    // 그래프 초기화
    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            graph[i][j] = 0;
        }
    }

    // 간선 추가
    add_edge(1, 0);
    add_edge(0, 2);
    add_edge(2, 1);
    add_edge(0, 3);
    add_edge(3, 4);

    find_articulation_points(vertices);

    return 0;
}
