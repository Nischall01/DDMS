#include <stdio.h>

void multiplyMatrices(int A[3][2], int B[3][2], int result[3][2])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            result[i][j] = 0;
            for (int k = 0; k < 2; k++)
            {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main()
{
    int A[3][2];
    int B[3][2];
    int result[3][2];

    printf("Enter values for matrix A (3x2):\n");
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            printf("Enter element A[%d][%d]: ", i, j);
            scanf("%d", &A[i][j]);
        }
    }

    printf("Enter values for matrix B (3x2):\n");
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            printf("Enter element B[%d][%d]: ", i, j);
            scanf("%d", &B[i][j]);
        }
    }

    multiplyMatrices(A, B, result);

    printf("Resultant matrix:\n");
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }

    return 0;
}
