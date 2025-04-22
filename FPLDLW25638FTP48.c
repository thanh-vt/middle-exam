#include <stdio.h>

int main() {
    int hours, minutes, seconds;

    // Nhập giờ, phút, giây
    printf("Nhập giờ: ");
    if (scanf("%d", &hours) != 1 || hours < 0) {
        printf("Giá trị giờ không hợp lệ.\n");
        return 1;
    }

    printf("Nhập phút: ");
    if (scanf("%d", &minutes) != 1 || minutes < 0 || minutes >= 60) {
        printf("Giá trị phút không hợp lệ (0-59).\n");
        return 1;
    }

    printf("Nhập giây: ");
    if (scanf("%d", &seconds) != 1 || seconds < 0 || seconds >= 60) {
        printf("Giá trị giây không hợp lệ (0-59).\n");
        return 1;
    }

    // Tính tổng số giây
    long total_seconds = (long) hours * 3600 + (long) minutes * 60 + seconds;

    // In kết quả
    printf("\nTổng số giây tương ứng: %ld giây\n", total_seconds);

    return 0;
}