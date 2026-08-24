/*3.1 Aim of the program: Write a menu driven program to sort list of array elements using Merge
Sort technique and calculate the execution time only to sort the elements. Count the number of
comparisons.*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 600

int comparisons = 0;

void merge(int arr[], int low, int mid, int high){
    int i = low, j = mid + 1, k = 0;
    int temp[MAX];

    while (i <= mid && j <= high){
        comparisons++;
        if (arr[i] <= arr[j])
            temp[k++] = arr[i++];
        else
            temp[k++] = arr[j++];
    }

    while (i <= mid)
        temp[k++] = arr[i++];

    while (j <= high)
        temp[k++] = arr[j++];

    for (i = low, k = 0; i <= high; i++, k++)
        arr[i] = temp[k];
}

void mergeSort(int arr[], int low, int high){
    if (low < high){
        int mid = (low + high) / 2;

        mergeSort(arr, low, mid);
        mergeSort(arr, mid + 1, high);
        merge(arr, low, mid, high);
    }
}

int main(){
    int arr[MAX], n = 0;
    int choice, i;
    char inputFile[30], outputFile[30];

    printf("MAIN MENU (MERGE SORT)\n");
    printf("1. Ascending Data\n");
    printf("2. Descending Data\n");
    printf("3. Random Data\n");
    printf("4. Exit\n");

    printf("Enter option: ");
    scanf("%d", &choice);

    switch (choice){
    case 1:
        sprintf(inputFile, "inAsce.dat");
        sprintf(outputFile, "outMergeAsce.dat");
        break;

    case 2:
        sprintf(inputFile, "inDesc.dat");
        sprintf(outputFile, "outMergeDesc.dat");
        break;

    case 3:
        sprintf(inputFile, "inRand.dat");
        sprintf(outputFile, "outMergeRand.dat");
        break;

    case 4:
        exit(0);

    default:
        printf("Invalid Choice!\n");
        return 0;
    }

    FILE *fp = fopen(inputFile, "r");

    if (fp == NULL){
        printf("Cannot open input file.\n");
        return 0;
    }

    while (fscanf(fp, "%d", &arr[n]) == 1)
        n++;

    fclose(fp);

    printf("\nBefore Sorting:\n");
    for (i = 0; i < n; i++)
        printf("%d ", arr[i]);

    comparisons = 0;

    clock_t start = clock();
    mergeSort(arr, 0, n - 1);
    clock_t end = clock();

    FILE *fo = fopen(outputFile, "w");

    for (i = 0; i < n; i++)
        fprintf(fo, "%d ", arr[i]);

    fclose(fo);

    printf("\n\nAfter Sorting:\n");
    for (i = 0; i < n; i++)
        printf("%d ", arr[i]);

    double time_taken = (double)(end - start) / CLOCKS_PER_SEC;

    printf("\n\nNumber of Comparisons: %d", comparisons);
    printf("\nExecution Time: %.0f nanoseconds\n", time_taken);

    return 0;
}