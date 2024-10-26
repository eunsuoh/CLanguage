#include <stdio.h>

int fib1(int n) {
    if (n <= 1)
        return n;
    else
        return fib1(n - 1) + fib1(n - 2); // fib1 함수가 재귀적으로 호출됨
}

int main() {
    int n;
    printf("Enter the value of N: ");
    scanf("%d", &n);
    printf("Fibonacci number at position %d is %d\n", n, fib1(n));
    
    return 0;
}
10
