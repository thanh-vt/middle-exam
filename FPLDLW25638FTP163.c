#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int **alloc_matrix(int n, int m);

int **alloc_matrix(int n, int m);

bool is_identity_block_left(int **A, int n, int m);

void free_matrix(int **M, int n);

int main() {
    int n, m;
    printf("Nhập số hàng n: ");
    scanf("%d", &n);
    printf("Nhập số cột m: ");
    scanf("%d", &m);

    // Cấp phát ma trận
    int **A = alloc_matrix(n, m);
    if (!A) {
        fprintf(stderr, "Cấp phát bộ nhớ thất bại.\n");
        return 1;
    }

    // Nhập giá trị ma trận
    printf("Nhập ma trận A (%d x %d):\n", n, m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("A[%d][%d] = ", i, j);
            scanf("%d", &A[i][j]);
        }
    }

    // Kiểm tra
    if (is_identity_block_left(A, n, m)) {
        printf("\nMa trận A đúng là ghép I_%d bên trái với một ma trận P.\n", n);
    } else {
        printf("\nMa trận A KHÔNG phải là ghép I_%d bên trái với một ma trận P.\n", n);
    }

    free_matrix(A, n);
    return 0;
}

// Hàm cấp phát động một ma trận n x m
int **alloc_matrix(int n, int m) {
    int **M = malloc(n * sizeof(int*));
    if (!M) return NULL;
    for (int i = 0; i < n; i++) {
        M[i] = malloc(m * sizeof(int));
        if (!M[i]) return NULL;
    }
    return M;
}

// Hàm giải phóng ma trận n x m
void free_matrix(int **M, int n) {
    for (int i = 0; i < n; i++) {
        free(M[i]);
    }
    free(M);
}

// Hàm kiểm tra A có phải [I | P] không
bool is_identity_block_left(int **A, int n, int m) {
    // Điều kiện tối thiểu: phải có m >= n (để ghép I_n bên trái)
    if (m < n) return false;

    // Kiểm tra khối I_n ở cột 0..n-1
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int expected = (i == j) ? 1 : 0;
            if (A[i][j] != expected) {
                return false;
            }
        }
    }

    // Phần P ở cột n..m-1 thì không cần kiểm tra gì thêm (bất kỳ giá trị nào cũng được)
    return true;
}
