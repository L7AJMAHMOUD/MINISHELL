/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkaram <abkaram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:34:41 by abkaram           #+#    #+#             */
/*   Updated: 2025/05/05 11:04:41 by abkaram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int main(int argc, char **argv, char **envp)
// {
// 	int id;
// 	int i;
// 	int j;
// 	int pipfd[2];
// 	pid_t pid;
// 	char *p = NULL;
// 	char *path;
// 	int fd[2];
// 	if (argc != 5)
// 		return (errno = EINVAL, perror("Erreur ! "), 1);
// 	i  = pipe(pipfd);
// 	if (i == -1)
// 		return (perror("Erreur de fork"), 1);
// 	fd[0] = open(argv[1], O_RDONLY);
// 	fd[1] = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644); /////////verifi si fd == -1  //////khas nvirefie wach origin readonly
// 	i = j = 0;
// 	pid = fork();
// 	pid_t pid1 = fork();
// 	if (pid < 0) {
// 		perror("Erreur de fork");
// 		return 1;
// 	}
// 	// unlink(argv[4]);
// 	if (pid == 0 && pid1 != 0) {
// 		if (fd[1] == -1)
// 			return (errno = EACCES, perror(argv[4]), 1);
// 		close (pipfd[1]);
// 		path = find_path(argv[3], envp);	
// 		dup2(fd[1] ,STDOUT_FILENO);
// 		dup2( pipfd[0], STDIN_FILENO);
// 		char **pi = ft_split(argv[3], ' ');;
// 		i = execve(path, pi ,envp);
// 		free(path);
// 		exit (1);
// 	}
// 	else if (pid1 == 0 && pid != 0)
// 	{
// 		if (fd[0] == -1)
// 			return (errno = ENOENT, perror(argv[1]), exit(1), 1);
// 		close (pipfd[0]);
// 		path = find_path(argv[2], envp);	
// 		dup2(fd[0],STDIN_FILENO);
// 		dup2(pipfd[1], STDOUT_FILENO);
// 		char **pi = ft_split(argv[2], ' ');
// 		i = execve(path, pi ,envp);
// 		free(path);
// 		exit (1);
// 	}
// 	else
// 	{
// 		close(pipfd[0]);
// 		close(pipfd[1]);
// 		waitpid(pid, NULL, 0);
// 		waitpid(pid1, NULL, 0);
// 	}
// 	return 0;
// }
