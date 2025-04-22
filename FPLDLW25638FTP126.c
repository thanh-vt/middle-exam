#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Hàm kiểm tra số nguyên tố
bool isPrime(int x);

int main() {
    int n;
    printf("Nhập số lượng phần tử của mảng: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Vui lòng nhập số nguyên dương.\n");
        return 1;
    }

    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        fprintf(stderr, "Không thể cấp phát bộ nhớ.\n");
        return 1;
    }

    // Nhập mảng
    printf("Nhập %d phần tử:\n", n);
    for (int i = 0; i < n; i++) {
        printf("arr[%d] = ", i);
        scanf("%d", &arr[i]);
    }

    // Tìm và in các số nguyên tố
    printf("\nCác số nguyên tố trong mảng là:\n");
    bool found = false;
    for (int i = 0; i < n; i++) {
        if (isPrime(arr[i])) {
            printf("%d  ", arr[i]);
            found = true;
        }
    }
    if (!found) {
        printf("Không có số nguyên tố nào.\n");
    }
    printf("\n");

    free(arr);
    return 0;
}

bool isPrime(int x) {
    if (x < 2) return false;
    if (x == 2) return true;
    if (x % 2 == 0) return false;
    for (int i = 3; i * i <= x; i += 2) {
        if (x % i == 0) return false;
    }
    return true;
}