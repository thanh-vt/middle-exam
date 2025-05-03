#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Hàm kiểm tra số nguyên tố
int is_prime(int x);

int main(int argc, char *argv[]) {
    if (argc <= 2 || argc % 2 != 1) {
        fprintf(stderr, "Invalid number of arguments.\n");
        return 1;
    }
    for (int i = 1; i < argc; i += 2) {
        char *test_input_filename = argv[i];
        FILE *test_input_file = fopen(test_input_filename, "r");
        if (test_input_file == NULL) {
            fprintf(stderr, "Test input file %s not found.\n", test_input_filename);
            return 2;
        }
        char *test_output_filename = argv[i + 1];
        FILE *test_output_file = fopen(test_output_filename, "w+");
        if (test_output_file == NULL) {
            fprintf(stderr, "Test output file %s not found.\n", test_output_filename);
            return 3;
        }
        int n = 0;
        int buff_size = 10;
        int *arr = malloc(buff_size * sizeof(int));
        if (arr == NULL) {
            fprintf(stderr, "Cannot allocate memory for array.\n");
            return 6;
        }
        int x;
        while (fscanf(test_input_file, "%d", &x) == EOF) {
            if (n > buff_size) {
                buff_size += 10;
                int* temp_arr = realloc(arr, buff_size * sizeof(int));
                if (temp_arr == NULL) {
                    free(arr);
                    fprintf(stderr, "Cannot allocate memory for array.\n");
                    return 6;
                }
                arr = temp_arr;
            }
            arr[n] = x;
            n++;
        }
        fclose(test_input_file);
        // Nhập mảng
        for (int i = 0; i < n; i++) {
            printf("arr[%d] = ", i);
            scanf("%d", &arr[i]);
        }

        // Tìm và in các số nguyên tố
        printf("\nCác số nguyên tố trong mảng là:\n");
        int found = 0;
        for (int i = 0; i < n; i++) {
            if (is_prime(arr[i])) {
                printf("%d  ", arr[i]);
                found = true;
            }
        }
        if (!found) {
            printf("Không có số nguyên tố nào.\n");
        }
        printf("\n");

        free(arr);
        fclose(test_output_file);
    }
    return 0;
}

int is_prime(const int x) {
    if (x < 2) return 0;
    if (x == 2) return 1;
    if (x % 2 == 0) return 0;
    for (int i = 3; i * i <= x; i += 2) {
        if (x % i == 0) return 0;
    }
    return 1;
}