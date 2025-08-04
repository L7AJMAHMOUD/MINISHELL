#include "../../minishell.h"

char	*check_executable_or_error(char *tmp, char *path)
{
	if (access(tmp, X_OK) == 0)
		return (tmp);
	return (print_permission_denied_error(path));
}

char	*find_executable_in_path(char **envp, t_data *data, char *path, int *j)
{
	int		i;
	int		k;
	char	*tmp;

	i = find_path_index(envp);
	if (i == -1 && !data->path)
		return (print_access_error(path));
	if (i == -1)
		envp[i] = data->path;
	*j = 5;
	while ((size_t) * j < ft_strlen(envp[i]))
	{
		tmp = strdup_until_char(&envp[i][*j], ':', &k);
		if (!tmp)
			return (NULL);
		*j += k;
		tmp = strjoin_with_slash(tmp, path);
		if (!tmp)
			return (NULL);
		if (access(tmp, F_OK) == 0)
			return (check_executable_or_error(tmp, path));
		free(tmp);
	}
	return (print_command_not_found_error(path));
}

void print_is_a_directory_error(char *path)
{
	write(2, "minishell: ", 11);
	write(2, path, ft_strlen(path));
	write(2, ": is a directory\n", 17);
	exit(126);
}
