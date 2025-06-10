#include <stdio.h>

int main() {
    double a, b;
    char c;
    scanf("%lf %c %lf", &a, &c, &b);
    double result = 0;
    switch (c) {
        case '+':
            result = a + b;
            break;
        case '-':
            result = a - b;
            break;
        case '*':
            result = a * b;
            break;
        case '/':
            result = a / b;
            break;
        default:
            break;
    }
    printf("%.6f", result);
    return 0;
}