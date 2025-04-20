#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
	execve("/usr/bin/ls", argv + 1, NULL);
	return 0;
}
