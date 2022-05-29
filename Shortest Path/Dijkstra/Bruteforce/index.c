#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_VERTEX 5
#define MAX 10 /** undirected: 5(5-1) / 2 or n (n-1) /2 **/
#define INF 9999

/* An unweighted, undirected Edge */
typedef struct
{
    int vertex;
    int adj_vertex;
} edgeType;

typedef struct
{
    edgeType Edge[MAX];
    int edge_count;
} EdgeList;

typedef int MATRIX_1[MAX_VERTEX][MAX_VERTEX]; // static
typedef int **MATRIX_2;                       // dynamic

int *dijkstra(MATRIX_1 M, int start)
{
    // Create a distance matrix
    int *distance = (int *)calloc(sizeof(int), MAX_VERTEX);

    // Create a marker for visited vertices
    int visited[MAX_VERTEX] = {0};

    // Copy the default distances of the starting vertex from the given matrix to the distance matrix
    memcpy(distance, M[start], sizeof(int) * MAX_VERTEX);

    // The distance of the starting vertex to itself is always 0
    distance[start] = 0;

    // Mark the starting vertex as visited
    visited[start] = 1;

    // Set the starting vertex as the current vertex
    int current_vertex = start;

    // Iterate through the remaining vertices
    for (int i = 1; i < MAX_VERTEX; i++)
    {
        // Set the minimum distance to INF
        int min = INF;

        // Get the current vertex which follows the ff conditions:
        // - The vertex is not yet visited
        // - Has the smallest distance
        for (int j = 0; j < MAX_VERTEX; j++)
        {
            if (!visited[j] && distance[j] < min)
            {
                min = distance[j];
                current_vertex = j;
            }
        }

        // Mark the current_vertex as visited
        visited[current_vertex] = 1;

        // Apply relaxation if possible
        for (int k = 0; k < MAX_VERTEX; k++)
        {
            if (!visited[k] && distance[k] > distance[current_vertex] + M[current_vertex][k])
            {
                distance[k] = distance[current_vertex] + M[current_vertex][k];
            }
        }
    }

    return distance;
}

void displayDistance(int distance[], int source)
{
    printf("\n\nSource vertex: %d", source);
    for (int i = 0; i < MAX_VERTEX; i++)
        printf("\nShortest distance from %d to %d: %d", source, i, distance[i]);
}

void displayMatrix(MATRIX_1 M)
{
    printf("%3c", ' ');
    for (int i = 0; i < MAX_VERTEX; i++)
        printf("%4d ", i);

    for (int i = 0; i < MAX_VERTEX; i++)
    {
        printf("\n%d: ", i);
        for (int j = 0; j < MAX_VERTEX; j++)
            printf("%4d ", M[i][j]);
    }
}

int main()
{
    MATRIX_1 M = {
        {INF, 30, 25, INF, 50},
        {30, INF, INF, 90, 30},
        {25, INF, INF, 40, INF},
        {INF, 90, 40, INF, 10},
        {50, 30, INF, 10, INF}};

    displayMatrix(M);

    int start = 0;
    int *distance = dijkstra(M, start);
    displayDistance(distance, start);

    return 0;
}