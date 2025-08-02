/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maen-naj <maen-naj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 03:28:48 by maen-naj          #+#    #+#             */
/*   Updated: 2025/07/17 06:03:45 by maen-naj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int file_already_exist()
{
    DIR *directory;
    int new_f = 0;
    int found = 1;
    struct dirent *entry;

    directory = opendir("/tmp/HEREDOC_DIR_SYSTEMD/");
    if (!directory)
        return -1;
    while (1)
    {
        found = 0;
        entry = readdir(directory);
        while (entry != NULL)
        {
            if (entry->d_name[0] == 'h' && atoi(entry->d_name + 1) == new_f)
            {
                found = 1;
                new_f++;
                break;
            }
            entry = readdir(directory);
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
    int pid = 0;
    int d_exist = dir_already_exist();
    int f_index;
    char *file_num;
    char *file_name;
    char *full_path;
    char *curr_wor_dir = malloc(100 * sizeof(char));

    if (!getcwd(curr_wor_dir, 100) || !curr_wor_dir)
        return NULL;

    if (d_exist != -1)
    {
        pid = fork();
        if (pid == -1)
        {
            perror("fork");
            exit(1);
        }
        else if (pid == 0)
        {
            char *dir[] = {"mkdir", "HEREDOC_DIR_SYSTEMD", NULL};
            if (chdir("/tmp/") == -1)
            {
                perror("chdir");
                exit(1);
            }
            if (execve("/bin/mkdir", dir, NULL) == -1)
            {
                perror("execve");
                exit(1);
            }
        }
        else
            waitpid(pid, NULL, 0);
    }

    if (chdir("/tmp/HEREDOC_DIR_SYSTEMD") == -1)
    {
        perror("chdir");
        return NULL;
    }
    f_index = file_already_exist();
    if (f_index == -1)
    {
        chdir(curr_wor_dir);
        return NULL;
    }

    file_num = ft_itoa(f_index);
    file_name = join_strings("h", file_num);
    full_path = join_strings("/tmp/HEREDOC_DIR_SYSTEMD/", file_name);

    free(file_num);
    free(file_name);
    chdir(curr_wor_dir);
    free(curr_wor_dir);

    return full_path;
}
