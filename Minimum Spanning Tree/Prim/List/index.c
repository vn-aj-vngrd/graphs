#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX 4
#define MAX 6 // n(n-1)/2
#define INF 9999

typedef struct
{
    int u;
    int v;
    int weight;
} EdgeType;

typedef struct
{
    EdgeType edges[MAX];
    int count;
} EdgeList;

typedef struct node
{
    int vertex;
    int weight;
    struct node *next;
} Node, *NodePtr;

typedef NodePtr *AdjList;

AdjList createAL(EdgeList E)
{
    AdjList A = (AdjList)calloc(sizeof(NodePtr), MAX_VERTEX);
    if (A)
    {
        NodePtr temp;
        for (int i = 0; i < E.count; i++)
        {
            int u = E.edges[i].u;
            int v = E.edges[i].v;

            temp = (NodePtr)calloc(sizeof(Node), 1);
            if (temp)
            {
                temp->vertex = v;
                temp->weight = E.edges[i].weight;
                temp->next = A[u];
                A[u] = temp;
            }

            temp = (NodePtr)calloc(sizeof(Node), 1);
            if (temp)
            {
                temp->vertex = u;
                temp->weight = E.edges[i].weight;
                temp->next = A[v];
                A[v] = temp;
            }
        }
    }
    return A;
}

EdgeType *prim(AdjList A, int source)
{
    EdgeType *mst = (EdgeType *)calloc(sizeof(EdgeType), MAX_VERTEX - 1);

    int visited[MAX_VERTEX] = {0};

    visited[source] = 1;
    int next_vertex = source;

    for (int count = 0; count < MAX_VERTEX - 1; count++)
    {
        int min_cost = INF;

        int vertex;
        for (int current_vertex = 0; current_vertex < MAX_VERTEX; current_vertex++)
        {
            if (visited[current_vertex])
            {
                NodePtr neighbor;
                for (neighbor = A[current_vertex]; neighbor != NULL; neighbor = neighbor->next)
                {
                    if (!visited[neighbor->vertex] && neighbor->weight < min_cost)
                    {
                        min_cost = neighbor->weight;
                        next_vertex = neighbor->vertex;
                        vertex = current_vertex;
                    }
                }
            }
        }

        visited[next_vertex] = 1;
        mst[count].u = vertex;
        mst[count].v = next_vertex;
        mst[count].weight = min_cost;
    }

    return mst;
}

void display(AdjList A)
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

void displayMST(EdgeType mst[])
{
    for (int i = 0; i < MAX_VERTEX - 1; i++)
    {
        printf("(%d->%d) %d\n", mst[i].u, mst[i].v, mst[i].weight);
    }
}

int main()
{
    // EdgeList E = {{{1, 3, 20}, {2, 3, 30}, {3, 4, 40}, {0, 1, 50}, {3, 0, 40}}, 5};
    EdgeList E = {{{0, 1, 2}, {0, 2, 4}, {1, 2, 1}, {2, 3, 3}}, 4};
    AdjList A = createAL(E);
    display(A);

    EdgeType *mst = prim(A, 1);
    displayMST(mst);

    return 0;
}
