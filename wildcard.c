/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maen-naj <maen-naj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 12:57:15 by abkaram           #+#    #+#             */
/*   Updated: 2025/07/06 17:37:33 by maen-naj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **add_in_array(char **st, char *cmd, int i)
{
	return NULL;
}
char **wildcart(char **str, char **envp)
{
	DIR *dir;
	struct dirent *entry;
	int i;
	int j;
	
	i = 0;
	while(str[i])
	{
		j = 0;
		while(str[i][j])
		{
			skip_inside_quotes(str[i], &j);
			if (str[i][j] == '*')
			{
				printf("\033[1;32m*** Welcome to SGF HHHH ***\033[0m\n");
				dir = opendir(".");
				if (!dir) {
					perror("opendir");
					return NULL;
				}
				while ((entry = readdir(dir)) != NULL)
					str = add_in_array(str, entry->d_name, i);
				closedir(dir);
				break;
			}
			if (str[i][j])
				j++;
		}
		i++;
	}
	return str;
}