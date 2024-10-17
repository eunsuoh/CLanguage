#include <stdio.h>

int fib2(int n) {
    int ary_fib2[n+1]; // 크기가 n+1인 배열 선언

    ary_fib2[0] = 0; // 첫 번째 항은 0
    ary_fib2[1] = 1; // 두 번째 항은 1

    for (int k = 2; k <= n; k++) {
        ary_fib2[k] = ary_fib2[k-1] + ary_fib2[k-2]; // 앞 두 항의 합을 현재 항에 저장
    }

    return ary_fib2[n]; // n번째 Fibonacci 값을 반환
}

int main() {
    int n;
    printf("Enter the value of N: ");
    scanf("%d", &n);

    printf("Fibonacci number at position %d is %d\n", n, fib2(n));
    
    return 0;
}
