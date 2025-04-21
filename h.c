#include <unistd.h>

int main(void)
{
	char *av[] = {"ls", "&&", "ls", NULL};  // Correctly terminated argv
	execve("/bin/ls", av, NULL);     // Make sure path is right
	return 0;
}