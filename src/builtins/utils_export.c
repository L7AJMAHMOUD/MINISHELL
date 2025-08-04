#include "../../minishell.h"

int	strcmp_until_equal(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] && s1[i] != '=')
		i++;
	if ((s1[i] == '=' && !s2[i]) || (s2[i] == '=' && !s1[i]))
		return (0);
	return (*(unsigned char *)(s1 + i) - *(unsigned char *)(s2 + i));
}

int	find_env_var_index(char **envp, char *ligne, int *k)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!strcmp_until_equal(envp[i], ligne))
		{
			*k = 1;
			return (i);
		}
		i++;
	}
	return (0);
}

int	is_prefix_equal_until_equal_sign(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] && s1[i] != '=')
		i++;
	if ((s1[i] == '=' && s2[i] != '=') || (!s1[i] && !s2[i]))
		return (0);
	return (1);
}

int	envp_array_length(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

int	duplicate_line_to_array(char **str, char *ligne, t_indexes *indx)
{
	str[indx->j] = malloc(ft_strlen(ligne) + 1);
	if (!str[indx->j])
		return (free_all_ul_split(str), 1);
	while (ligne[indx->i])
	{
		str[indx->j][indx->i] = ligne[indx->i];
		indx->i++;
	}
	str[indx->j][indx->i] = '\0';
	return (0);
}
