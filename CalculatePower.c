#include <stdio.h>

// 밑(base)의 지수(exponent) 제곱을 재귀적으로 계산하는 함수
int calculate_power(int base, int exponent){
    if (exponent == 0)
        return 1;
    return base * calculate_power(base, exponent - 1);
}

int main(){
    int base, exponent;

    // 사용자로부터 base(밑)와 exponent(지수)를 입력받음
    printf("Enter the base: ");
    scanf("%d", &base);

    printf("Enter the exponent: ");
    scanf("%d", &exponent);

    // calculate_power 함수를 사용하여 base^exponent 계산
    printf("%d^%d is %d\n", base, exponent, calculate_power(base, exponent));
    
    return 0;
}
