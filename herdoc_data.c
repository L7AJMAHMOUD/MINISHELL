/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maen-naj <maen-naj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 03:28:48 by maen-naj          #+#    #+#             */
/*   Updated: 2025/07/17 05:51:08 by maen-naj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int file_already_exist()
{
    DIR *directory;
    int new_f = 0;
    int found = 1;

    directory = opendir("/tmp/HEREDOC_DIR_SYSTEMD/");
    if (!directory)
        return -1;

    while (1)
    {
        struct dirent *entry;
        found = 0;

        while ((entry = readdir(directory)) != NULL)
        {
            if (atoi(entry->d_name) == new_f)
            {
                found = 1;
                new_f++;
                break;
            }
        }

        if (!found)
            break;

        closedir(directory);
        directory = opendir("/tmp/HEREDOC_DIR_SYSTEMD/");
        if (!directory)
            return -1;
    }
    closedir(directory);
    return new_f;
}
int    dir_already_exist()
{
    DIR *directory;
    struct dirent *entry;

    directory = opendir("/tmp/");
    if (!directory)
        return -1;
    while ((entry = readdir(directory)) != NULL)
    {
        if (ft_strcmp(entry -> d_name, "HEREDOC_DIR_SYSTEMD") == 0)
        {
            closedir(directory);
            return -1;
        }
    }
    closedir(directory);
    return 0;
}

char *here_doc_data()
{
    int i = 0;
    int d_exist = dir_already_exist();
    int f_index;
    char *file_num;
    char *file_name;

    if (d_exist != -1)
    {
        i = fork();
        if (i == 0)
        {
            char *dir[] = {"mkdir", "HEREDOC_DIR_SYSTEMD", NULL};
            chdir("/tmp/");
            execve("/bin/mkdir", dir, NULL);
            perror("mkdir failed");
            exit(1);
        }
        waitpid(i, NULL, 0);
    }

    chdir("/tmp/HEREDOC_DIR_SYSTEMD");

    f_index = file_already_exist();
    if (f_index != -1)
    {
        file_num = ft_itoa(f_index);
        i = fork();
        if (i == 0)
        {
            char *fheredoc[] = {"touch", file_num, NULL};
            execve("/usr/bin/touch", fheredoc, NULL);
            perror("touch failed");
            free(file_num);
            exit(1);
        }
        waitpid(i, NULL, 0);
    }
    else
        return NULL;

    file_num = ft_itoa(f_index);
    file_name = ft_strjoin("H", file_num);
    free(file_num);
    return file_name;
}

// int main()
// {
//     char *t[] = {"cat", "<<", "0"};
    
//     here_doc_data(t);


// }