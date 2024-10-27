#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX 100
#define INF 1000000

typedef struct {
    int x, y;
    int g, h, f;
    int parentX, parentY;
    int inOpen, inClosed;
} Node;

Node grid[MAX][MAX];
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

int heuristic(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

void AStar(int startX, int startY, int goalX, int goalY) {
    grid[startX][startY].g = 0;
    grid[startX][startY].h = heuristic(startX, startY, goalX, goalY);
    grid[startX][startY].f = grid[startX][startY].g + grid[startX][startY].h;
    grid[startX][startY].inOpen = 1;

    while (1) {
        int minF = INF, currentX = -1, currentY = -1;

        // 가장 낮은 f 값을 가진 노드를 탐색
        for (int i = 0; i < MAX; i++) {
            for (int j = 0; j < MAX; j++) {
                if (grid[i][j].inOpen && grid[i][j].f < minF) {
                    minF = grid[i][j].f;
                    currentX = i;
                    currentY = j;
                }
            }
        }

        if (currentX == -1) {
            printf("Goal not reachable.\n");
            return;
        }

        if (currentX == goalX && currentY == goalY) {
            printf("Goal reached.\n");
            return;
        }

        grid[currentX][currentY].inOpen = 0;
        grid[currentX][currentY].inClosed = 1;

        for (int i = 0; i < 4; i++) {
            int newX = currentX + dx[i];
            int newY = currentY + dy[i];

            if (newX < 0 || newY < 0 || newX >= MAX || newY >= MAX || grid[newX][newY].inClosed) continue;

            int tentativeG = grid[currentX][currentY].g + 1;
            if (!grid[newX][newY].inOpen || tentativeG < grid[newX][newY].g) {
                grid[newX][newY].g = tentativeG;
                grid[newX][newY].h = heuristic(newX, newY, goalX, goalY);
                grid[newX][newY].f = grid[newX][newY].g + grid[newX][newY].h;
                grid[newX][newY].parentX = currentX;
                grid[newX][newY].parentY = currentY;
                grid[newX][newY].inOpen = 1;
            }
        }
    }
}

int main() {
    int startX = 0, startY = 0, goalX = 5, goalY = 5;
    printf("A* Search from (%d, %d) to (%d, %d):\n", startX, startY, goalX, goalY);
    AStar(startX, startY, goalX, goalY);
    return 0;
}
