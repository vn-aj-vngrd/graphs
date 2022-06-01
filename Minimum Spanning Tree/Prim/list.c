#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX 5
#define MAX 10 // n(n-1)/2
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
        NodePtr temp, *trav;
        for (int i = 0; i < E.count; i++)
        {
            int u = E.edges[i].u;
            int v = E.edges[i].v;

            // temp = (NodePtr)calloc(sizeof(Node), 1);
            // if (temp)
            // {
            //     temp->vertex = v;
            //     temp->weight = E.edges[v].weight;
            //     temp->next = A[u];
            //     A[u] = temp;
            // }

            // temp = (NodePtr)calloc(sizeof(Node), 1);
            // if (temp)
            // {
            //     temp->vertex = u;
            //     temp->weight = E.edges[u].weight;
            //     temp->next = A[v];
            //     A[v] = temp;
            // }

            trav = &A[u];
            while (*trav)
            {
                trav = &(*trav)->next;
            }
            *trav = (NodePtr)calloc(sizeof(Node), 1);
            if (*trav)
            {
                (*trav)->vertex = v;
                (*trav)->weight = E.edges[i].weight;
            }

            trav = &A[v];
            while (*trav)
            {
                trav = &(*trav)->next;
            }
            *trav = (NodePtr)calloc(sizeof(Node), 1);
            if (*trav)
            {
                (*trav)->vertex = u;
                (*trav)->weight = E.edges[i].weight;
            }
        }
    }
    return A;
}

void displayV(AdjList A)
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

EdgeType *Prim(AdjList A, int source)
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
                    if (!visited[neighbor->vertex] && min_cost > A[current_vertex]->weight)
                    {
                        min_cost = A[current_vertex]->weight;
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

void displayPrim(EdgeType mst[])
{
    printf("\nMST Edges");
    for (int i = 0; i < MAX_VERTEX - 1; i++)
        printf("\n(%d, %d, %d)", mst[i].u, mst[i].v, mst[i].weight);
}

int main()
{
    EdgeList E = {{
                      {0, 1, 30},
                      {0, 2, 25},
                      {0, 4, 50},

                      {1, 3, 90},
                      {1, 4, 30},

                      {2, 3, 40},

                      {3, 4, 10},
                  },
                  7};

    AdjList A = createAL(E);
    displayV(A);

    EdgeType *mst = Prim(A, 0);
    displayPrim(mst);

    return 0;
}
