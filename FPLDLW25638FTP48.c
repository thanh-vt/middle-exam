#include <stdio.h>
#include <stdlib.h>

int calculate_total_seconds(int hours, int minutes, int seconds);

/*
 * Test cases run command
 * Windows: .\FPLDLW25638FTP48.exe 1 2 3
 * Linux: ./FPLDLW25638FTP48 1 2 3
*/
int main(int argc, char * argv[]) {
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
    for (int i = 1; i < argc; i ++) {
        int test_case_number = test_cases[i - 1];
        char test_input_filename[24];
        sprintf(test_input_filename, "FPLDLW25638FTP48IN%02d.txt", test_case_number);
        FILE* test_input_file = fopen(test_input_filename, "r");
        if (test_input_file == NULL) {
            fprintf(stderr, "Test input file %s not found.\n", test_input_filename);
            return 2;
        }
        char test_output_filename[25];
        sprintf(test_output_filename, "FPLDLW25638FTP48OUT%02d.txt", test_case_number);
        FILE* test_output_file = fopen(test_output_filename, "w+");
        if (test_output_file == NULL) {
            fprintf(stderr, "Test output file %s not found.\n", test_output_filename);
            return 3;
        }
        int hours, minutes, seconds;
        if (fscanf(test_input_file, "%d:%d:%d", &hours, &minutes, &seconds) == EOF) {
            fprintf(stderr, "Invalid input format.\n");
            return 4;
        }
        fclose(test_input_file);
        int total_seconds = calculate_total_seconds(hours, minutes, seconds);
        fprintf(test_output_file, "%d", total_seconds);
        fclose(test_output_file);
    }
    free(test_cases);
    return 0;
}

int calculate_total_seconds(const int hours, const int minutes, const int seconds) {
    return hours * 3600 + minutes * 60 + seconds;
}