#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VERTEX 5
#define MAX 10 // n/n-1)/2
#define INFINITY 9999

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
    edgeType *mst = (edgeType *)malloc(sizeof(edgeType));

    int visited[MAX_VERTEX] = {0};

    visited[source] = 1;
    int 
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
        {INFINITY, 30, 25, INFINITY, 50},
        {30, INFINITY, INFINITY, 90, 30},
        {25, INFINITY, INFINITY, 40, INFINITY},
        {INFINITY, 90, 40, INFINITY, 10},
        {50, 30, INFINITY, 10, INFINITY}};
    displayMatrix(M);

    // int source = 0;
    // edgeType *minimum_cost = prim(M, source);
    // displayPrim(minimum_cost);

    return 0;
}