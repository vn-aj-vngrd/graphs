#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_VERTEX 5
#define INF 9999
typedef struct
{
    int vertex;
    int weight;
} Node;

typedef struct
{
    Node node[MAX_VERTEX];
    int last_index;
} PQ;

typedef int MATRIX[MAX_VERTEX][MAX_VERTEX];

void insert(PQ *Q, int vertex, int weight)
{
    if (Q->last_index < MAX_VERTEX - 1)
    {
        int current = ++Q->last_index;

        int parent = (current - 1) / 2;
        while (current > 0 && Q->node[parent].weight > weight)
        {
            Q->node[current] = Q->node[parent];
            current = parent;
            parent = (parent - 1) / 2;
        }
        Q->node[current].vertex = vertex;
        Q->node[current].weight = weight;
    }
}

Node deleteMin(PQ *Q)
{
    Node node;
    // if PQ is not empty, perform operation
    if (Q->last_index >= 0)
    {
        // Set current to 0 and child to 1
        int current = 0, child = 1;

        // Get to root node of the tree
        node = Q->node[current];

        // Get the last node of the tree and set it to the root
        Q->node[current] = Q->node[Q->last_index--];

        // Heapify
        while (child <= Q->last_index)
        {
            //   right    <=  last                 left             >          right
            if (child + 1 <= Q->last_index && Q->node[child].weight > Q->node[child + 1].weight)
            {
                child++;
            }

            // current > child
            if (Q->node[current].weight > Q->node[child].weight)
            {
                Node temp = Q->node[current];
                Q->node[current] = Q->node[child];
                Q->node[child] = temp;

                current = child;
                child = 2 * child + 1;
            }
            else
            {
                break;
            }
        }
    }
    return node;
}

int *dijkstra(MATRIX M, int start)
{
    // create an empty PQ
    PQ Q = {.last_index = -1};

    // initialize distance to infinity
    int *distance = (int *)calloc(MAX_VERTEX, sizeof(int));
    memset(distance, INF, sizeof(int) * MAX_VERTEX);

    distance[start] = 0;
    insert(&Q, start, 0);

    // O (V) where N is the number of vertices
    // Until PQ is empty, we perform the operation.
    while (Q.last_index > -1)
    {
        Node current = deleteMin(&Q);
        int current_vertex = current.vertex;

        for (int neighbor = 0; neighbor < MAX_VERTEX; neighbor++)
        {
            if (M[current_vertex][neighbor] != INF && M[current_vertex][neighbor] != 0)
            {
                if (distance[neighbor] > distance[current_vertex] + M[current_vertex][neighbor])
                {
                    distance[neighbor] = distance[current_vertex] + M[current_vertex][neighbor];
                    insert(&Q, neighbor, distance[neighbor]);
                }
            }
        }
    }

    return distance;
}

void displayDistance(int distance[], int source)
{
    printf("\n\nSource vertex: %d", source);
    for (int i = 0; i < MAX_VERTEX; i++)
        printf("\nShortest distance from %d to %d: %d", source, i, distance[i]);
}

void displayMatrix(MATRIX M)
{
    printf("%3c", ' ');
    for (int i = 0; i < MAX_VERTEX; i++)
        printf("%4d ", i);

    for (int i = 0; i < MAX_VERTEX; i++)
    {
        printf("\n%d: ", i);
        for (int j = 0; j < MAX_VERTEX; j++)
            printf("%4d ", M[i][j]);
    }
}

int main()
{
    MATRIX M = {
        {9999, 30, 25, 9999, 50},
        {30, 9999, 9999, 90, 30},
        {25, 9999, 9999, 40, 9999},
        {9999, 90, 40, 9999, 10},
        {50, 30, 9999, 10, 9999}};

    displayMatrix(M);

    int start = 0;
    int *distance = dijkstra(M, start);
    displayDistance(distance, start);

    return 0;
}