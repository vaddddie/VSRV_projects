#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void Interruption();

int main()
{
    printf("I can be stopped with CRTL + C\n");
    sleep(3);

    signal(SIGINT, Interruption);
    printf("I can`t be stopped with CTRL + C\n");
    sleep(3);

    signal(SIGINT, SIG_DFL);
    printf("I can be stopped again with CTRL + C\n");
    sleep(3);

    printf("Goodbye\n");

    return 0;
}

void Interruption()
{
    printf(" No\n");
    sleep(1);
}
