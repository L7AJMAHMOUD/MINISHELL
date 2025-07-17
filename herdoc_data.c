/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maen-naj <maen-naj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 03:28:48 by maen-naj          #+#    #+#             */
/*   Updated: 2025/07/17 03:52:08 by maen-naj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int    dir_already_exist()
{
    DIR *directory;
    struct dirent *entry;

    directory = opendir("/tmp/");
    while ((entry = readdir(directory)) != NULL)
    {
        printf("%s\n", entry ->d_name);
        if (ft_strcmp(entry -> d_name, "HEREDOC_DIR_SYSTEMD") == 0)
            return -1;
    }
    closedir(directory);
    return 0;
}

void	here_doc_data()
{
    int i = 0 ;
    int d_exist = dir_already_exist();
    int f_exist = file_already_exist();
    int hed_files = 0;

    if (d_exist != -1)
    {
        i = fork();
        if (i == 0)
        {
            char *dir[3] = {"mkdir", "HEREDOC_DIR_SYSTEMD", NULL};
            chdir("/tmp/");
            execve("/bin/mkdir", dir, NULL);
        }
        waitpid(i, NULL, 0);
    }
	chdir("/tmp/HEREDOC_DIR_SYSTEMD");
	i = fork();
	if (i == 0)
	{
		char *fheredoc[3] = {"touch", "fre", NULL};
		execve("/usr/bin/touch", fheredoc, NULL);
	}
    waitpid(i, NULL, 0);
}

// int main()
// {
//     const char *path = "/tmp/HEREDOC_DIR_SYSTEMD";

//     here_doc_data();


// }