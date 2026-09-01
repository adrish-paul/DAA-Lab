/*
Aim of the program: Given an undirected weighted connected graph G(V, E) and starring
vertex ‘s’. Maintain a Min-Priority Queue ‘Q’ from the vertex set V and apply Prim’s algorithm
to
● Find the minimum spanning tree T(V, E’). Display the cost adjacency matrix of ‘T’.
● Display total cost of the minimum spanning tree T.
*/

#include <stdio.h>
#include <time.h>

#define MAX 100
#define INF 9999

int main()
{
    clock_t start = clock();

    int a[MAX][MAX], mst[MAX][MAX] = {0};
    int key[MAX], parent[MAX], visited[MAX] = {0};
    int n, s, i, j, u, v, min, total = 0;

    FILE *fp = fopen("inUnAdjMat.dat", "r");

    printf("Enter the Number of Vertices: ");
    scanf("%d", &n);

    printf("Enter the Starting Vertex: ");
    scanf("%d", &s);
    s--;

    /* Read adjacency matrix */
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            fscanf(fp, "%d", &a[i][j]);

    fclose(fp);

    /* Initialize Min-Priority Queue */
    for (i = 0; i < n; i++) {
        key[i] = INF;
        parent[i] = -1;
    }

    key[s] = 0;

    /* Prim's Algorithm */
    for (i = 0; i < n; i++) {

        /* Find minimum key vertex */
        min = INF;
        u = -1;

        for (j = 0; j < n; j++) {
            if (!visited[j] && key[j] < min) {
                min = key[j];
                u = j;
            }
        }

        visited[u] = 1;

        /* Add edge to MST */
        if (parent[u] != -1) {
            mst[u][parent[u]] = a[u][parent[u]];
            mst[parent[u]][u] = a[u][parent[u]];
            total += a[u][parent[u]];
        }

        /* Update keys */
        for (v = 0; v < n; v++) {
            if (a[u][v] != 0 &&
                !visited[v] &&
                a[u][v] < key[v]) {

                key[v] = a[u][v];
                parent[v] = u;
            }
        }
    }

    /* Display MST */
    printf("\nCost Adjacency Matrix of Minimum Spanning Tree:\n");

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++)
            printf("%d ", mst[i][j]);
        printf("\n");
    }

    printf("\nTotal Weight of the Spanning Tree: %d\n", total);

    clock_t end = clock();

    double cpu_time_used =
        ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("CPU Time Used: %f seconds\n", cpu_time_used);

    return 0;
}