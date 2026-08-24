/*Aim of the program: Write a function to ROTATE_RIGHT (p1, p2) right an array for first p2
elements by 1 position using EXCHANGE (p, q) function that swaps/exchanges the numbers p
&amp; q. Parameter p1 be the starting address of the array and p2 be the number of elements to be
rotated.*/

#include <stdio.h>

void EXCHANGE(int *p, int *q)
{
    int temp = *p;
    *p = *q;
    *q = temp;
}

void ROTATE_RIGHT(int p1[], int p2)
{
    int i;
    for(i = p2 - 1; i > 0; i--)
    {
        EXCHANGE(&p1[i], &p1[i - 1]);
    }
}

int main()
{
    int A[100], N, i, p2;

    printf("Enter size of array: ");
    scanf("%d", &N);

    printf("Enter array elements:\n");
    for(i = 0; i < N; i++)
    {
        scanf("%d", &A[i]);
    }

    printf("Enter number of elements to rotate: ");
    scanf("%d", &p2);

    printf("\nBefore ROTATE:\n");
    for(i = 0; i < N; i++)
        printf("%d ", A[i]);

    ROTATE_RIGHT(A, p2);

    printf("\nAfter ROTATE:\n");
    for(i = 0; i < N; i++)
        printf("%d ", A[i]);

    return 0;
}