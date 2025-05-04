#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
        char line[1000];

        while (fgets(line, sizeof(line), test_input_file)) {
            int *row = NULL;
            int value;
            int count = 0;
            char *token = strtok(line, " \t\n");

            // Count number of columns
            while (token) {
                row = realloc(row, (count + 1) * sizeof(int));
                if (!row) {
                    perror("Memory allocation failed");
                    return 1;
                }
                value = atoi(token);
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
            if (!matrix) {
                perror("Memory allocation failed");
                return 1;
            }
            matrix[rows++] = row;
        }
        fclose(test_input_file);

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                fprintf(test_output_file, "%d ", matrix[i][j]);
            }
            fprintf(test_output_file, "\n");
            free(matrix[i]); // Free each row after printing
        }
        free(matrix); // Free the matrix array
        fclose(test_output_file);
    }
    return 0;
}
