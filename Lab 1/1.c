//Wap to find the second smallest and the second largest element of an array of n integers.

#include <stdio.h>
#include <time.h>

int main() {
    clock_t start = clock();
    int a[100], n = 0, i, j, temp;

    FILE *fp = fopen("numbers.txt", "r");
    while (fscanf(fp, "%d", &a[n]) == 1) {
        n++;
    }
    fclose(fp);

    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (a[j] > a[j + 1]) {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }

    int sec_smallest = a[0], sec_largest = a[n - 1];
    for (i = 0; i < n; i++) {
        if (a[i] > a[0]) {
            sec_smallest = a[i];
            break;
        }
    }
    for (i = n - 1; i >= 0; i--) {
        if (a[i] < a[n - 1]) {
            sec_largest = a[i];
            break;
        }
    }

    printf("Second smallest element: %d\n", sec_smallest);
    printf("Second largest element: %d\n", sec_largest);

    clock_t end = clock();
    double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("CPU Time Used: %f seconds\n", cpu_time_used);

    return 0;
}
