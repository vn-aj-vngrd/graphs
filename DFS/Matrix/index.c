#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VERTEX 5
#define MAX_EDGES 10 // n(n-1)/2

typedef struct
{
    int vertex;
    int adj_vertex;
} EdgeType;

typedef struct
{
    EdgeType edge[MAX_EDGES];
    int edge_count;
} EdgeList;

typedef int **MATRIX;

MATRIX createAM(EdgeList E)
{
    MATRIX M = (MATRIX)calloc(sizeof(int *), MAX_VERTEX);

    int i;
    for (i = 0; i < MAX_VERTEX; i++)
    {
        M[i] = (int *)calloc(sizeof(int), MAX_VERTEX);
    }

    for (i = 0; i < E.edge_count; i++)
    {
        M[E.edge[i].vertex][E.edge[i].adj_vertex] = 1;
        M[E.edge[i].adj_vertex][E.edge[i].vertex] = 1;
    }

    return M;
}

void display(MATRIX_1 M)
{
    int i, j;
    printf("   ");
    for (i = 0; i < MAX_VERTEX; i++)
        printf("%d ", i);

    for (i = 0; i < MAX_VERTEX; i++)
    {
        printf("\n%d: ", i);
        for (j = 0; j < MAX_VERTEX; j++)
        {
            printf("%d ", M[i][j]);
        }
    }
}

void DFS(MATRIX_1 M, int start)
{
    int visited[MAX_VERTEX] = {0};
    int stack[100];

    int top = -1;
    int last = 1;
    int trav;
    int current;

    visited[start] = 1;
    stack[++top] = start;
    printf("%d ", start);

    while (top >= 0)
    {
        current = stack[top];
        if (last == 1)
        {
            top--;
        }

        if (!visited[current])
        {
            visited[current] = 1;
            printf("%d ", current);
        }

        for (trav = 0; trav < MAX_VERTEX; trav++)
        {
            if (!visited[trav] && M[current][trav] != 0)
            {
                stack[++top] = trav;
                break;
            }
        }

        last = MAX_VERTEX == trav ? 1 : 0;
    }
    // while (top > -1)
    // {
    //     for (int y = 0; y < MAX_VERTEX; y++)
    //     {
    //         if (visited[y] == 0 && M[y][stack[top]] == 1)
    //         {
    //             printf("%d ", y);
    //             stack[++top] = y;
    //             visited[y] = 1;
    //             // printf("%d ", stack[top]);
    //             y = 0;
    //             printf("\n");
    //         }
    //     }
    //     top--;
    // }
}

void DFS2(MATRIX_1 M, int visited[], int current)
{
    printf("%d ", current);
    visited[current] = 1;

    for (int i = 0; i < MAX_VERTEX; i++)
    {
        if (!visited[i] && M[current][i])
        {
            DFS2(M, visited, i);
        }
    }
}

int main()
{
    EdgeList E = {{{1, 3}, {2, 3}, {3, 4}, {0, 4}, {2, 1}}, 5};

    MATRIX_1 M1;
    initMatrix(M1);
    createAM2(M1, E);
    displayV2(M1);
    printf("\n");

    DFS(M1, 0);
    printf("\n");
    int visited[MAX_VERTEX] = {0};
    DFS2(M1, visited, 0);

    return 0;
}