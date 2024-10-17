#include <stdio.h>

int main() {
    int a;
    unsigned int b;
    short int c;
    long int d;
    long long int e;
    unsigned long long int f;
    float g;
    double h;
    long double i;
    char j;
    char str[100];
    void *ptr;

    // 정수형 입력 받기
    printf("Enter an integer (int): ");
    scanf("%d", &a);

    printf("Enter an unsigned integer (unsigned int): ");
    scanf("%u", &b);

    printf("Enter a short integer (short int): ");
    scanf("%hd", &c);

    printf("Enter a long integer (long int): ");
    scanf("%ld", &d);

    printf("Enter a long long integer (long long int): ");
    scanf("%lld", &e);

    printf("Enter an unsigned long long integer (unsigned long long int): ");
    scanf("%llu", &f);

    // 실수형 입력 받기
    printf("Enter a float: ");
    scanf("%f", &g);

    printf("Enter a double: ");
    scanf("%lf", &h);

    printf("Enter a long double: ");
    scanf("%Lf", &i);

    // 문자와 문자열 입력 받기
    printf("Enter a character: ");
    scanf(" %c", &j);  // 공백 문자는 무시

    printf("Enter a string: ");
    scanf("%s", str);

    // 포인터 입력 받기 (예: 변수의 주소)
    ptr = &a;
    printf("Address of 'a' stored in pointer: %p\n", ptr);

    // 출력
    printf("\nYou entered:\n");
    printf("int: %d\n", a);
    printf("unsigned int: %u\n", b);
    printf("short int: %hd\n", c);
    printf("long int: %ld\n", d);
    printf("long long int: %lld\n", e);
    printf("unsigned long long int: %llu\n", f);
    printf("float: %.2f\n", g);
    printf("double: %.2lf\n", h);
    printf("long double: %.2Lf\n", i);
    printf("character: %c\n", j);
    printf("string: %s\n", str);
    printf("Pointer (address of 'a'): %p\n", ptr);

    return 0;
}
