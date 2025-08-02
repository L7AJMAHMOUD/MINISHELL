/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_applications.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkaram <abkaram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 14:35:50 by maen-naj          #+#    #+#             */
/*   Updated: 2025/07/30 10:58:30 by abkaram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_simple_redirs(t_node *node, t_data *data, int i)
{
	if (ft_strcmp(node->command[i], ">") == 0 && node->arr[i].q == 0)
		return (redirect_output_fd(node->command, node->arr, data));
	else if (ft_strcmp(node->command[i], ">>") == 0 && node->arr[i].q == 0)
		return (append_to_fd(node->command, node->arr, data));
	else if (ft_strcmp(node->command[i], "<") == 0 && node->arr[i].q == 0)
		return (redirect_input_fd(node->command, data));
	return (0);
}

int	handle_heredoc(t_node *node, t_data *data, t_indexes indx, int *i)
{
	int	s_p;
	int	s_po;

	s_p = dup(1);
	s_po = dup(0);
	if (indx.j != -1 && indx.i != -1)
	{
		dup2(indx.j, 1);
		dup2(indx.i, 0);
	}
	if (here_doc(node, *(data->envp), data) == -1 && node->arr[*i].q == 0)
		return (-1);
	*i += (data->i) * 2;
	*i -= 1;
	dup2(s_p, 1);
	dup2(s_po, 0);
	return (0);
}

int	save_check(int *s_in, int *s_out)
{
	*s_in = dup(0);
	*s_out = dup(1);
	if (*s_in == -1 || *s_out == -1)
		return (1);
	return (0);
}

char	**apply_redirections(t_node *node, char ***envp,
			t_data *data, t_indexes indx)
{
	static int	s_in;
	static int	s_out;
	int			i;

	i = 0;
	data->envp = envp;
	if (indx.p == 0)
	{
		if (save_check(&s_in, &s_out))
			return (free_all_ul_split(node->command), NULL);
		while (node->command[i])
		{
			data->i = 0;
			if (handle_simple_redirs(node, data, i) == -1)
				return (free_all_ul_split(node->command), NULL);
			else if (ft_strcmp(node->command[i], "<<") == 0
				&& node->arr[i].q == 0)
				if (handle_heredoc(node, data, indx, &i) == -1)
					return (free_all_ul_split(node->command), NULL);
			i++;
		}
		return (clean_command(node->command, node->arr));
	}
	if (s_in == 0 || s_out == 0 || dup2(s_in, 0) == -1 || dup2(s_out, 1) == -1)
		return (NULL);
	return (close(s_in), close(s_out), s_out = 0, s_in = 0, NULL);
}
