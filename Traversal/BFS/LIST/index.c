#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX 5
#define MAX 10 // n(n-1)/2
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
    EdgeType edges[MAX];
    int count;
} EdgeList;

typedef struct node
{
    int vertex;
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
            int u = E.edges[i].vertex;
            int v = E.edges[i].adj_vertex;

            temp = (NodePtr)calloc(sizeof(Node), 1);
            if (temp)
            {
                temp->vertex = v;
                temp->next = A[u];
                A[u] = temp;
            }

            // temp = (NodePtr)calloc(sizeof(Node), 1);
            // if (temp)
            // {
            //     temp->vertex = u;
            //     temp->next = A[v];
            //     A[v] = temp;
            // }
        }
    }
    return A;
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
}

void BFS_Iterative(AdjList A, int start)
{
    int queue[100];
    int front = 0, rear = -1;

    int visited[MAX_VERTEX] = {0};

    queue[++rear] = start;

    while (front <= rear)
    {
        int current = queue[front++];

        if (!visited[current])
        {
            visited[current] = 1;
            printf("%d ", current);
        }

        NodePtr trav;
        for (trav = A[current]; trav != NULL; trav = trav->next)
        {
            if (visited[trav->vertex] != 1)
            {
                queue[++rear] = trav->vertex;
            }
        }
    }
}

void BFS_Recursive(AdjList A, Queue *Q, int visited[], int current)
{
    if (!visited[current])
    {
        visited[current] = 1;
        printf("%d ", current);
    }

    NodePtr trav;
    for (trav = A[current]; trav != NULL; trav = trav->next)
    {
        if (visited[trav->vertex] != 1)
        {
            Q->queue[++Q->rear] = trav->vertex;
        }
    }

    if (Q->front <= Q->rear)
    {
        int next = Q->queue[Q->front++];
        BFS_Recursive(A, Q, visited, next);
    }
}

void BFS_Traversal(AdjList A, int start)
{
    Queue Q = {};
    Q.front = 0;
    Q.rear = -1;

    int visited[MAX_VERTEX] = {0};

    BFS_Recursive(A, &Q, visited, start);
}

int main()
{
    EdgeList E = {{{0, 4}, {1, 0}, {1, 3}, {2, 1}, {2, 3}, {3, 4}}, 6};
    int start = 2;

    AdjList A1 = createAL(E);
    display(A1);

    printf("\nI: ");
    BFS_Iterative(A1, start);

    printf("\nR: ");
    BFS_Traversal(A1, start);

    return 0;
}
