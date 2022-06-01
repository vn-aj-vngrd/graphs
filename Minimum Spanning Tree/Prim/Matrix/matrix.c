#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VERTEX 5
#define MAX 10 // n/n-1)/2
#define INF 9999

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

typedef int MATRIX[MAX_VERTEX][MAX_VERTEX];

edgeType *Prim(MATRIX M, int source)
{
    edgeType *mst = (edgeType *)malloc(sizeof(edgeType) * (MAX_VERTEX - 1));

    int visited[MAX_VERTEX] = {0};

    visited[source] = 1;
    int next_vertex = source;

    for (int count = 0; count < MAX_VERTEX - 1; count++)
    {
        int min_cost = INF;

        int current_vertex, vertex;
        for (current_vertex = 0; current_vertex < MAX_VERTEX; current_vertex++)
        {
            if (visited[current_vertex])
            {
                for (int neighbor = 0; neighbor < MAX_VERTEX; neighbor++)
                {
                    if (!visited[neighbor] && min_cost > M[current_vertex][neighbor])
                    {
                        min_cost = M[current_vertex][neighbor];
                        next_vertex = neighbor;
                        vertex = current_vertex;
                    }
                }
            }
        }

        visited[next_vertex] = 1;
        mst[count].vertex = vertex;
        mst[count].adj_vertex = next_vertex;
    }

    return mst;
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

void displayPrim(edgeType mst[])
{
    printf("\nMST Edges");
    for (int i = 0; i < MAX_VERTEX - 1; i++)
        printf("\n(%d, %d)", mst[i].vertex, mst[i].adj_vertex);
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

    int source = 0;
    edgeType *minimum_cost = Prim(M, source);
    displayPrim(minimum_cost);

    return 0;
}