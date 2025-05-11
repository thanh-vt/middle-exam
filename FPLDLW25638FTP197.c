#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Test cases run command
 * Windows: .\FPLDLW25638FTP197.exe 1 2 3
 * Linux: ./FPLDLW25638FTP197 1 2 3
*/
int main(int argc, char *argv[]) {
    int* test_cases;
    if (argc <= 1) {
        fprintf(stderr, "No test cases provided, use default test cases: [01,02,03].\n");
        test_cases = calloc(3, sizeof(int));
        test_cases[0] = 1;
        test_cases[1] = 2;
        test_cases[2] = 3;
    } else {
        test_cases = calloc(argc - 1, sizeof(int));
        int x;
        for (int i = 1; i < argc; i++) {
            if (sscanf(argv[i], "%d", &x) == EOF) {
                fprintf(stderr, "Test case must be a number.\n");
                return 1;
            }
            if (x >= 100 || x <= 0) {
                fprintf(stderr, "Test case number min = 1, max = 99.\n");
                return 1;
            }
            test_cases[i - 1] = x;
        }
    }
    for (int i = 1; i < argc; i++) {
        int test_case_number = test_cases[i - 1];
        char test_input_filename[24];
        sprintf(test_input_filename, "FPLDLW25638FTP197IN%02d.txt", test_case_number);
        FILE *test_input_file = fopen(test_input_filename, "r");
        if (test_input_file == NULL) {
            fprintf(stderr, "Test input file %s not found.\n", test_input_filename);
            return 2;
        }
        char test_output_filename[25];
        sprintf(test_output_filename, "FPLDLW25638FTP197OUT%02d.txt", test_case_number);
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
                    fprintf(stderr,  "Invalid character: %c\n", *end_ptr);
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

        for (int j = 0; j < rows; ++j) {
            for (int k = 0; k < cols; ++k) {
                fprintf(test_output_file, "%8d ", matrix[j][k]); // padding fill 8 digits
            }
            fprintf(test_output_file, "\n");
            free(matrix[j]);
        }
        free(matrix);
        fclose(test_output_file);
    }
    free(test_cases);
    return 0;
}
