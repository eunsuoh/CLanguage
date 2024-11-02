#include <stdio.h>
#include <string.h>

#define MAX 100

// 스택 구조체 정의
typedef struct {
    char data[MAX];
    int top;
} Stack;

void init(Stack* stack) {
    stack->top = -1;
}

int IsEmpty(Stack* stack) {
    return stack->top == -1;
}

int IsFull(Stack* stack) {
    return stack->top == MAX - 1;
}

void push(Stack* stack, char value) {
    if (!IsFull(stack)) {
        stack->data[++(stack->top)] = value;
    }
}

char pop(Stack* stack) {
    if (!IsEmpty(stack)) {
        return stack->data[(stack->top)--];
    }
    return '\0';
}

char GetValue(Stack* stack) {
    if (!IsEmpty(stack)) {
        return stack->data[stack->top];
    }
    return '\0';
}

int main() {
    char S[MAX];
    char r[MAX] = "";
    int rn = 0, i;
    Stack stack;
    init(&stack);

    // 문자열 입력 받기
    printf("Enter a string: ");
    scanf("%s", S);

    int length = strlen(S);

    for (i = 0; i < length; i++) {
        while (!IsEmpty(&stack) && GetValue(&stack) < S[i]) {
            r[rn++] = pop(&stack);
        }
        push(&stack, S[i]);
    }

    // 스택에 남아있는 요소들을 r에 추가
    while (!IsEmpty(&stack)) {
        r[rn++] = pop(&stack);
    }

    r[rn] = '\0';  // 문자열 끝에 NULL 문자 추가
    printf("Result: %s\n", r);

    return 0;
}
