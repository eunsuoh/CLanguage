#include <stdio.h>

#define INF 1000

// 미니맥스 알고리즘에 알파-베타 가지치기를 적용한 함수
int minimax(int depth, int nodeIndex, int isMax, int values[], int alpha, int beta, int maxDepth) {
    // 리프 노드에 도달한 경우 해당 값을 반환
    if (depth == maxDepth) {
        return values[nodeIndex];
    }

    if (isMax) {
        int best = -INF;
        for (int i = 0; i < 2; i++) {
            int val = minimax(depth + 1, nodeIndex * 2 + i, 0, values, alpha, beta, maxDepth);
            best = (best > val) ? best : val;
            alpha = (alpha > best) ? alpha : best;
            
            // 가지치기 조건
            if (beta <= alpha) {
                break;
            }
        }
        return best;
    } else {
        int best = INF;
        for (int i = 0; i < 2; i++) {
            int val = minimax(depth + 1, nodeIndex * 2 + i, 1, values, alpha, beta, maxDepth);
            best = (best < val) ? best : val;
            beta = (beta < best) ? beta : best;
            
            // 가지치기 조건
            if (beta <= alpha) {
                break;
            }
        }
        return best;
    }
}

int main() {
    // 트리의 리프 노드 값들
    int values[] = {3, 5, 6, 9, 1, 2, 0, -1};
    int maxDepth = 3;  // 트리의 최대 깊이

    // 미니맥스 알고리즘 실행
    int optimalValue = minimax(0, 0, 1, values, -INF, INF, maxDepth);
    printf("Optimal value: %d\n", optimalValue);

    return 0;
}
