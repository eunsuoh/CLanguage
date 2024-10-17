#include <stdio.h>
#include <stdlib.h>

// 노드 구조체 정의
struct Node {
    int data;             // 노드에 저장할 데이터
    struct Node* next;    // 다음 노드를 가리키는 포인터
};

// 연결 리스트의 헤드 포인터
struct Node* head = NULL;

// 노드를 리스트의 맨 앞에 추가하는 함수
void push(int new_data) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node)); // 새로운 노드 생성
    new_node->data = new_data;   // 데이터 초기화
    new_node->next = head;       // 현재 헤드 포인터를 다음 노드로 설정
    head = new_node;             // 헤드를 새로운 노드로 업데이트
}

// 리스트의 모든 노드를 출력하는 함수
void printList() {
    struct Node* current = head; // 현재 노드를 헤드로 초기화
    while (current != NULL) {
        printf("%d -> ", current->data); // 데이터 출력
        current = current->next;          // 다음 노드로 이동
    }
    printf("NULL\n"); // 리스트의 끝을 표시
}

// 메모리 해제를 위한 함수
void freeList() {
    struct Node* current = head;
    struct Node* next;

    while (current != NULL) {
        next = current->next; // 다음 노드를 저장
        free(current);        // 현재 노드 메모리 해제
        current = next;      // 다음 노드로 이동
    }

    head = NULL; // 헤드 포인터 초기화
}

int main() {
    int value, n;

    printf("How many nodes do you want to add? ");
    scanf("%d", &n); // 추가할 노드의 수 입력받기

    // 사용자로부터 노드의 값을 입력받아 리스트에 추가
    for (int i = 0; i < n; i++) {
        printf("Enter value for node %d: ", i + 1);
        scanf("%d", &value); // 각 노드의 값 입력받기
        push(value); // 입력받은 값을 리스트에 추가
    }

    // 현재 연결 리스트 출력
    printf("Current Linked List: ");
    printList();

    freeList(); // 메모리 해제
    return 0;
}
