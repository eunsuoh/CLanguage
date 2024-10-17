#include <stdio.h>

// Quiet speaking advice function
void quiet_speaking_advice(int speaking_volume) {
    if (speaking_volume > 70) {
        printf("Your speaking volume is too high! Please speak more quietly.\n");
    } else if (speaking_volume > 50) {
        printf("Try lowering your voice a bit.\n");
    } else {
        printf("Good! You are speaking at the perfect volume.\n");
    }
}

int main() {
    int user_volume;

    // Input speaking volume
    printf("Enter speaking volume (0-100): ");
    scanf("%d", &user_volume);

    // Call quiet speaking advice function
    quiet_speaking_advice(user_volume);

    return 0;
}
