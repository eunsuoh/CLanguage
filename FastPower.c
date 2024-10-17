#include <stdio.h>

// 빠른 거듭제곱을 재귀적으로 계산하는 함수
int fast_power(int base, int exponent){
    printf("exponent = %d\n", exponen3t);  // 현재 지수 값 출력

    if (exponent == 0)
        return 1;
    else if (exponent % 2 == 0)
        return fast_power(base * base, exponent / 2);  // 지수가 짝수일 때
    else
        return base * fast_power(base * base, (exponent - 1) / 2);  // 지수가 홀수일 때
}

int main(){
    int base, exponent;

    // 사용자로부터 base(밑)와 exponent(지수)를 입력받음
    printf("Enter the base: ");
    scanf("%d", &base);

    printf("Enter the exponent: ");
    scanf("%d", &exponent);

    // fast_power 함수를 사용하여 base^exponent 계산
    printf("%d^%d is %d\n", base, exponent, fast_power(base, exponent));
    
    return 0;
}
