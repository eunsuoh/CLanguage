#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// 다항식 출력 함수
void print_polynomial(int coefficients[], int degree) {
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

// 다항식 덧셈 함수
void add_polynomials(int poly1[], int poly2[], int result[], int degree1, int degree2) {
    int max_degree = (degree1 > degree2) ? degree1 : degree2;
    
    for (int i = 0; i <= max_degree; i++) {
        int coeff1 = (i <= degree1) ? poly1[i] : 0;
        int coeff2 = (i <= degree2) ? poly2[i] : 0;
        result[i] = coeff1 + coeff2;
    }
}

// 다항식 뺄셈 함수
void subtract_polynomials(int poly1[], int poly2[], int result[], int degree1, int degree2) {
    int max_degree = (degree1 > degree2) ? degree1 : degree2;

    for (int i = 0; i <= max_degree; i++) {
        int coeff1 = (i <= degree1) ? poly1[i] : 0;
        int coeff2 = (i <= degree2) ? poly2[i] : 0;
        result[i] = coeff1 - coeff2;
    }
}

int main() {
    int degree1, degree2;

    // 첫 번째 다항식 입력
    printf("Enter the degree of the first polynomial: ");
    scanf("%d", &degree1);
    int *poly1 = (int *)malloc((degree1 + 1) * sizeof(int));
    printf("Enter the coefficients (from highest degree to constant term):\n");
    for (int i = 0; i <= degree1; i++) {
        printf("Coefficient for x^%d: ", degree1 - i);
        scanf("%d", &poly1[i]);
    }

    // 두 번째 다항식 입력
    printf("Enter the degree of the second polynomial: ");
    scanf("%d", &degree2);
    int *poly2 = (int *)malloc((degree2 + 1) * sizeof(int));
    printf("Enter the coefficients (from highest degree to constant term):\n");
    for (int i = 0; i <= degree2; i++) {
        printf("Coefficient for x^%d: ", degree2 - i);
        scanf("%d", &poly2[i]);
    }

    // 최대 차수를 계산하여 결과 배열 생성
    int max_degree = (degree1 > degree2) ? degree1 : degree2;
    int *result_add = (int *)malloc((max_degree + 1) * sizeof(int));
    int *result_sub = (int *)malloc((max_degree + 1) * sizeof(int));

    // 덧셈 및 뺄셈 수행
    add_polynomials(poly1, poly2, result_add, degree1, degree2);
    subtract_polynomials(poly1, poly2, result_sub, degree1, degree2);

    // 결과 출력
    printf("First polynomial: ");
    print_polynomial(poly1, degree1);

    printf("Second polynomial: ");
    print_polynomial(poly2, degree2);

    printf("Sum of polynomials: ");
    print_polynomial(result_add, max_degree);

    printf("Difference of polynomials: ");
    print_polynomial(result_sub, max_degree);

    // 동적 메모리 해제
    free(poly1);
    free(poly2);
    free(result_add);
    free(result_sub);

    return 0;
}
