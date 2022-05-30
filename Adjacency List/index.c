#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX 5
#define MAX 10 // n(n-1)/2

typedef struct
{
    int vertex;
    int adj_vertex;
} EdgeType;

typedef struct
{
    EdgeType edges[MAX];
    int count;
} EdgeList;

typedef struct node
{
    int vertex;
    struct node *next;
} Node, *NodePtr;

typedef NodePtr *AdjList_1;
typedef NodePtr AdjList_2[MAX_VERTEX];

AdjList_1 createAL1(EdgeList E)
{
    AdjList_1 A = (AdjList_1)calloc(sizeof(NodePtr), MAX_VERTEX);
    if (A)
    {
        NodePtr temp;
        for (int i = 0; i < E.count; i++)
        {
            int u = E.edges[i].vertex;
            int v = E.edges[i].adj_vertex;

            temp = (NodePtr)calloc(sizeof(Node), 1);
            if (temp)
            {
                temp->vertex = v;
                temp->next = A[u];
                A[u] = temp;
            }

            temp = (NodePtr)calloc(sizeof(Node), 1);
            if (temp)
            {
                temp->vertex = u;
                temp->next = A[v];
                A[v] = temp;
            }
        }
    }
    return A;
}

void createAL2(AdjList_2 A, EdgeList E)
{
    if (A)
    {
        NodePtr temp;
        for (int i = 0; i < E.count; i++)
        {
            int u = E.edges[i].vertex;
            int v = E.edges[i].adj_vertex;

            temp = (NodePtr)calloc(sizeof(Node), 1);
            if (temp)
            {
                temp->vertex = v;
                temp->next = A[u];
                A[u] = temp;
            }

            temp = (NodePtr)calloc(sizeof(Node), 1);
            if (temp)
            {
                temp->vertex = u;
                temp->next = A[v];
                A[v] = temp;
            }
        }
    }
}

void displayV1(AdjList_1 A)
{
    for (int i = 0; i < MAX_VERTEX; i++)
    {
        printf("%d: ", i);
        for (NodePtr trav = A[i]; trav != NULL; trav = trav->next)
        {
            printf("%d ", trav->vertex);
        }
        printf("\n");
    }
    printf("\n");
}

void displayV2(AdjList_2 A)
{
    for (int i = 0; i < MAX_VERTEX; i++)
    {
        printf("%d: ", i);
        for (NodePtr trav = A[i]; trav != NULL; trav = trav->next)
        {
            printf("%d ", trav->vertex);
        }
        printf("\n");
    }
}

int main()
{
    EdgeList E = {{{1, 3}, {2, 3}, {3, 4}, {0, 1}, {3, 0}}, 5};

    AdjList_1 A1 = createAL1(E);
    displayV1(A1);

    AdjList_2 A2 = {0};
    createAL2(A2, E);
    displayV2(A2);

    return 0;
}
