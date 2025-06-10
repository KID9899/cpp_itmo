#include <stdio.h>

int main() {
    long long h, m = 0, s = 0, D = 0, M = 0, Y = 0;
    long long delta;
    scanf("%lld:%lld:%lld %lld-%lld-%lld", &h, &m, &s, &D, &M, &Y);
    scanf("%lld", &delta);
    D--;
    M--;
    s += delta;
    if (s >= 60) {
        m += s / 60;
        s %= 60;
    }
    if (m >= 60) {
        h += m / 60;
        m %= 60;
    }
    if (h >= 24) {
        D += h / 24;
        h %= 24;
    }
    while (1) {
        int lim;
        switch (M) {
            case 0:
            case 2:
            case 4:
            case 6:
            case 7:
            case 9:
            case 11:
                lim = 31;
                break;
            case 1:
                if ((Y % 400 == 0) || ((Y % 100 != 0) && (Y % 4 == 0))) {
                    lim = 29;
                } else {
                    lim = 28;
                }
                break;
            default:
                lim = 30;
                break;
        }
        if (D >= lim) {
            D -= lim;
            M += 1;
            if (M >= 12) {
                Y += M/12;
                M %= 12;
            }
        } else {
            break;
        }
    }
    D++;
    M++;
    printf("%02lld:%02lld:%02lld %02lld-%02lld-%04lld", h, m, s, D, M, Y);
}