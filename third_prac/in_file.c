#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main()
{
    char msg[50];
    int filedesc = open("delete_me.txt", O_CREAT | O_RDWR | O_TRUNC);
    scanf("%s", msg);
    write(filedesc, msg, strlen(msg));
    dup2(filedesc, 1);
    close(filedesc);

    return 0;
}
