#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


#define MAX_COUNT 200

void ParentProcess()
{
    for (int i = 0; i < MAX_COUNT; i++)
    {
        printf("This line is from parent, value = %d\n", i);
    }
}

void ChildProcess()
{
    for (int i = 0; i < MAX_COUNT; i++)
    {
        printf("This line is from child, value = %d\n", i);
    }
}

int main()
{
    printf("PID of main programm: %d\n", getpid());
    int pid = fork();
    if (pid != 0)
    {
        ParentProcess();
    }
    else
    {
        ChildProcess();
    }
    wait(0);

    return 0;
}
