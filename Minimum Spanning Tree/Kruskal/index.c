#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INF 9999
#define UNDEFINED -1
#define MAX_VERTEX 5
#define MAX 10
#define MAXIMUM 1000

typedef struct
{
    int u;
    int v;
    int weight;
} data;

typedef struct
{
    data elem[MAXIMUM];
    int lastIdx;
} POT;

typedef struct node
{
    int vertex;
    int weight;
    struct node *next;
} Node, *NodePtr;

typedef NodePtr *AdjList;
typedef int **MATRIX;

void insert(int u, int v, int weight, POT *P)
{
    int i, parent;
    if (P->lastIdx < MAXIMUM - 1)
    {
        i = ++P->lastIdx;
        parent = (i - 1) / 2;

        while (i > 0 && P->elem[parent].weight > weight)
        {
            P->elem[i] = P->elem[parent];
            i = parent;
            parent = (i - 1) / 2;
        }
        P->elem[i].u = u;
        P->elem[i].v = v;
        P->elem[i].weight = weight;
    }
}

data deleteMin(POT *P)
{
    int i, LC;
    data retval, temp;
    if (P->lastIdx > -1)
    {
        i = 0;
        retval = P->elem[i];
        P->elem[i] = P->elem[P->lastIdx--];

        LC = 2 * i + 1;
        while (LC <= P->lastIdx)
        {
            if (LC + 1 <= P->lastIdx && P->elem[LC].weight > P->elem[LC + 1].weight)
                LC++;

            if (P->elem[i].weight > P->elem[LC].weight)
            {
                temp = P->elem[i];
                P->elem[i] = P->elem[LC];
                P->elem[LC] = temp;
                i = LC;
                LC = 2 * i + 1;
            }
            else
            {
                break;
            }
        }
    }
    return retval;
}

int find(int i, int parent[])
{
    while (i != parent[i])
        i = parent[i];
    return i;
}

int add(int u, int v, data retval[], int count)
{
    int i;
    retval[count].u = u;
    retval[count].v = v;
    count++;
    return 1;
}

void unionSet(int parent[], int u, int v)
{
    int i = find(u, parent);
    int j = find(v, parent);
    parent[j] = i;
}

data *kruskalMatrix(MATRIX M)
{
    int parent[MAX_VERTEX], min_cost = 0;
    int i, u, v, count = 0;
    data temp;
    POT P = {{}, -1};
    data *retval;

    retval = (data *)calloc(MAX_VERTEX, sizeof(data));
    if (retval != NULL)
    {

        for (u = 0; u < MAX_VERTEX; u++)
        {
            for (v = u; v < MAX_VERTEX; v++)
            {
                if (M[u][v] != INF && M[u][v] != 0)
                {
                    insert(u, v, M[u][v], &P);
                }
            }
        }

        for (i = 0; i < MAX_VERTEX; i++)
            parent[i] = i;

        while (P.lastIdx != -1 && count <= MAX_VERTEX)
        {

            temp = deleteMin(&P);
            u = temp.u;
            v = temp.v;

            if (find(u, parent) != find(v, parent))
            {

                add(u, v, retval, count);
                count++;

                min_cost += temp.weight;
                unionSet(parent, u, v);
            }
        }
    }
    printf("\n\nMinimum Cost is %d", min_cost);
    return retval;
}

data *kruskalList(AdjList L)
{
    POT P = {{}, -1};
    data temp;
    int i, count = 0, u, v, min = 0;
    int parent[MAX_VERTEX];
    NodePtr trav;
    data *retval;

    for (i = 0; i < MAX_VERTEX; i++)
        parent[i] = i;

    retval = (data *)calloc(MAX_VERTEX, sizeof(data));
    if (retval != NULL)
    {

        for (i = 0; i < MAX_VERTEX; i++)
        {

            trav = L[i];
            while (trav != NULL)
            {
                insert(i, trav->vertex, trav->weight, &P);
                trav = trav->next;
            }
        }

        while (P.lastIdx != -1 && count < MAX_VERTEX)
        {

            temp = deleteMin(&P);
            u = temp.u;
            v = temp.v;

            if (find(u, parent) != find(v, parent))
            {

                add(u, v, retval, count);
                count++;

                min += temp.weight;
                unionSet(parent, u, v);
            }
        }
    }
    printf("\nMinimum Cost is %d", min);
    return retval;
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

int main()
{
    return 0;
}
