/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcart.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkaram <abkaram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 12:57:15 by abkaram           #+#    #+#             */
/*   Updated: 2025/06/26 12:58:34 by abkaram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char **wildcart(char **st, char **envp)
// {
// 	int i;
// 	int j;
// 	char *tmp;
// 	char **str;

// 	str = st;

// 	i = 0;
	
// 	while (str[i])
// 	{
// 		j  = 0;
// 		while (str[i][j])
// 		{
// 			if (str[i][j] == '$' && str[i][j + 1] != 32 && str[i][j + 1])
// 			{
// 				while(str[i][j] == '$')
// 				{
// 					j++;
// 					o++;
// 					if (str[i][j] != '$')
// 					{
// 						if (o % 2)
// 							o = -1;
// 					}
// 				}
// 				if (o != -1 || (str[i][j] <= 57 && str[i][j] >= 48))
// 				{
// 					st = regenerat_without_dol(st);
// 							return(dirham(st,envp));
// 				}
// 				else
// 				{
// 					while(envp[b])
// 					{
// 						tmp = ft_shearch(&str[i][j], envp[b++]);
// 						if (tmp)
// 						{
// 							st = regenerat_dol_with_env(st, envp[b - 1], i);
// 							b = -1;
// 							return(dirham(st,envp));
// 						}
// 					}
// 				}
// 				if (b != -1)
// 				{
// 					st = regenerat_dol_with_env_emply(st, i);
// 					while (str[i][j] && str[i][j + 1] != '$')
// 						j++;
// 				}
// 			}
// 			if (str[i][j])
// 				j++;
// 		}
// 		i++;
// 	}
// 	return st;
// }