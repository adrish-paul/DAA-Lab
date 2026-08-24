/*WAP to read n integers from a disc file that must contain some duplicate values and store them into an array. Perform the following operations: 
a. find out the total number of duplicate elements.
b. find the most repeating element in the array*/

#include <stdio.h>
#include <time.h>

int main() {
    clock_t start = clock();
    int arr[100], n = 0, i, j, duplicates = 0, most_repeating, max_count = 0;

    FILE *fp = fopen("numbers.txt", "r");
    while (fscanf(fp, "%d", &arr[n]) == 1) {
        n++;
    }
    fclose(fp);

    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            if (arr[i] == arr[j]) {
                duplicates++;
                break;
            }
        }
    }

    most_repeating = arr[0];
    for (i = 0; i < n; i++) {
        int count = 0;
        for (j = 0; j < n; j++) {
            if (arr[i] == arr[j]) count++;
        }
        if (count > max_count) {
            max_count = count;
            most_repeating = arr[i];
        }
    }

    printf("Total duplicate elements: %d\n", duplicates);
    printf("Most repeating element: %d\n", most_repeating);

    clock_t end = clock();
    double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("CPU Time Used: %f seconds\n", cpu_time_used);

    return 0;
}