#include <stdio.h>
#include <stdlib.h>

int is_prime(int x);

/*
 * Test cases run command
 * Windows: .\FPLDLW25638FTP126.exe 1 2 3
 * Linux: ./FPLDLW25638FTP126 1 2 3
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
        sprintf(test_input_filename, "FPLDLW25638FTP126IN%02d.txt", test_case_number);
        FILE *test_input_file = fopen(test_input_filename, "r");
        if (test_input_file == NULL) {
            fprintf(stderr, "Test input file %s not found.\n", test_input_filename);
            return 2;
        }
        char test_output_filename[25];
        sprintf(test_output_filename, "FPLDLW25638FTP126OUT%02d.txt", test_case_number);
        FILE *test_output_file = fopen(test_output_filename, "w+");
        if (test_output_file == NULL) {
            fprintf(stderr, "Test output file %s not found.\n", test_output_filename);
            return 3;
        }
        int n = 0; // current index
        int buff_size = 10;
        int *arr = malloc(buff_size * sizeof(int));
        if (arr == NULL) {
            fprintf(stderr, "Cannot allocate memory for array.\n");
            return 6;
        }
        int x;
        while (fscanf(test_input_file, "%d ", &x) != EOF) {
            if (n >= buff_size) {
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

        for (int j = 0; j < n; j++) {
            if (is_prime(arr[j])) {
                fprintf(test_output_file, "%8d ", arr[j]);
            }
        }

        free(arr);
        fclose(test_output_file);
    }
    free(test_cases);
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