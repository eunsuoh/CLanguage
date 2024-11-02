#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// 다항식 계산 함수
double evaluate_polynomial(int coefficients[], int degree, double x) {
    double result = 0.0;
    for (int i = 0; i <= degree; i++) {
        result += coefficients[i] * pow(x, degree - i);
    }
    return result;
}

// 다항식 출력 함수
void print_polynomial(int coefficients[], int degree) {
    printf("The polynomial is: ");
    for (int i = 0; i <= degree; i++) {
        if (coefficients[i] == 0) continue; // 계수가 0이면 출력 생략

        // 양수 계수일 때 + 표시 추가 (첫 항 제외)
        if (i > 0 && coefficients[i] > 0) {
            printf(" + ");
        }
        
        // 계수가 -1 또는 1이면서 상수항이 아닐 때, 1을 생략하고 x만 표시
        if (coefficients[i] == 1 && degree - i > 0) {
            printf("x");
        } else if (coefficients[i] == -1 && degree - i > 0) {
            printf("-x");
        } else {
            printf("%d", coefficients[i]); // 일반 계수 출력
        }

        // 차수 표시
        if (degree - i > 1) {
            printf("x^%d", degree - i);
        } else if (degree - i == 1) {
            printf("x");
        }
    }
    printf("\n");
}

int main() {
    int degree;

    // 차수 입력 받기
    printf("Enter the degree of the polynomial: ");
    scanf("%d", &degree);

    // 계수 배열 동적 할당
    int *coefficients = (int *)malloc((degree + 1) * sizeof(int));
    if (coefficients == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    // 계수 입력 받기
    printf("Enter the coefficients (from highest degree to constant term):\n");
    for (int i = 0; i <= degree; i++) {
        printf("Coefficient for x^%d: ", degree - i);
        scanf("%d", &coefficients[i]);
    }

    // 다항식 출력
    print_polynomial(coefficients, degree);

    // x 값 입력 받기
    double x;
    printf("Enter the value of x: ");
    scanf("%lf", &x);

    // 다항식 값 계산 및 출력
    double result = evaluate_polynomial(coefficients, degree, x);
    printf("Polynomial value at x = %.2f: %.2f\n", x, result);

    // 동적 메모리 해제
    free(coefficients);

    return 0;
}
