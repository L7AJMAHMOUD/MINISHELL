/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user01 <user01@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:44:11 by maen-naj          #+#    #+#             */
/*   Updated: 2025/04/19 22:43:57 by user01           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void    and_or(char *command)
{
    int i;

    i = 0;
    while  (command[i + 1])
    {
        if ((command[i] == '&' && command[i + 1] == '&') 
        || (command[i] == '|' && command[i + 1] == '|'))
        {
            
        }
        i++;
    }
}
int dsq_detector(char *command)
{
    int i;
    int count;
    int c;

    i = 0;
    count = 0;
    c = 0;
    while (command[i])
    {
        if (command[i] == '"' || command[i] == '\'')
        {
            if (c == 0)
                c = command[i];
            if (c == command[i]) 
                count++;
            if(count == 2)
                c = 0;
        }
        i++;
    }
    return (count);
}
void    pipe_detector(char *command)
{
    int i;

    i = 0;
    while (command[i])
    {
		if (i == 0)
		{
			while (command[i] == ' ')
                i++;
			if(command[i] == '|')
				printf("SYNTAX ERROR \n");
		}
        if(command[i] == '|')
        {
            while (command[++i] == ' ')
                i++;
            if (command[i] == '\0')
                printf("SYNTAX ERROR \n");
        }
        i++;
    }
}

void    command_analyze(char *command)
{
    int sdq;

    sdq = dsq_detector(command);
    if (sdq % 2 != 0)
        printf("SYNTAX ERROR \n");
    pipe_detector(command);
    and_or(command);
}
char	*ft_strdup(char *src )
{
	size_t	i;
	char	*h;

	i = 0;
	h = malloc(ft_strlen(src) * sizeof(char) + 1);
	if (!h)
		return (0);
	while (src[i])
	{
		h[i] = src[i];
		i++;
	}
	h[i] = '\0';
	return (h);
}

char	*ft_strjoin(char *s1, char *s2)
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
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 2);
	if (str == NULL)
		return (0);
	while (s1[j])
	{
		str[j] = s1[j];
		j++;
	}
	str[j++] = 32;
	while (s2[k])
		str[j++] = s2[k++];
	str[j] = '\0';
	return (free(s1), free(s2), str);
}

int	ft_strleen(const char *str, int c)
{
	int		i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != c)
		i++;
	return (i);
}


char	*ft_strduup(const char *src, int c, int *i)
{
	char	*h;

	*i = 0;
	if (!src)
		return (0);
	if (!src[*i])
		return NULL;
	h = malloc(ft_strleen(src, c) * sizeof(char) + 1);
	if (!h)
		return (0);
	while (src[*i] && src[*i] != c)
	{
		h[*i] = src[*i];
		*i += 1;
	}
	h[*i] = '\0';
	*i += 1;
	return (h);
}

t_node node_null(void)
{
	t_node node;
	
	node.command = 0;
	node.flags = 0;
    node.arg = 0;
	node.pipe = 0;
   	node.flag = 0;
	node.and = 0;
	node.or = 0;
    node.next = 0;

	return node;
}

void    command_tokenization(char *command)
{
	int i;
	int j;
	t_node node;
	char *str;
	i = 0;
	// if (ft_strstr(command, " | "))
		// {pipex}
	node = node_null();
	if (ft_strstr(command, "&&"))
	{
		node.and = 1;
		command_tokenization(ft_strstr(command, "&&"));
	}
	if (ft_strstr(command, "||"))
	{
		node.or = 1;
		command_tokenization(ft_strstr(command, "||"));
	}
	if (ft_strstr(command, "-"))
		node.flag = 1;
	while(command[i])
	{
		j = 0;
		while (command[i] == ' ')
			i++;
		if (!node.command)
			node.command = ft_strduup(&command[i], 32, &j);
		i = i + j;
		j = 0;
		if (node.flag == 1)
		{
			while (command[i] != '-')
					i++;
			node.flags = ft_strduup(&command[i], ' ', &j);
			i = i + j;
			j = 0;
		}
		while (node.flag == 1 && node.flags)
		{
			while (command[i] != '-' && command[i])
				i++;
			str = ft_strduup(&command[i], ' ', &j);
			if (!str)
				break;
			node.flags = ft_strjoin(node.flags, str);	
			i = i + j;
			j = 0;
		}
		if (node.and == 1 && command[i] == '&')
			break;
		if (node.or == 1 && command[i] == '|')
			break;
		i++;
	}
	printf("command = %s\n", node.command);
	printf("flags = %s\n", node.flags);
}

void    read_input()
{
    char *command;

    while (1)
    {
        command = readline("▄︻デ══━一💥 > ");
        if (!command)
            break ;
        if (command && *command)
            add_history(command);
        // command_analyze(command);
		command_tokenization(command);
    }
}
