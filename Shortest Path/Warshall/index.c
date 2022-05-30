#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VERTEX 5
#define INF 9999

typedef int MATRIX[MAX_VERTEX][MAX_VERTEX];

int **Floyd(MATRIX M)
{
    // Create a matrix that will hold the shortest distances
    int **apsp = (int **)calloc(MAX_VERTEX, sizeof(int *));
    for (int i = 0; i < MAX_VERTEX; i++)
        apsp[i] = (int *)calloc(MAX_VERTEX, sizeof(int));

    // Copy the given matrix to apsp
    for (int i = 0; i < MAX_VERTEX; i++)
    {
        for (int j = 0; j < MAX_VERTEX; j++)
        {
            apsp[i][j] = M[i][j];
        }
    }

    // Set the diagonals as 0
    for (int i = 0; i < MAX_VERTEX; i++)
        apsp[i][i] = 0;

    // We need to loop all the vertices. This is the outer loop.
    for (int k = 0; k < MAX_VERTEX; k++)
    {
        // The 2 inner loops are used to traverse the matrix. [ROW X COL]
        for (int i = 0; i < MAX_VERTEX; i++)
        {
            for (int j = 0; j < MAX_VERTEX; j++)
            {

                apsp[i][j] = apsp[i][j] || apsp[i][k] && apsp[k][j];
            }
        }
    }

    return apsp;
}

void displayFloyd(int **M)
{
    printf("\n\n%3c", ' ');
    for (int i = 0; i < MAX_VERTEX; i++)
        printf("%4d ", i);

    for (int i = 0; i < MAX_VERTEX; i++)
    {
        printf("\n%d: ", i);
        for (int j = 0; j < MAX_VERTEX; j++)
            printf("%4d ", M[i][j]);
    }
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
        {INF, 30, 125, INF, 50},
        {30, INF, INF, 90, 30},
        {125, INF, INF, 40, INF},
        {INF, 90, 40, INF, 10},
        {50, 30, INF, INF, INF}};

    displayMatrix(M);

    int **apsp_floyd = Floyd(M);
    displayFloyd(apsp_floyd);

    return 0;
}
