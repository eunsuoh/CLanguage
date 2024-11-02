#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void fail(char *pat) {
    int i, j;
    int n = strlen(pat);
    int *failure = (int *)malloc(n * sizeof(int));  // 동적 배열 할당

    if (failure == NULL) {
        printf("Memory allocation failed\n");
        return;
    }

    failure[0] = -1;
    for (j = 1; j < n; j++) {
        i = failure[j - 1];
        while ((pat[j] != pat[i + 1]) && (i >= 0))
            i = failure[i];
        if (pat[j] == pat[i + 1])
            failure[j] = i + 1;
        else
            failure[j] = -1;
    }

    for (i = 0; i < n; i++)
        printf("%d ", failure[i]);
    printf("\n");

    free(failure);  // 동적 메모리 해제
}

int main() {
    char patp[100];  // 최대 99글자까지 입력 가능하도록 배열 선언
    printf("Enter the pattern: ");
    scanf("%s", patp);

    fail(patp);
    return 0;
}
