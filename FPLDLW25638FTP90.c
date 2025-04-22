#include <stdio.h>

void printBinary(int x);

int main() {
    int n;
    if (scanf("%d", &n) != 1 || n < 1) {
        printf("Vui lòng nhập số nguyên dương.\n");
        return 1;
    }

    printf("Bảng nhị phân từ 1 đến %d:\n", n);
    for (int i = 1; i <= n; i++) {
        printBinary(i);
        putchar('\n');
    }

    return 0;
}

void printBinary(int x) {
    if (x > 1) {
        printBinary(x / 2);
    }
    putchar((x % 2) + '0');
}