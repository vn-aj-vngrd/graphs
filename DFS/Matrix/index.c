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

void display(MATRIX M)
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

void DFS_Iterative(MATRIX M, int start)
{
    // Create marker for visited nodes
    int visited[MAX_VERTEX] = {0};

    // Create a stack
    int stack[100];
    int top = -1;

    // Mark the starting point visited and display it
    visited[start] = 1;
    stack[++top] = start;
    printf("%d ", start);

    // This will determine if a row is traversed completely
    int last = 1;

    // Loop while stack is not empty
    while (top >= 0)
    {
        int current = stack[top];
        if (last == 1)
        {
            top--;
        }

        if (!visited[current])
        {
            visited[current] = 1;
            printf("%d ", current);
        }

        int trav;
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
}

void DFS_Recursive(MATRIX M, int visited[], int current)
{
    // Display the current node
    printf("%d ", current);
    visited[current] = 1;

    // Traverse the adjacency matrix
    int i;
    for (i = 0; i < MAX_VERTEX; i++)
    {
        // Look for unvisited links
        if (!visited[i] && M[current][i])
        {
            DFS_Recursive(M, visited, i);
        }
    }
}

int main()
{
    EdgeList E = {{{1, 3}, {2, 3}, {3, 4}, {0, 4}, {2, 1}}, 5};

    MATRIX M = createAM(E);
    display(M);

    printf("\n\nI: ");
    DFS_Iterative(M, 0);

    printf("\nR: ");
    int visited[MAX_VERTEX] = {0};
    DFS_Recursive(M, visited, 0);

    return 0;
}