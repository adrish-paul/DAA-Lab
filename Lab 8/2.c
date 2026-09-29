/*
Aim of the program:
Write a program to find out the Longest Common Subsequence
of two given strings. Calculate length of the LCS.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 1000

int main()
{
    clock_t start = clock();

    char str1[MAX];
    char str2[MAX];
    char lcs[MAX];

    int m, n;
    int i, j;

    printf("Enter the first string into an array: ");
    fflush(stdout);
    scanf("%999s", str1);

    printf("Enter the second string into an array: ");
    fflush(stdout);
    scanf("%999s", str2);

    m = strlen(str1);
    n = strlen(str2);

    /* Allocate memory for DP table */
    int **dp = (int **)malloc((m + 1) * sizeof(int *));

    if (dp == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    for (i = 0; i <= m; i++)
    {
        dp[i] = (int *)malloc((n + 1) * sizeof(int));

        if (dp[i] == NULL)
        {
            printf("Memory allocation failed.\n");

            for (int k = 0; k < i; k++)
                free(dp[k]);

            free(dp);
            return 1;
        }
    }

    /* Construct the LCS table */

    for (i = 0; i <= m; i++)
    {
        for (j = 0; j <= n; j++)
        {
            if (i == 0 || j == 0)
            {
                dp[i][j] = 0;
            }
            else if (str1[i - 1] == str2[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            }
            else
            {
                if (dp[i - 1][j] > dp[i][j - 1])
                    dp[i][j] = dp[i - 1][j];
                else
                    dp[i][j] = dp[i][j - 1];
            }
        }
    }

    /* Store LCS length */

    int lcsLength = dp[m][n];

    /* Construct the actual LCS */

    lcs[lcsLength] = '\0';

    i = m;
    j = n;

    while (i > 0 && j > 0)
    {
        if (str1[i - 1] == str2[j - 1])
        {
            lcs[lcsLength - 1] = str1[i - 1];

            i--;
            j--;
            lcsLength--;
        }
        else if (dp[i - 1][j] >= dp[i][j - 1])
        {
            /*
             When both choices have the same LCS length,
             move upward to match the sample output.
            */
            i--;
        }
        else
        {
            j--;
        }
    }

    printf("\nLCS: %s\n", lcs);
    printf("LCS Length: %d\n", dp[m][n]);

    /* Free allocated memory */

    for (i = 0; i <= m; i++)
    {
        free(dp[i]);
    }

    free(dp);

    /* Calculate CPU time */

    clock_t end = clock();

    double cpu_time_used =
        (double)(end - start) / CLOCKS_PER_SEC;

    printf("\nCPU Time Used: %f seconds\n", cpu_time_used);

    return 0;
}