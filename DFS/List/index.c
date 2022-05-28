#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// n(n-1)/2
#define MAX_VERTEX 5
#define MAX_EDGES 10

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

void init(AdjList L)
{
    for (int i = 0; i < MAX_VERTEX; i++)
    {
        L[i] = NULL;
    }
}

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

            for (trav = &A[v]; *trav != NULL; trav = &(*trav)->next)
            {
            }
            *trav = (NodePtr)calloc(sizeof(Node), 1);
            if (*trav)
                (*trav)->vertex = u;
        }
    }
}

void DFS_IterativeV1(AdjList A, int start)
{
    // NodePtr trav;

    // int visited[MAX_VERTEX] = {0};
    // int stack[MAX_VERTEX] = {0};
    // int top = 0;

    // visited[start] = 1;
    // stack[top] = start;
    // printf("%d ", start);

    // while (top > -1)
    // {
    //     for (trav = A[top]; trav != NULL; trav = trav->next)
    //     {
    //         if (!visited[trav->vertex])
    //         {
    //             break;
    //         }
    //     }
    //     if (trav == NULL)
    //     {
    //         top--;
    //     }
    //     else
    //     {
    //         stack[++top] = trav->vertex;
    //         visited[stack[top]] = 1;
    //         printf("%d ", stack[top]);
    //     }
    // }

    int mark[MAX_VERTEX];
    int curr, stack[MAX_VERTEX + 1];
    NodePtr trav;

    stack[0] = 1;
    stack[stack[0]] = start;
    mark[start] = 1;
    printf("%d ", start);

    while (stack[0] > 0)
    {
        curr = stack[stack[0]];
        for (trav = A[curr]; trav != NULL; trav = trav->next)
        {
            if (mark[trav->vertex] != 1)
            {
                break;
            }
        }
        if (trav == NULL)
        {
            stack[0]--;
        }
        else
        {
            stack[0]++;
            stack[stack[0]] = trav->vertex;
            printf("%d ", stack[stack[0]]);
            mark[stack[stack[0]]] = 1;
        }
    }
}

void DFS_IterativeV2(AdjList A, int start)
{
    NodePtr trav;

    int visited[MAX_VERTEX] = {0};
    int stack[MAX_VERTEX] = {0};
    int top = -1;

    visited[start] = 1;
    stack[++top] = start;
    printf("%d ", start);

    int last = 1;
    while (top >= 0)
    {
        int current = stack[top];

        last == 1 ? top-- : 0;

        if (!visited[current])
        {
            visited[current] = 1;
            printf("%d ", current);
        }

        for (trav = A[current]; trav != NULL; trav = trav->next)
        {
            if (!visited[trav->vertex])
            {
                stack[++top] = trav->vertex;
                break;
            }
        }

        last = trav == NULL ? 1 : 0;
    }
}

void DFS_RecursiveV1(AdjList A, int visited[], int current)
{
    printf("%d ", current);
    visited[current] = 1;

    NodePtr trav;
    for (trav = A[current]; trav != NULL; trav = trav->next)
    {
        if (!visited[trav->vertex])
        {
            DFS_RecursiveV1(A, visited, trav->vertex);
        }
    }
}

int main()
{
    EdgeList E = {{{1, 3}, {2, 3}, {3, 4}, {1, 4}, {2, 1}}, 5};

    AdjList A;
    init(A);
    createAdjList(A, E);
    printf("V1: ");
    DFS_IterativeV1(A, 3);

    printf("\nV2: ");

    DFS_IterativeV2(A, 3);

    printf("\nR1: ");

    int visited[MAX_VERTEX] = {0};
    DFS_RecursiveV1(A, visited, 3);

    return 0;
}