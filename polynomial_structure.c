#include <stdio.h>
#include <stdlib.h>

// 다항식을 나타내는 구조체 정의
typedef struct {
    int degree;     // 차수
    int coefficient; // 계수
} Term;

// 다항식 구조체 정의
typedef struct {
    Term *terms;    // 다항식의 항 배열
    int num_terms;  // 다항식의 항 개수
} Polynomial;

// 다항식 출력 함수
void print_polynomial(Polynomial poly) {
    for (int i = 0; i < poly.num_terms; i++) {
        int coef = poly.terms[i].coefficient;
        int deg = poly.terms[i].degree;

        if (coef == 0) continue; // 계수가 0이면 출력 생략

        // 첫 항이 아니고, 계수가 양수일 때 + 표시 추가
        if (i > 0 && coef > 0) printf(" + ");
        
        // 계수가 1 또는 -1일 때 x만 표시
        if (coef == 1 && deg != 0) printf("x");
        else if (coef == -1 && deg != 0) printf("-x");
        else printf("%d", coef);

        // 차수 표시
        if (deg > 1) printf("x^%d", deg);
        else if (deg == 1) printf("x");
    }
    printf("\n");
}

// 다항식 덧셈 함수
Polynomial add_polynomials(Polynomial poly1, Polynomial poly2) {
    int max_degree = (poly1.terms[0].degree > poly2.terms[0].degree) ? poly1.terms[0].degree : poly2.terms[0].degree;
    Polynomial result;
    result.terms = (Term *)malloc((max_degree + 1) * sizeof(Term));
    result.num_terms = max_degree + 1;

    // 결과 다항식 초기화
    for (int i = 0; i <= max_degree; i++) {
        result.terms[i].degree = max_degree - i;
        result.terms[i].coefficient = 0;
    }

    // 첫 번째 다항식의 항 더하기
    for (int i = 0; i < poly1.num_terms; i++) {
        int deg = poly1.terms[i].degree;
        result.terms[max_degree - deg].coefficient += poly1.terms[i].coefficient;
    }

    // 두 번째 다항식의 항 더하기
    for (int i = 0; i < poly2.num_terms; i++) {
        int deg = poly2.terms[i].degree;
        result.terms[max_degree - deg].coefficient += poly2.terms[i].coefficient;
    }

    return result;
}

// 다항식 뺄셈 함수
Polynomial subtract_polynomials(Polynomial poly1, Polynomial poly2) {
    int max_degree = (poly1.terms[0].degree > poly2.terms[0].degree) ? poly1.terms[0].degree : poly2.terms[0].degree;
    Polynomial result;
    result.terms = (Term *)malloc((max_degree + 1) * sizeof(Term));
    result.num_terms = max_degree + 1;

    // 결과 다항식 초기화
    for (int i = 0; i <= max_degree; i++) {
        result.terms[i].degree = max_degree - i;
        result.terms[i].coefficient = 0;
    }

    // 첫 번째 다항식의 항 더하기
    for (int i = 0; i < poly1.num_terms; i++) {
        int deg = poly1.terms[i].degree;
        result.terms[max_degree - deg].coefficient += poly1.terms[i].coefficient;
    }

    // 두 번째 다항식의 항 빼기
    for (int i = 0; i < poly2.num_terms; i++) {
        int deg = poly2.terms[i].degree;
        result.terms[max_degree - deg].coefficient -= poly2.terms[i].coefficient;
    }

    return result;
}

int main() {
    Polynomial poly1, poly2;

    // 첫 번째 다항식 입력
    printf("Enter the number of terms in the first polynomial: ");
    scanf("%d", &poly1.num_terms);
    poly1.terms = (Term *)malloc(poly1.num_terms * sizeof(Term));
    printf("Enter each term's degree and coefficient (highest degree first):\n");
    for (int i = 0; i < poly1.num_terms; i++) {
        printf("Degree: ");
        scanf("%d", &poly1.terms[i].degree);
        printf("Coefficient: ");
        scanf("%d", &poly1.terms[i].coefficient);
    }

    // 두 번째 다항식 입력
    printf("Enter the number of terms in the second polynomial: ");
    scanf("%d", &poly2.num_terms);
    poly2.terms = (Term *)malloc(poly2.num_terms * sizeof(Term));
    printf("Enter each term's degree and coefficient (highest degree first):\n");
    for (int i = 0; i < poly2.num_terms; i++) {
        printf("Degree: ");
        scanf("%d", &poly2.terms[i].degree);
        printf("Coefficient: ");
        scanf("%d", &poly2.terms[i].coefficient);
    }

    // 다항식 덧셈 및 뺄셈
    Polynomial sum = add_polynomials(poly1, poly2);
    Polynomial difference = subtract_polynomials(poly1, poly2);

    // 결과 출력
    printf("First polynomial: ");
    print_polynomial(poly1);

    printf("Second polynomial: ");
    print_polynomial(poly2);

    printf("Sum of polynomials: ");
    print_polynomial(sum);

    printf("Difference of polynomials: ");
    print_polynomial(difference);

    // 동적 메모리 해제
    free(poly1.terms);
    free(poly2.terms);
    free(sum.terms);
    free(difference.terms);

    return 0;
}
