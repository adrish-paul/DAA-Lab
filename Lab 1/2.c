// Given an array arr[] of size n, find the prefix sum of the array. A prefix sum array prefixSum[] of the same size, such that the value of the prefixSum[i] is arr[0] + arr[1] + ... + arr[i]

#include <stdio.h>
#include <time.h>

int main() {
    clock_t start = clock();
    int arr[100], prefixSum[100], n = 0, i;

    FILE *fp = fopen("numbers.txt", "r");
    while (fscanf(fp, "%d", &arr[n]) == 1) {
        n++;
    }
    fclose(fp);

    prefixSum[0] = arr[0];
    for (i = 1; i < n; i++) {
        prefixSum[i] = prefixSum[i - 1] + arr[i];
    }

    printf("Original array: ");
    for (i = 0; i < n; i++){
        printf("%d ", arr[i]);
    }
    printf("\nPrefix sum array: ");
    for (i = 0; i < n; i++){
        printf("%d ", prefixSum[i]);
    }
    printf("\n");

    clock_t end = clock();
    double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("CPU Time Used: %f seconds\n", cpu_time_used);

    return 0;
}