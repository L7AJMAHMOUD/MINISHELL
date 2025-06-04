/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dirham.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkaram <abkaram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 06:00:23 by abkaram           #+#    #+#             */
/*   Updated: 2025/06/04 10:16:57 by abkaram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ //

// char **ft_regenerate_2arr(char **stro)
// {
// 	char **str;
// 	int i;
// 	int j;
// 	int len;

// 	i = 0;
// 	while(stro[i])
// 		i++;
// 	str = malloc ((i + 1) * sizeof(char *));
// 	i = 0;
// 	while (stro[i])
// 	{
// 		j = 0;
// 		while(stro[i][j] == 32)
// 			j++;
// 		len = ft_strlen(&stro[i][j]);
// 		str[i] = malloc(len + 1);
// 		while(stro[i][j])
// 			str[i][len++] = stro[i][j++];
// 		str[i][len] = 0;
// 		i++;
// 	}
// 	str[i] = 0;
// 	return str;	
// }

// char **regenerat_without_dol(char **stro)
// {
// 	char **str;
// 	int i;
// 	int j;

// 	i = 0;
// 	printf("hana\n");
// 	while(stro[i])
// 	{
// 		j = 0;
// 		while (stro[i][j] == '$')
// 			stro[i][j++] = 32;
// 		if (j != 0)
// 			break;
// 		i++;
// 	}
// 	str = ft_regenerate_2arr(stro);
// 	// free_all_ul_split(stro);
// 	return (str);
// }

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
// 		j  = 0;
// 		while (str[i][j])
// 		{
// 			if (str[i][j] == '$')
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
// 				if (o == -1)
// 				{
// 					str = regenerat_without_dol(str);
// 					break;
// 				}
// 				// else
// 				// {
// 				// 	while(envp[b])
// 				// 	{
// 				// 		tmp = ft_shearch(&str[i][j], envp[b++]);
// 				// 		if (tmp)
// 				// 		{
// 				// 			regenerat_dol_with_env();
// 				// 			b = -1;
// 				// 			break;
// 				// 		}
// 				// 	}
				
// 				// }
// 				// if (b == -1)
// 				// 	return_with_vide();
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// 	return str;
// }
