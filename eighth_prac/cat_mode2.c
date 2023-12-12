#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
	char buf;
	int fd_IN;

	if (argc == 2)
	{
		fd_IN = open(argv[1], O_RDONLY, 0644);
		close(0);
		dup(fd_IN);
	}

	while (read(STDIN_FILENO, &buf, 1) > 0)
	{
		write(STDOUT_FILENO, &buf, 1);
	}

	return 0;
}
