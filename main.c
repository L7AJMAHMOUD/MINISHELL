/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkaram <abkaram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:20:22 by maen-naj          #+#    #+#             */
/*   Updated: 2025/08/07 19:26:13 by abkaram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	isapure(void)
{
	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO))
		return (0);
	return (1);
}

// static int	is_not_tty(void)
// {
// 	if (isapure())
// 	{
// 		write(STDERR_FILENO,
// 			"minishell: error: non-TTY mode is not supported\n", 49);
// 		return (1);
// 	}
// 	return (0);
// }

static int	init_pwd(t_data *data)
{
	char	buff[BUFFER_SIZE];

	if (!getcwd(buff, BUFFER_SIZE))
		return (ft_print("minishell : Erreur initialisation", 0), 1);
	data->pwd = ft_strdup(buff);
	if (!data->pwd)
		return (ft_print("minishell : Erreur initialisation", 0), 1);
	return (0);
}

static int	init_env(t_data *data)
{
	data->path = ft_strdup(
			"/usr/local/bin:/usr/local/sbin:/usr/bin:/usr/sbin:"
			"/bin:/sbin"
			);
	if (!data->path)
	{
		free(data->pwd);
		ft_print("minishell : Erreur initialisation", 0);
		return (1);
	}
	data->pid = malloc(2000 * sizeof(int));
	if (!data->pid)
		return (free(data->pwd), free(data->path),
			ft_print("minishell : Erreur initialisation", 0), 1);
	data->status = 0;
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;

	(void)ac;
	(void)av;
	// if (is_not_tty())
	// 	return (1);
	if (ac == 1)
	{
		if (init_pwd(&data) || init_env(&data))
			return (1);
		envp = read_stock(envp, &data, 0, 0);
		if (!envp)
			return (free(data.pwd), free(data.path), 1);
		read_input(&envp, &data);
	}
	else
		invalid_param();
	return (0);
}
