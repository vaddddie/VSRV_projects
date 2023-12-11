#include <stdio.h>
#include <stdlib.h>

int NullCount(int array[], int len, int *mult)
{
    int count = 0;
    *mult = 1;

    for (int i = 0; i < len; i++)
    {
        if (array[i] == 0)
        {
            count++;
            continue;
        }
        *mult *= array[i];
    }

    return count;
}

int main()
{
    int array[] = {0, 1, 0, 2, 0, 3, 0, 4, 0, 5, 0};
    int len = sizeof(array) / sizeof(int);
    int mult;

    int count = NullCount(array, len, &mult);
    printf("The number of zeros: %d. Multiplication: %d\n", count, mult);

    return 0;
}
