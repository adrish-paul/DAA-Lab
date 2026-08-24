/*5.1 Aim of the program: Write a program to find the maximum profit nearest to but not
exceeding the given knapsack capacity using the Fractional Knapsack algorithm.*/

#include <stdio.h>
#include <time.h>

struct ITEM
{
    int item_id;
    float item_profit;
    float item_weight;
    float profit_weight_ratio;
};

typedef struct ITEM ITEM;

void swap(ITEM *a, ITEM *b)
{
    ITEM temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(ITEM items[], int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n &&
        items[left].profit_weight_ratio >
        items[largest].profit_weight_ratio)
    {
        largest = left;
    }

    if (right < n &&
        items[right].profit_weight_ratio >
        items[largest].profit_weight_ratio)
    {
        largest = right;
    }

    if (largest != i)
    {
        swap(&items[i], &items[largest]);
        heapify(items, n, largest);
    }
}

void heapSort(ITEM items[], int n)
{
    int i;

    for (i = n / 2 - 1; i >= 0; i--)
    {
        heapify(items, n, i);
    }

    for (i = n - 1; i > 0; i--)
    {
        swap(&items[0], &items[i]);
        heapify(items, i, 0);
    }
}

int main()
{
    int n, i;
    float capacity;
    float remaining_capacity;
    float max_profit = 0.0;

    clock_t start, end;
    double cpu_time_used;

    ITEM items[100];

    start = clock();

    printf("Enter the number of items: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++)
    {
        items[i].item_id = i + 1;

        printf("Enter the profit and weight of item no %d: ",
               items[i].item_id);

        scanf("%f %f",
              &items[i].item_profit,
              &items[i].item_weight);

        items[i].profit_weight_ratio =
            items[i].item_profit / items[i].item_weight;
    }

    printf("Enter the capacity of knapsack: ");
    scanf("%f", &capacity);

    heapSort(items, n);
    remaining_capacity = capacity;

    printf("\nItem No\tProfit\t\tWeight\t\tAmount to be taken\n");

    for (i = n - 1; i >= 0; i--)
    {
        float fraction;

        if (remaining_capacity == 0)
        {
            fraction = 0.0;
        }
        else if (items[i].item_weight <= remaining_capacity)
        {
            fraction = 1.0;
            remaining_capacity -= items[i].item_weight;
            max_profit += items[i].item_profit;
        }
        else
        {
            fraction = remaining_capacity / items[i].item_weight;
            max_profit += items[i].item_profit * fraction;
            remaining_capacity = 0;
        }

        printf("%d\t%.6f\t%.6f\t%.6f\n",
               items[i].item_id,
               items[i].item_profit,
               items[i].item_weight,
               fraction);
    }

    printf("\nMaximum profit: %.6f\n", max_profit);

    end = clock();

    cpu_time_used =
        ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("CPU Time Used: %f seconds\n", cpu_time_used);

    return 0;
}