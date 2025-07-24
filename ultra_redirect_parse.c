/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ultra_redirect_parse.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maen-naj <maen-naj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 16:09:37 by maen-naj          #+#    #+#             */
/*   Updated: 2025/07/24 21:47:20 by maen-naj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ultra_redirect_parse(char *command)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = ft_strstr_pare(command);
	if (!command)
		return (1);
	if (tmp)
		command = tmp;
	while (command[i])
	{
		if (command[i] == 32)
			j++;
		i++;
	}
	if (i == j)
		return (1);
	i = 0;
	if (ft_strstr(command, "&&"))
		return (ultra_redirect_parse(ft_strstr(command, "&&")));
	else if (ft_strstr(command, "||"))
		return (ultra_redirect_parse(ft_strstr(command, "||")));
	return (i);
}

int	ultra_redirect_parsee(char *command)
{
	int	i;

	i = 0;
	while (command[i])
	{
		skip_inside_quotes(command, &i);
		if (command[i++] == ')')
		{
			while (command[i] == 32)
				i++;
			if (command[i] && (command[i] != PIPE_CHAR
					&& command[i] != '&' && command[i] != ')'))
				return (1);
		}
	}
	return (0);
}
