/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpr_here_document.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maen-naj <maen-naj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 19:14:07 by maen-naj          #+#    #+#             */
/*   Updated: 2025/08/07 19:14:08 by maen-naj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	open_heredoc_fd(const char *file)
{
	int	fd;

	fd = open(file, O_CREAT | O_RDWR, 0644);
	if (fd == -1)
	{
		perror("minishell");
		exit(1);
	}
	return (fd);
}

int	handle_delimiter(int *no, int fd, t_data *data, char *file)
{
	if (!data->com || (ft_strcmp(data->com, data->limiters[*no]) == 0
			&& !data->limiters[*no + 1]))
	{
		if (!data->com)
			ft_print("minishell: warning: \
here-document delimited by end-of-file", 0);
		if (!data->com && data->limiters[*no + 1])
		{
			(*no)++;
			return (0);
		}
		close(fd);
		fd = open_heredoc_fd(file);
		data->fd = fd;
		data->i = *no + 1;
		heredoc_child_cleanup(data->limiters, file, data->com);
		exit(0);
	}
	return (1);
}

void	write_expanded(int fd, char *com, t_data *data)
{
	char		*arr_;
	t_indexes	indx;

	arr_ = expand_str(com, *(data->envp), data, indx);
	if (arr_)
	{
		write(fd, arr_, ft_strlen(arr_));
		free(arr_);
	}
	write(fd, "\n", 1);
}

static void	helper_process(t_data *data, char **limiters, int *j, int *no)
{
	*j = 0;
	*no = 0;
	data->com = NULL;
	data->limiters = limiters;
}

void	process_here_doc(t_data *data, char *file, char **limiters, int expand)
{
	int	fd;
	int	no;
	int	j;

	helper_process(data, limiters, &j, &no);
	fd = open_heredoc_fd(file);
	while (1)
	{
		data->com = readline("> ");
		if (handle_delimiter(&no, fd, data, file) == 0)
			continue ;
		if (expand && data->com[0] && limiters[no + 1] == NULL)
			write_expanded(fd, data->com, data);
		else if (!expand && data->com[0] && limiters[no + 1] == NULL)
		{
			write(fd, data->com, ft_strlen(data->com));
			write(fd, "\n", 1);
		}
		j++;
		if (data->com && ft_strcmp(data->com, limiters[no]) == 0)
			no++;
		free(data->com);
	}
}
