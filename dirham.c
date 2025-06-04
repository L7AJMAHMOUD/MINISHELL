/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dirham.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkaram <abkaram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 06:00:23 by abkaram           #+#    #+#             */
/*   Updated: 2025/06/04 08:53:05 by abkaram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ //

// char **dirham(char **str, char **envp)
// {
// 	int i;
// 	int j;
// 	int o;
// 	int b;
// 	char *tmp;

// 	i = 0;
// 	o = 0;
// 	j = 0;
// 	b = 0;
// 	while (str[i])
// 	{
// 		while (str[i][j])
// 		{
// 			if (str[i][j] == '$')
// 				break;
// 			j++;
// 			if (!str[i][j])
// 				return str;
// 		}
// 		i++;
// 	}
// 	i = 0;
// 	j = 0;
// 	if (str[j][i] == '$')
// 	{
// 		while(str[i][j] == '$')
// 		{
// 			j++;
// 			o++;
// 			if (str[i][j] != '$')
// 			{
// 				if (o % 2)
// 					o = -1;
// 			}
// 		}
// 		if (o == -1)
// 			regenerat_without_dol();
// 		else
// 		{
// 			while(envp[b])
// 			{
// 				tmp = ft_shearch(&str[i][j], envp[b++]);
// 				if (tmp)
// 				{
// 					regenerat_dol_with_env();
// 					b = -1;
// 					break;
// 				}
// 			}
		
// 		}
// 		if (b == -1)
// 			return_with_vide();
// 	}
// }
