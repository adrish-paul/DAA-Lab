/*
Aim of the program: Write a program in C to convert the first 'n' decimal numbers of a disc
file to binary using recursion. Store the binary value in a separate disc file.
Note# Read the value of 'n', source file name and destination file name from command line
arguments. Display the decimal numbers and their equivalent binary numbers from the output file.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void decToBin(int num, int bits, FILE *out) {
    if (bits > 1) {
        decToBin(num >> 1, bits - 1, out);
    }
    fprintf(out, "%d", num & 1);
}

int main(int argc, char *argv[]) {
    clock_t start = clock();

    int n = 150;
    const char *src = "inDec.dat";
    const char *dest = "outBin.dat";

    if (argc >= 4) {
        n = atoi(argv[1]);
        src = argv[2];
        dest = argv[3];
    }

    FILE *fin = fopen(src, "r");
    if (fin == NULL) {
        printf("Error: Cannot open source file '%s'.\n", src);
        return 1;
    }

    FILE *fout = fopen(dest, "w");
    if (fout == NULL) {
        printf("Error: Cannot open destination file '%s'.\n", dest);
        fclose(fin);
        return 1;
    }

    int num;
    int count = 0;

    while (count < n && fscanf(fin, "%d", &num) == 1) {
        fprintf(fout, "The binary equivalent of %d is ", num);
        decToBin(num, 16, fout);
        fprintf(fout, "\n");
        count++;
    }

    fclose(fin);
    fclose(fout);

    FILE *fout_read = fopen(dest, "r");
    if (fout_read != NULL) {
        char line[256];
        while (fgets(line, sizeof(line), fout_read) != NULL) {
            printf("%s", line);
        }
        fclose(fout_read);
    }

    clock_t end = clock();
    double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\nCPU Time Used: %f seconds\n", cpu_time_used);

    return 0;
}