#include <math.h>
#include <stdio.h>

void print_binary(int x, FILE *output_file, int* padding_size);

/*
 * Test cases run command
 * Windows: .\FPLDLW25638FTP90.exe FPLDLW25638FTP90IN01.txt FPLDLW25638FTP90OUT01.txt FPLDLW25638FTP90IN02.txt FPLDLW25638FTP90OUT02.txt FPLDLW25638FTP90IN03.txt FPLDLW25638FTP90OUT03.txt
 * Linux: ./FPLDLW25638FTP90 FPLDLW25638FTP90IN01.txt FPLDLW25638FTP90OUT01.txt FPLDLW25638FTP90IN02.txt FPLDLW25638FTP90OUT02.txt FPLDLW25638FTP90IN03.txt FPLDLW25638FTP90OUT03.txt
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
        int n;
        if (fscanf(test_input_file, "%d", &n) == EOF) {
            fprintf(stderr, "Invalid input format.\n");
            return 4;
        }
        fclose(test_input_file);
        for (int j = 1; j <= n; j++) {
            int padding_size = 32; // INT_MAX = 4294967295 = 11111111111111111111111111111111b => 32 binary digits
            print_binary(j, test_output_file, &padding_size);
            fprintf(test_output_file, "\n");
        }
        fclose(test_output_file);
    }
}

void print_binary(const int x, FILE *output_file, int* padding_size) {
    if (x > 1) {
        *padding_size -= 1;
        print_binary(x / 2, output_file, padding_size);
    } else {
        for (int i = 0; i < *padding_size; i++) {
            fprintf(output_file, "0");
        }
    }
    fprintf(output_file, "%c", x % 2 + '0');
}
