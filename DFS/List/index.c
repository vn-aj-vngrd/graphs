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
    EdgeType edges[MAX_EDGES];
    int count;
} EdgeList;

typedef struct node
{
    int vertex;
    struct node *next;
} Node, *NodePtr;

typedef NodePtr AdjList[MAX_VERTEX];

void createAdjList(AdjList A, EdgeList E)
{
    if (A)
    {
        NodePtr *trav, temp;
        for (int i = 0; i < E.count; i++)
        {
            int u = E.edges[i].vertex;
            int v = E.edges[i].adj_vertex;

            // Insert Last
            for (trav = &A[u]; *trav != NULL; trav = &(*trav)->next)
            {
            }
            *trav = (NodePtr)calloc(sizeof(Node), 1);
            if (*trav)
                (*trav)->vertex = v;

            // for (trav = &A[v]; *trav != NULL; trav = &(*trav)->next)
            // {
            // }
            // *trav = (NodePtr)calloc(sizeof(Node), 1);
            // if (*trav)
            //     (*trav)->vertex = u;
        }
    }
}

void DFS_Iterative(AdjList A, int start)
{
    // Create a stack
    int stack[MAX_VERTEX] = {0};
    int top = -1;

    // Create marker for visited nodes
    int visited[MAX_VERTEX] = {0};

    // Mark the starting node as visited and display it
    visited[start] = 1;
    stack[++top] = start;
    printf("%d ", start);

    // Loop while stack is not empty
    while (top >= 0)
    {
        int current = stack[top--];

        // Display the unvisited current vertex
        if (!visited[current])
        {
            visited[current] = 1;
            printf("%d ", current);
        }

        // Traverse the row and stop when the unvisited vertex is reached
        NodePtr trav;
        for (trav = A[current]; trav != NULL; trav = trav->next)
        {
            // Look for the unvisited vertex
            if (!visited[trav->vertex])
            {
                stack[++top] = trav->vertex;
            }
        }
    }
}

void DFS_Recursive(AdjList A, int visited[], int current)
{
    // Display the current node
    printf("%d ", current);
    visited[current] = 1;

    // Traverse the adjacency list
    NodePtr trav;
    for (trav = A[current]; trav != NULL; trav = trav->next)
    {
        // Look for the unvisited vertex
        if (!visited[trav->vertex])
        {
            DFS_Recursive(A, visited, trav->vertex);
        }
    }
}

void display(AdjList A)
{
    NodePtr trav;
    for (int i = 0; i < MAX_VERTEX; i++)
    {
        printf("%d: ", i);
        for (trav = A[i]; trav != NULL; trav = trav->next)
        {
            printf("%d ", trav->vertex);
        }
        printf("\n");
    }
}

int main()
{
    EdgeList E = {{{0, 4}, {1, 0}, {1, 3}, {2, 1}, {2, 3}, {3, 4}}, 6};
    int start = 2;

    AdjList A = {};
    createAdjList(A, E);
    display(A);

    printf("\nI: ");
    DFS_Iterative(A, start);

    printf("\nR: ");
    int visited[MAX_VERTEX] = {0};
    DFS_Recursive(A, visited, start);

    return 0;
}