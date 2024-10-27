#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MAX_N 5
#define INF 1000000

typedef struct {
    int puzzle[MAX_N][MAX_N];
    int g, h, f;
    int empty_x, empty_y;
} Node;

int N; // 퍼즐 크기 (NxN)

// 목표 상태 배열
int goal[MAX_N][MAX_N];

// 방향 벡터 (위, 아래, 왼쪽, 오른쪽)
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

// 목표 상태 설정
void setGoalState() {
    int count = 1;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            goal[i][j] = count % (N * N);
            count++;
        }
    }
}

// 맨해튼 거리 계산 (휴리스틱 h(n) 함수)
int calculateHeuristic(int puzzle[MAX_N][MAX_N]) {
    int dist = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int value = puzzle[i][j];
            if (value != 0) {
                int goal_x = (value - 1) / N;
                int goal_y = (value - 1) % N;
                dist += abs(i - goal_x) + abs(j - goal_y);
            }
        }
    }
    return dist;
}

// 퍼즐 상태 출력
void printPuzzle(int puzzle[MAX_N][MAX_N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%2d ", puzzle[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// 노드 생성
Node createNode(int puzzle[MAX_N][MAX_N], int empty_x, int empty_y, int g) {
    Node node;
    memcpy(node.puzzle, puzzle, sizeof(node.puzzle));
    node.empty_x = empty_x;
    node.empty_y = empty_y;
    node.g = g;
    node.h = calculateHeuristic(puzzle);
    node.f = node.g + node.h;
    return node;
}

// 퍼즐이 목표 상태인지 확인
int isGoal(int puzzle[MAX_N][MAX_N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (puzzle[i][j] != goal[i][j]) {
                return 0;
            }
        }
    }
    return 1;
}

// A* 알고리즘 적용
void AStar(int start[MAX_N][MAX_N], int empty_x, int empty_y) {
    Node current = createNode(start, empty_x, empty_y, 0);
    int openListSize = 1;
    Node openList[MAX_N * MAX_N * 10];
    openList[0] = current;

    while (openListSize > 0) {
        // 최소 f 값을 가진 노드 선택
        int minIndex = 0;
        for (int i = 1; i < openListSize; i++) {
            if (openList[i].f < openList[minIndex].f) {
                minIndex = i;
            }
        }
        
        current = openList[minIndex];
        openListSize--;
        for (int i = minIndex; i < openListSize; i++) {
            openList[i] = openList[i + 1];
        }

        if (isGoal(current.puzzle)) {
            printf("Goal reached with g(n) = %d\n", current.g);
            printPuzzle(current.puzzle);
            return;
        }

        // 빈칸을 이동할 수 있는 모든 방향으로 이동 시도
        for (int i = 0; i < 4; i++) {
            int newX = current.empty_x + dx[i];
            int newY = current.empty_y + dy[i];

            if (newX >= 0 && newY >= 0 && newX < N && newY < N) {
                Node newNode = createNode(current.puzzle, newX, newY, current.g + 1);

                // 빈칸과 새 위치 타일 교환
                newNode.puzzle[current.empty_x][current.empty_y] = newNode.puzzle[newX][newY];
                newNode.puzzle[newX][newY] = 0;

                openList[openListSize++] = newNode;
            }
        }
    }
    printf("No solution found.\n");
}

int main() {
    printf("Enter the size of the puzzle (N x N): ");
    scanf("%d", &N);

    int start[MAX_N][MAX_N];
    printf("Enter the starting puzzle state (use 0 for the empty space):\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &start[i][j]);
        }
    }

    int empty_x, empty_y;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (start[i][j] == 0) {
                empty_x = i;
                empty_y = j;
            }
        }
    }

    setGoalState();
    printf("Starting puzzle state:\n");
    printPuzzle(start);
    printf("Goal puzzle state:\n");
    printPuzzle(goal);

    AStar(start, empty_x, empty_y);
    return 0;
}
