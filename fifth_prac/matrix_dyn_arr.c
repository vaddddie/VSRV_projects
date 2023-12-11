#include <stdio.h>
#include <stdlib.h>

int main()
{
    int N;
    scanf("%d", &N);

    int **ptr = (int**) calloc(N, sizeof((int*) calloc(N, sizeof(int))));

    for (int i = 0; i < N; i++)
    {
        ptr[i] = (int*) calloc(N, sizeof(int));

        printf("Numbers: ");

        for (int j = 0; j < N; j++)
        {
            ptr[i][j] = i * j;
            printf("%d ", ptr[i][j]);
        }

        printf("Addresses: ");

        for (int j = 0; j < N; j++)
        {
            printf("%p ", &ptr[i][j]);
        }

        printf("\n");
    }

    free(ptr);

    return 0;
}
