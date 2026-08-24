/*
Aim of the program: Write a program in C to find GCD of two numbers using recursion.
Read all pair of numbers from a file and store the result in a separate file.
Source file name and destination file name taken from command line arguments (with automatic defaults if omitted).
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int main(int argc, char *argv[]) {
    clock_t start = clock();
    const char *src = "inGcd.dat";
    const char *dest = "outGcd.dat";

    if (argc >= 3) {
        src = argv[1];
        dest = argv[2];
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

    int num1, num2;
    while (fscanf(fin, "%d %d", &num1, &num2) == 2) {
        int result = gcd(num1, num2);
        fprintf(fout, "The GCD of %d and %d is %d\n", num1, num2, result);
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
    printf("CPU Time Used: %f seconds\n", cpu_time_used);

    return 0;
}
