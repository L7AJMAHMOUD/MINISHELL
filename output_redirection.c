#include "minishell.h"

void redirect_output_fd(char **command)
{
	int i;
	int fd;
	
 	i = 0;
	while (command[i])
	{
        printf("%s\n",command[i]);
		// if (ft_strcmp(command[i], ">") == 0)
		// {
		// 	fd = open(command[i + 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
		// 	command[i] = NULL;
		// 	dup2(fd, 1);
		// 	close(fd);
		// }
		i++;
	}
}