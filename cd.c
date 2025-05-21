/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkaram <abkaram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 10:32:43 by abkaram           #+#    #+#             */
/*   Updated: 2025/05/21 13:44:32 by abkaram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkaram <abkaram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 10:53:15 by abkaram           #+#    #+#             */
/*   Updated: 2024/11/19 13:52:26 by abkaram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*strjoin(char *s1, char *s2)
{
	size_t	k;
	size_t	j;
	char	*str;

	j = 0;
	k = 0;
	if (!s2 && !s1)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (str == NULL)
		return (0);
	while (s1[j])
	{
		str[j] = s1[j];
		j++;
	}
	while (s2[k])
		str[j++] = s2[k++];
	str[j] = '\0';
	return (str);
}

void cd(char *arg)
{
	char buff[BUFFER_SIZE];
	char *tmp;
	char *str;
	
	if(!getcwd(buff,BUFFER_SIZE))
		perror("getcwd");
	tmp = strjoin(buff, "/");
	str = strjoin(tmp, arg);
	chdir (str);
	free(tmp);
	free(str);
}