#include <unistd.h>

int main(int argc, char *argv[]) 
{
	char buf;

	while (read(STDIN_FILENO, &buf, 1) > 0)
	{
		write(STDOUT_FILENO, &buf, 1);
	}

	return 0;
}
