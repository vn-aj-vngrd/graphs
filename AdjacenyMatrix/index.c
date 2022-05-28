#include <stdio.h>
#include <stdlib.h>

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

typedef int **MATRIX_1;
typedef int MATRIX_2[MAX_VERTEX][MAX_VERTEX];

MATRIX_1 createAMV1(EdgeList E)
{
    MATRIX_1 M = (MATRIX_1)calloc(sizeof(int *), MAX_VERTEX);

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

void createAM2(MATRIX_2 M, EdgeList E)
{
    int i;
    for (i = 0; i < E.edge_count; i++)
    {
        M[E.edge[i].vertex][E.edge[i].adj_vertex] = 1;
        M[E.edge[i].adj_vertex][E.edge[i].vertex] = 1;
    }
}

void displayV1(MATRIX_1 M)
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
    printf("\n\n");
}

void displayV2(MATRIX_2 M)
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

int main()
{
    EdgeList E = {{{1, 3}, {2, 3}, {3, 4}, {0, 1}, {3, 0}}, 5};

    MATRIX_1 M1 = createAMV1(E);
    displayV1(M1);

    MATRIX_2 M2 = {0};
    createAM2(M2, E);
    displayV2(M2);

    return 0;
}