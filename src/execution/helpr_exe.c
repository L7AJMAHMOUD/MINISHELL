#include "../../minishell.h"

char	*ft_strchr(const char *str, int c)
{
	size_t	i;

	i = 0;
	while (str[i] != (char)c && str[i])
		i++;
	if (str[i] == (char)c)
		return ((char *)str + i);
	return (NULL);
}

char	*print_access_error(char *path)
{
	if (access(path, F_OK) == 0)
		return (path);
	write(2, "minishell: ", 11);
	write(2, path, ft_strlen(path));
	write(2, ": No such file or directory\n", 28);
	exit (127);
}

char	*print_no_such_file_error(char *path)
{
	write(2, "minishell: ", 11);
	write(2, path, ft_strlen(path));
	write(2, ": No such file or directory\n", 28);
	exit (127);
}

char	*print_permission_denied_error(char *path)
{
	write(2, "minishell: ", 11);
	write(2, path, ft_strlen(path));
	write(2, ": Permission denied\n", 20);
	exit(-2);
}

char	*print_command_not_found_error(char *path)
{
	write(2, "minihell: ", 11);
	write(2, path, ft_strlen(path));
	write(2, ": command not found\n", 20);
	exit (127);
}
