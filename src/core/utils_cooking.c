#include "minishell.h"

char	*ft_strjoin_(char *s1, char *s2)
{
	size_t	k;
	size_t	j;
	char	*str;

	j = 0;
	k = 0;
	if (!s2 && !s1)
		return (NULL);
	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
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
	return (free(s1), s1 = NULL, free(s2), s2 = NULL, str);
}

static void	free_commands_array(t_command *arr, int k)
{
	int	m;

	m = 0;
	while (m < k)
	{
		free(arr[m].command);
		arr[m++].command = NULL;
	}
	free(arr);
	arr = NULL;
}

int	allocate_next_command(t_command *arr, char *str, int *k, int j)
{
	arr[*k].command[j] = 0;
	*k += 1;
	arr[*k].command = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!arr[*k].command)
		return (free_arr(arr, *k - 1), 1);
	return (0);
}

int	complete_quoted_command(t_command *arr, char *str, t_indexes *ind)
{
	arr[ind->k].q = ind->c;
	while (str[ind->i] && str[ind->i] != ind->c)
		arr[ind->k].command[ind->j++] = str[ind->i++];
	if (str[ind->i] == ind->c)
		ind->i++;
	arr[ind->k].command[ind->j] = '\0';
	ind->k++;
	ind->j = 0;
	if (!str[ind->i])
	{
		arr[ind->k].command = NULL;
		arr->nbr = ind->k;
		return (2);
	}
	arr[ind->k].command = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!arr[ind->k].command)
		return (free_commands_array(arr, ind->k), 1);
	return (0);
}

int	handle_empty_quote_command(t_command *arr, t_indexes *indx, char *str)
{
	free(arr[indx->k].command);
	arr[indx->k].command = ft_strdup("''");
	if (!arr[indx->k].command)
		return (free_arr(arr, indx->k - 1), 1);
	indx->j = 0;
	indx->k++;
	arr[indx->k].command = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!arr[indx->k].command)
		return (free_commands_array(arr, indx->k), 1);
	return (0);
}
