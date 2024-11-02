#include <stdio.h>

#define MAX 100

int parent[MAX];

// 초기화 함수: 각 요소가 자신을 부모로 가리키게 설정
void initialize(int n) {
    for (int i = 0; i < n; i++) {
        parent[i] = i;
    }
}

// Collapsing Find 함수: 경로 압축을 수행하여 루트를 찾음
int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);  // 재귀적으로 루트를 찾으며 경로 압축
    }
    return parent[x];
}

// Union 함수: 두 집합을 합침
void union_sets(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    if (rootX != rootY) {
        parent[rootY] = rootX;  // rootY의 부모를 rootX로 설정
    }
}

int main() {
    int n = 10;  // 예시로 10개의 요소
    initialize(n);

    // 예시 Union 연산
    union_sets(1, 2);
    union_sets(2, 3);
    union_sets(4, 5);
    union_sets(6, 7);
    union_sets(5, 6);

    // Find 연산 수행 및 출력
    printf("Find(3): %d\n", find(3));
    printf("Find(7): %d\n", find(7));

    // 경로 압축 확인
    for (int i = 0; i < n; i++) {
        printf("Parent of %d: %d\n", i, parent[i]);
    }

    return 0;
}
