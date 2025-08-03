#include "minishell.h"

static int	duplicate_envp_entry(char **str, char **envp, t_indexes *indx)
{
	str[indx->j] = malloc(ft_strlen(envp[indx->j]) + 1);
	if (!str[indx->j])
		return (free_all_ul_split(str), 1);
	while (envp[indx->j][indx->i])
	{
		str[indx->j][indx->i] = envp[indx->j][indx->i];
		indx->i++;
	}
	str[indx->j][indx->i] = '\0';
	return (0);
}

static int	duplicate_line_and_increment_index(char **str,
	char *ligne, t_indexes *indx)
{
	indx->i = 0;
	str[indx->j] = malloc(ft_strlen(ligne) + 1);
	if (!str[indx->j])
		return (free_all_ul_split(str), 1);
	while (ligne[indx->i])
	{
		str[indx->j][indx->i] = ligne[indx->i];
		indx->i++;
	}
	str[indx->j++][indx->i] = '\0';
	return (0);
}

static int	initialize_indexes_and_find_env(char **envp, char *ligne,
			t_indexes *indx, int p)
{
	if (!envp)
		return (1);
	indx->p = p;
	indx->k = 2;
	indx->m = find_env_var_index(envp, ligne, &indx->k);
	indx->j = 0;
	if (indx->p == 1 && indx->k == 2)
		return (1);
	return (0);
}

char	**add_to_envp(char **envp, char *ligne, int p, char		**str)
{
	t_indexes	indx;

	if (!ligne || initialize_indexes_and_find_env(envp, ligne, &indx, p))
		return (envp);
	str = malloc((envp_array_length(envp) + indx.k) * sizeof(char *));
	if (!str)
		return (envp);
	while (envp[indx.j])
	{
		indx.i = 0;
		if (indx.k == 1 && indx.j == indx.m
			&& is_prefix_equal_until_equal_sign(envp[indx.m], ligne))
		{
			if (duplicate_line_to_array(str, ligne, &indx))
				return (envp);
		}
		else
			if (duplicate_envp_entry(str, envp, &indx))
				return (envp);
		indx.j++;
	}
	if (indx.k == 2)
		if (duplicate_line_and_increment_index(str, ligne, &indx))
			return (envp);
	return (free_all_ul_split(envp), str[indx.j] = NULL, str);
}

char	*dup_env_line(char *line)
{
	char	*dup;
	int		i;

	dup = malloc(ft_strlen(line) + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (line[i])
	{
		dup[i] = line[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
