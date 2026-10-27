#include "../../minishell.h"

static int apply_one(t_node *node, t_data *data, int i)
{
    if (!ft_strcmp(node->command[i], ">"))
        return (redirect_output_fd(node->command, node->arr, data, i));
    if (!ft_strcmp(node->command[i], ">>"))
        return (append_to_fd(node->command, node->arr, data, i));
    if (!ft_strcmp(node->command[i], "<"))
        return (redirect_input_fd(node->command, node->arr, data, i));
    if (!ft_strcmp(node->command[i], "<<") && dup2(node->hd, STDIN_FILENO) < 0)
        return (perror("minishell: heredoc"), data->status = 1, -1);
    return (0);
}

char **apply_redirections(t_node *node, char ***envp, t_data *data)
{
    int i = 0;

    data->envp = envp;
    while (node->command && node->command[i])
    {
        if (!node->arr[i].q && !is_redirect(node->command[i]))
        {
            if (apply_one(node, data, i) == -1)
                return (free_all_ul_split(node->command), NULL);
            i++;
        }
        i++;
    }
    return (clean_command(node->command, node->arr));
}
