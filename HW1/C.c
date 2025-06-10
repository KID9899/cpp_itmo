#include <stdio.h>

int main() {
    long long s = 0;
    while (1) {
        int x;
        if (scanf("%d", &x) == 1) {
            s += x;
        } else {
            break;
        }
    }
    printf("%lld", s);
}