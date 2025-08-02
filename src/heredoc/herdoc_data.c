/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maen-naj <maen-naj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 03:28:48 by maen-naj          #+#    #+#             */
/*   Updated: 2025/07/17 06:03:45 by maen-naj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	file_already_exist(DIR *directory, int new_f, int found,
		struct dirent *entry)
{
	directory = opendir("/tmp/HEREDOC_DIR_SYSTEMD/");
	if (!directory)
		return (-1);
	while (1)
	{
		found = 0;
		entry = readdir(directory);
		while (entry != NULL)
		{
			if (entry->d_name[0] == 'h' && atoi(entry->d_name + 1) == new_f)
			{
				found = 1;
				new_f++;
				break ;
			}
			entry = readdir(directory);
		}
		if (!found)
			break ;
		closedir(directory);
		directory = opendir("/tmp/HEREDOC_DIR_SYSTEMD/");
		if (!directory)
			return (-1);
	}
	return (closedir(directory), new_f);
}

int	dir_already_exist(void)
{
	DIR				*directory;
	struct dirent	*entry;

	directory = opendir("/tmp/");
	if (!directory)
		return (-1);
	entry = readdir(directory);
	while (entry != NULL)
	{
		if (ft_strcmp(entry->d_name, "HEREDOC_DIR_SYSTEMD") == 0)
		{
			closedir(directory);
			return (-1);
		}
		entry = readdir(directory);
	}
	closedir(directory);
	return (0);
}

char	*create_heredoc_path(int f_index)
{
	char	*file_num;
	char	*file_name;
	char	*full_path;

	file_num = ft_itoa(f_index);
	file_name = join_strings("h", file_num);
	full_path = join_strings("/tmp/HEREDOC_DIR_SYSTEMD/", file_name);
	free(file_num);
	free(file_name);
	return (full_path);
}

void	create_heredoc_dir_if_needed(int d_exist)
{
	int		pid;
	char	*dir[3];

	dir[0] = "mkdir";
	dir[1] = "HEREDOC_DIR_SYSTEMD";
	dir[2] = NULL;
	if (d_exist == -1)
		return ;
	pid = fork();
	if (pid == -1)
		exit(1);
	else if (pid == 0)
	{
		if (chdir("/tmp/") == -1)
			exit(1);
		if (execve("/bin/mkdir", dir, NULL) == -1)
			exit(1);
	}
	waitpid(pid, NULL, 0);
}

char	*here_doc_data(int pid, char *file_num, char *file_name,
		char *full_path)
{
	int		d_exist;
	int		f_index;
	char	*curr_wor_dir;

	d_exist = dir_already_exist();
	curr_wor_dir = malloc(100 * sizeof(char));
	if (!curr_wor_dir || !getcwd(curr_wor_dir, 100))
		return (NULL);
	create_heredoc_dir_if_needed(d_exist);
	if (chdir("/tmp/HEREDOC_DIR_SYSTEMD") == -1)
	{
		perror("chdir");
		return (NULL);
	}
	f_index = file_already_exist(NULL, 0, 1, NULL);
	if (f_index == -1)
	{
		free(curr_wor_dir);
		chdir(curr_wor_dir);
		return (NULL);
	}
	full_path = create_heredoc_path(f_index);
	chdir(curr_wor_dir);
	free(curr_wor_dir);
	return (full_path);
}
