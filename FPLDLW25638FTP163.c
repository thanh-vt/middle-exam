#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_identity_block_left(int **A, int n, int m);

/*
 * Test cases run command
 * Windows: .\FPLDLW25638FTP163.exe FFPLDLW25638FTP163IN01.txt FPLDLW25638FTP163OUT01.txt FPLDLW25638FTP163IN02.txt FPLDLW25638FTP163OUT02.txt FPLDLW25638FTP163IN03.txt FPLDLW25638FTP163OUT03.txt
 * Linux: ./FPLDLW25638FTP163 FFPLDLW25638FTP163IN01.txt FPLDLW25638FTP163OUT01.txt FPLDLW25638FTP163IN02.txt FPLDLW25638FTP163OUT02.txt FPLDLW25638FTP163IN03.txt FPLDLW25638FTP163OUT03.txt
*/
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
        int **matrix = NULL;
        int rows = 0;
        int cols = 0;
        char line[1000]; // max 1000 chars

        while (fgets(line, sizeof(line), test_input_file)) {
            int *row = NULL;
            int count = 0;
            char *token = strtok(line, " \t\n");

            // Count numbers of columns
            while (token) {
                int *tmp_row = realloc(row, (count + 1) * sizeof(int));
                if (tmp_row == NULL) {
                    fprintf(stderr, "Memory allocation failed");
                    return 1;
                }
                row = tmp_row;
                char *end_ptr;
                int value = (int) strtol(token, &end_ptr, 10);
                if (end_ptr == token) {
                    fprintf(stderr, "No digits were found.\n");
                } else if (*end_ptr != '\0') {
                    fprintf(stderr, "Invalid character: %c\n", *end_ptr);
                }
                row[count++] = value;
                token = strtok(NULL, " \t\n");
            }

            if (cols == 0) {
                cols = count;
            } else if (count != cols) {
                fprintf(stderr, "Inconsistent number of columns in row %d\n", rows + 1);
                return 1;
            }

            matrix = realloc(matrix, (rows + 1) * sizeof(int *));
            if (matrix == NULL) {
                fprintf(stderr, "Memory allocation failed");
                return 1;
            }
            matrix[rows++] = row;
        }
        if (matrix == NULL) {
            fprintf(stderr, "Memory allocation failed");
            return 1;
        }
        fclose(test_input_file);

        // Kiểm tra
        fprintf(test_output_file, "%d", is_identity_block_left(matrix, cols, rows));

        // free matrix
        for (int j = 0; j < rows; ++j) {
            free(matrix[j]);
        }
        free(matrix);
        fclose(test_output_file);
    }

    return 0;
}

// Hàm kiểm tra A có phải [I | P] không
int is_identity_block_left(int **A, int n, int m) {
    // Điều kiện tối thiểu: phải có m >= n (để ghép I_n bên trái)
    if (m < n) return 0;

    // Kiểm tra khối I_n ở cột 0..n-1
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int expected = (i == j) ? 1 : 0;
            if (A[i][j] != expected) {
                return 0;
            }
        }
    }

    // Phần P ở cột n..m-1 thì không cần kiểm tra gì thêm (bất kỳ giá trị nào cũng được)
    return 1;
}
