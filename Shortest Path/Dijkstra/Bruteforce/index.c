#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_VERTEX 5
#define INF 9999

typedef int MATRIX[MAX_VERTEX][MAX_VERTEX];

int *dijkstra(MATRIX M, int start)
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

    // Set the starting vertex as the selected vertex
    int selected_vertex = start;

    // Iterate through the remaining vertices
    for (int i = 1; i < MAX_VERTEX; i++)
    {
        // Set the minimum distance to INF
        int min = INF;

        // Get the current vertex which follows the ff conditions:
        // - The vertex is not yet visited
        // - Has the smallest distance
        for (int smallest = 0; smallest < MAX_VERTEX; smallest++)
        {
            if (!visited[smallest] && distance[smallest] < min)
            {
                min = distance[smallest];
                selected_vertex = smallest;
            }
        }

        // Mark the selected_vertex as visited
        visited[selected_vertex] = 1;

        // Apply relaxation if possible
        for (int neighbor = 0; neighbor < MAX_VERTEX; neighbor++)
        {
            if (!visited[neighbor] && distance[neighbor] > distance[selected_vertex] + M[selected_vertex][neighbor])
            {
                distance[neighbor] = distance[selected_vertex] + M[selected_vertex][neighbor];
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

void displayMatrix(MATRIX M)
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
    MATRIX M = {
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