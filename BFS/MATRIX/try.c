#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VERTEX 5
#define MAX_EDGES 10 // n(n-1)/2
#define QUEUE_SIZE 100

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

typedef int MATRIX[MAX_VERTEX][MAX_VERTEX];

void createGraph(MATRIX M, EdgeList E)
{
    int i;
    for (i = 0; i < E.edge_count; i++)
    {
        M[E.edge[i].vertex][E.edge[i].adj_vertex] = 1;
        // M[E.edge[i].adj_vertex][E.edge[i].vertex] = 1;
    }
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
    printf("\n");
}

void BFS_Traversal(MATRIX M, int start)
{
    int trav, current_vertex;

    int visited[MAX_VERTEX];
    memset(visited, 0, sizeof(visited));

    int queue[100];
    int front = 0;
    int rear = -1;

    queue[++rear] = start;

    while (front <= rear)
    {
        current_vertex = queue[front++];
        printf("%d ", current_vertex);

        for (trav = 0; trav < MAX_VERTEX; trav++)
        {
            if (M[current_vertex][trav] != 0 && visited[trav] != 1 && visited[trav] != 2)
            {
                queue[++rear] = trav;
                visited[trav] = 1;
            }
        }
        visited[current_vertex] = 2;
    }
    printf("\n");
}

void BFS_Recursive(MATRIX M, int visited[], int current)
{
    printf("%d ", current);
    visited[current] = 1;

    int trav;
    for (trav = 0; trav < MAX_VERTEX; trav++)
    {
        if (M[current][trav] != 0 && visited[trav] != 1 && visited[trav] != 2)
        {
            BFS_Recursive(M, visited, trav);
        }
    }
}

int main()
{
    EdgeList E = {{{0, 4}, {1, 3}, {2, 1}, {2, 3}, {3, 4}}, 5};
    MATRIX M = {0};

    createGraph(M, E);
    display(M);

    int visited[MAX_VERTEX] = {0};
    printf("\nR: ");
    BFS_Traversal(M, 2);
    printf("I: ");
    BFS_Recursive(M, visited, 2);

    return 0;
}