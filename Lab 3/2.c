/*3.2 Aim of the program: Write a menu driven program to sort a list of elements in ascending
order using Quick Sort technique. Each choice for the input data has its own disc file. A separate
output file can be used for sorted elements. After sorting display the content of the output file
along with number of comparisons. Based on the partitioning position for each recursive call,
conclude the input scenario is either best-case partitioning or worst-case partitioning.*/

#include <stdio.h>
#include <stdlib.h>

#define MAX 600

int comparisons = 0;
int best = 1;
int worst = 0;

void swap(int *a, int *b){
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int a[], int low, int high){
    int pivot = a[high];
    int i = low - 1;
    for (int j = low; j < high; j++){
        comparisons++;
        if (a[j] <= pivot){
            i++;
            swap(&a[i], &a[j]);
        }
    }

    swap(&a[i + 1], &a[high]);

    int pos = i + 1;
    int left = pos - low;
    int right = high - pos;

    if (left == 0 || right == 0)
        worst = 1;

    if (abs(left - right) > 1)
        best = 0;

    return pos;
}

void quickSort(int a[], int low, int high){
    if (low < high){
        int p = partition(a, low, high);
        quickSort(a, low, p - 1);
        quickSort(a, p + 1, high);
    }
}

int main(){
    int a[MAX], n = 0, ch;
    char infile[30], outfile[30];

    printf("MAIN MENU (QUICK SORT)\n");
    printf("1. Ascending Data\n");
    printf("2. Descending Data\n");
    printf("3. Random Data\n");
    printf("4. ERROR (EXIT)\n");

    printf("Enter option: ");
    scanf("%d", &ch);

    switch (ch){
    case 1:
        sprintf(infile, "inAsce.dat");
        sprintf(outfile, "outQuickAsce.dat");
        break;

    case 2:
        sprintf(infile, "inDesc.dat");
        sprintf(outfile, "outQuickDesc.dat");
        break;

    case 3:
        sprintf(infile, "inRand.dat");
        sprintf(outfile, "outQuickRand.dat");
        break;

    case 4:
        exit(0);

    default:
        printf("Invalid Choice\n");
        return 0;
    }

    FILE *fp = fopen(infile, "r");

    if (fp == NULL){
        printf("Cannot open input file.\n");
        return 0;
    }

    while (fscanf(fp, "%d", &a[n]) == 1)
        n++;

    fclose(fp);

    printf("\nBefore Sorting:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);

    comparisons = 0;
    best = 1;
    worst = 0;

    quickSort(a, 0, n - 1);

    FILE *fo = fopen(outfile, "w");

    for (int i = 0; i < n; i++)
        fprintf(fo, "%d ", a[i]);

    fclose(fo);

    printf("\n\nAfter Sorting:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);

    printf("\n\nNumber of Comparisons: %d\n", comparisons);

    if (worst)
        printf("Scenario: Worst Case\n");
    else if (best)
        printf("Scenario: Best Case\n");
    else
        printf("Scenario: Average Case\n");

    return 0;
}