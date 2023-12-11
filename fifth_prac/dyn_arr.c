#include <stdio.h>
#include <stdlib.h>

int main()
{
    int N;
    scanf("%d", &N);

    int *ptr = (int*) calloc(N, sizeof(int));

    for (int i = 0; i < N; i++)
    {
        ptr[i] = i;
        printf("Number: %d, Address: %p\n", ptr[i], &ptr[i]);
    }

    free(ptr);
    return 0;
}
