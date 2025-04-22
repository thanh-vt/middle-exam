#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n, m;
    scanf("%d %d", &n, &m);
    int **matrix = malloc(m * sizeof(int *));
    if (matrix == NULL) {
        fprintf(stderr, "Cannot allocate memory for row pointer.\n");
        return 1;
    }
    for (int i = 0; i < n; i++) {
        matrix[i] = malloc(n * sizeof(int));
        if (matrix[i] == NULL) {
            fprintf(stderr, "Cannot allocate memory for column %d pointer.\n", i);
            // Giải phóng bộ nhớ đã cấp phát trước đó
            for (int j = 0; j < i; j++) {
                free(matrix[j]);
            }
            free(matrix);
            return 1;
        }
    }
    // Nhập giá trị cho ma trận
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    // In ma trận
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }

    // Giải phóng bộ nhớ
    for (int i = 0; i < m; i++) {
        free(matrix[i]);
    }
    free(matrix);
    return 0;
}
