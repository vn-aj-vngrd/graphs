#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VERTEX 5
#define MAX_EDGES 10 // n(n-1)/2
#define QUEUE_SIZE 100

typedef struct
{
    int queue[QUEUE_SIZE];
    int front, rear;
} Queue;

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

void BFS_Iterative(MATRIX M, int start)
{
    // Create a queue
    int queue[100];
    int front = 0, rear = -1;

    // Create a marker for visited nodes
    int visited[MAX_VERTEX] = {0};

    // Enqueue the start node
    queue[++rear] = start;

    // While queue is not empty
    while (front <= rear)
    {
        // Dequeue a vertex from queue and display it
        int current = queue[front++];

        if (!visited[current])
        {
            printf("%d ", current);
            visited[current] = 1;
        }

        // Explore the neighbors of current vertex
        int trav;
        for (trav = 0; trav < MAX_VERTEX; trav++)
        {
            if (M[current][trav] != 0 && visited[trav] != 1)
            {
                queue[++rear] = trav;
            }
        }
    }
}

void BFS_Recursive(MATRIX M, Queue *Q, int visited[], int current)
{
    if (!visited[current])
    {
        visited[current] = 1;
        printf("%d ", current);
    }

    int trav;
    for (trav = 0; trav < MAX_VERTEX; trav++)
    {
        if (M[current][trav] != 0 && visited[trav] != 1)
        {
            Q->queue[++Q->rear] = trav;
        }
    }

    if (Q->front <= Q->rear)
    {
        int next = Q->queue[Q->front++];
        BFS_Recursive(M, Q, visited, next);
    }
}

void BFS_Traversal(MATRIX M, int start)
{
    Queue Q;
    Q.front = 0;
    Q.rear = -1;

    int visited[MAX_VERTEX] = {0};

    BFS_Recursive(M, &Q, visited, start);
}

int main()
{
    EdgeList E = {{{0, 4}, {1, 0}, {1, 3}, {2, 1}, {2, 3}, {3, 4}}, 6};
    int start = 2;

    MATRIX M = {0};
    createGraph(M, E);
    display(M);

    printf("\nI: ");
    BFS_Iterative(M, start);

    printf("\nR: ");
    BFS_Traversal(M, start);

    return 0;
}