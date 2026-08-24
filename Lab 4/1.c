#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct person {
    int id, age, height, weight;
    char *name;
};

void swap(struct person *a, struct person *b) {
    struct person t = *a;
    *a = *b;
    *b = t;
}

void minHeapify(struct person a[], int n, int i) {
    int s = i, l = 2*i+1, r = 2*i+2;

    if (l < n && a[l].age < a[s].age) s = l;
    if (r < n && a[r].age < a[s].age) s = r;

    if (s != i) {
        swap(&a[i], &a[s]);
        minHeapify(a, n, s);
    }
}

void createMinHeap(struct person a[], int n) {
    for (int i = n/2-1; i >= 0; i--)
        minHeapify(a, n, i);
}

void maxHeapify(struct person a[], int n, int i) {
    int lrg = i, l = 2*i+1, r = 2*i+2;

    if (l < n && a[l].weight > a[lrg].weight) lrg = l;
    if (r < n && a[r].weight > a[lrg].weight) lrg = r;

    if (lrg != i) {
        swap(&a[i], &a[lrg]);
        maxHeapify(a, n, lrg);
    }
}

void createMaxHeap(struct person a[], int n) {
    for (int i = n/2-1; i >= 0; i--)
        maxHeapify(a, n, i);
}

void insert(struct person a[], int *n, struct person p) {
    int i = (*n)++;
    a[i] = p;

    while (i && a[(i-1)/2].age > a[i].age) {
        swap(&a[i], &a[(i-1)/2]);
        i = (i-1)/2;
    }
}

void display(struct person a[], int n) {
    printf("\nId\tName\tAge\tHeight\tWeight\n");

    for (int i = 0; i < n; i++)
        printf("%d\t%s\t%d\t%d\t%d\n",
               a[i].id, a[i].name, a[i].age,
               a[i].height, a[i].weight);
}

int main() {
    FILE *f = fopen("students.txt", "r");
    struct person *p, *minHeap, *maxHeap;
    int n, minN, maxN, ch;

    if (!f) return 1;

    fscanf(f, "%d", &n);

    p = malloc((n+10) * sizeof(struct person));
    minHeap = malloc((n+10) * sizeof(struct person));
    maxHeap = malloc((n+10) * sizeof(struct person));

    for (int i = 0; i < n; i++) {
        char s[50];

        fscanf(f, "%d %s %d %d %d",
               &p[i].id, s, &p[i].age,
               &p[i].height, &p[i].weight);

        p[i].name = malloc(strlen(s)+1);
        strcpy(p[i].name, s);

        minHeap[i] = p[i];
        maxHeap[i] = p[i];
    }

    fclose(f);
    minN = maxN = n;

    do {
        printf("\nMAIN MENU (HEAP)\n");
        printf("1. Read Data\n");
        printf("2. Create a Min-heap based on the age\n");
        printf("3. Create a Max-heap based on the weight\n");
        printf("4. Display weight of the youngest person\n");
        printf("5. Insert a new person into the Min-heap\n");
        printf("6. Delete the oldest person\n");
        printf("7. Exit\n");
        printf("Enter option: ");
        scanf("%d", &ch);

        clock_t start = clock();

        switch (ch) {

        case 1:
            display(p, n);
            break;

        case 2:
            createMinHeap(minHeap, minN);
            display(minHeap, minN);
            break;

        case 3:
            createMaxHeap(maxHeap, maxN);
            display(maxHeap, maxN);
            break;

        case 4:
            createMinHeap(minHeap, minN);
            printf("Weight of youngest student: %.2f kg\n",
                   minHeap[0].weight * 0.453592);
            break;

        case 5: {
            struct person x;
            char s[50];

            printf("Enter id name age height weight: ");
            scanf("%d %s %d %d %d",
                  &x.id, s, &x.age, &x.height, &x.weight);

            x.name = malloc(strlen(s)+1);
            strcpy(x.name, s);

            insert(minHeap, &minN, x);
            break;
        }

        case 6: {
            int pos = 0;

            /* Find oldest person */
            for (int i = 1; i < minN; i++)
                if (minHeap[i].age > minHeap[pos].age)
                    pos = i;

            printf("Deleted: %s\n", minHeap[pos].name);

            minHeap[pos] = minHeap[--minN];
            minHeapify(minHeap, minN, pos);
            break;
        }

        case 7:
            break;

        default:
            printf("Invalid option!\n");
        }

        clock_t end = clock();
        printf("Time: %f seconds\n",
               (double)(end-start) / CLOCKS_PER_SEC);

    } while (ch != 7);

    return 0;
}