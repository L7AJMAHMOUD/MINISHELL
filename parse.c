/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maen-naj <maen-naj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 12:01:45 by maen-naj          #+#    #+#             */
/*   Updated: 2025/05/15 12:05:19 by maen-naj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_spc(int cmd)
{
    if ((33 <= cmd && cmd <= 40) || (42 <= cmd && cmd <= 126))
        return (1);
    else
	    return (-1);
}

int is_something(char *cmd)
{
	int i = 0;
	if (!cmd || cmd[0] == '\0')
		return 0;
	while (cmd[i] == ' ' || cmd[i] == '\t')
		i++;
	if (!cmd[i])
		return 0;
	if (cmd[i] == '<' || cmd[i] == '>' || cmd[i] == '|' || cmd[i] == '&')
		return 0;
	return 1;
}

// 33 -> 37

// 39  -> 123


// 125 -> 126