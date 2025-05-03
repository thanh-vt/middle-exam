#include <stdio.h>

int calculate_total_seconds(int hours, int minutes, int seconds);

/*
 * Test cases run command
 * Windows: .\FPLDLW25638FTP48.exe FFPLDLW25638FTP48IN01.txt FPLDLW25638FTP48OUT01.txt FPLDLW25638FTP48IN02.txt FPLDLW25638FTP48OUT02.txt FPLDLW25638FTP48IN03.txt FPLDLW25638FTP48OUT03.txt
 * Linux: ./FPLDLW25638FTP48 FFPLDLW25638FTP48IN01.txt FPLDLW25638FTP48OUT01.txt FPLDLW25638FTP48IN02.txt FPLDLW25638FTP48OUT02.txt FPLDLW25638FTP48IN03.txt FPLDLW25638FTP48OUT03.txt
*/
int main(int argc, char * argv[]) {
    if (argc <= 2 || argc % 2 != 1) {
        fprintf(stderr, "Invalid number of arguments.\n");
        return 1;
    }
    for (int i = 1; i < argc; i += 2) {
        char* test_input_filename = argv[i];
        FILE* test_input_file = fopen(test_input_filename, "r");
        if (test_input_file == NULL) {
            fprintf(stderr, "Test input file %s not found.\n", test_input_filename);
            return 2;
        }
        char* test_output_filename = argv[i + 1];
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
    return 0;
}

int calculate_total_seconds(const int hours, const int minutes, const int seconds) {
    return hours * 3600 + minutes * 60 + seconds;
}