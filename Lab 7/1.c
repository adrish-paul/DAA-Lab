/*
Aim of the program:
Given a directed graph G(V, E) and a starting vertex 's',
determine the shortest paths from source vertex 's' to all
other vertices using Dijkstra's Algorithm.
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#define INF INT_MAX

void printPath(int parent[], int source, int destination)
{
    int path[100];
    int count = 0;
    int current = destination;

    while (current != -1)
    {
        path[count++] = current;

        if (current == source)
            break;

        current = parent[current];
    }

    for (int i = count - 1; i >= 0; i--)
    {
        printf("%d", path[i] + 1);

        if (i != 0)
            printf("->");
    }
}

void dijkstra(int n, int graph[n][n], int source,
              int distance[], int parent[])
{
    int visited[n];

    for (int i = 0; i < n; i++)
    {
        distance[i] = INF;
        visited[i] = 0;
        parent[i] = -1;
    }

    distance[source] = 0;

    for (int count = 0; count < n - 1; count++)
    {
        int minDistance = INF;
        int u = -1;

        for (int i = 0; i < n; i++)
        {
            if (!visited[i] && distance[i] < minDistance)
            {
                minDistance = distance[i];
                u = i;
            }
        }

        if (u == -1)
            break;

        visited[u] = 1;

        for (int v = 0; v < n; v++)
        {
            if (!visited[v] &&
                graph[u][v] != 0 &&
                distance[u] != INF &&
                distance[u] + graph[u][v] < distance[v])
            {
                distance[v] = distance[u] + graph[u][v];
                parent[v] = u;
            }
        }
    }
}

int main()
{
    clock_t start = clock();

    int n, source;

    printf("Enter the Number of Vertices: ");
    scanf("%d", &n);

    printf("Enter the Source Vertex: ");
    scanf("%d", &source);

    source--;

    FILE *fin = fopen("inDiAdjMat1.dat", "r");

    if (fin == NULL)
    {
        printf("Error: Cannot open input file 'inDiAdjMat1.dat'.\n");
        return 1;
    }

    int graph[n][n];

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (fscanf(fin, "%d", &graph[i][j]) != 1)
            {
                printf("Error: Invalid data in input file.\n");
                fclose(fin);
                return 1;
            }
        }
    }

    fclose(fin);

    int distance[n];
    int parent[n];

    dijkstra(n, graph, source, distance, parent);

    printf("\nOutput:\n");

    printf("%-10s %-12s %-10s %s\n",
           "Source", "Destination", "Cost", "Path");

    for (int i = 0; i < n; i++)
    {
        printf("%-10d %-12d ",
               source + 1, i + 1);

        if (distance[i] == INF)
        {
            printf("%-10s No Path", "INF");
        }
        else
        {
            printf("%-10d ", distance[i]);

            if (i == source)
                printf("-");
            else
                printPath(parent, source, i);
        }

        printf("\n");
    }

    clock_t end = clock();

    double cpu_time_used =
        (double)(end - start) / CLOCKS_PER_SEC;

    printf("\nCPU Time Used: %f seconds\n", cpu_time_used);

    return 0;
}