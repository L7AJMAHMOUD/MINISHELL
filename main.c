#include "minishell.h"

static int init_pwd(t_data *data)
{
    char buff[BUFFER_SIZE];

    if (!getcwd(buff, BUFFER_SIZE))
        return (ft_print("minishell: initialization failed", 0), 1);
    data->pwd = ft_strdup(buff);
    if (!data->pwd)
        return (ft_print("minishell: initialization failed", 0), 1);
    return (0);
}

static int init_env(t_data *data)
{
    data->path = ft_strdup("/usr/local/bin:/usr/local/sbin:/usr/bin:/usr/sbin:"
                           "/bin:/sbin");
    if (!data->path)
    {
        free(data->pwd);
        ft_print("minishell: initialization failed", 0);
        return (1);
    }
    data->pid = malloc(2000 * sizeof(int));
    if (!data->pid)
        return (free(data->pwd), free(data->path), ft_print("minishell: initialization failed", 0),
                1);
    data->status = 0;
    return (0);
}

int main(int ac, char **av, char **envp)
{
    t_data data = {0};

    if (ac == 2 && !ft_strcmp(av[1], "--version"))
        return (puts("minishell 1.0.0"), 0);
    if (ac == 2 && !ft_strcmp(av[1], "--help"))
        return (puts("Usage: minishell [--help | --version]\n"
                     "Read commands from the terminal or standard input."),
                0);
    if (ac != 1)
        return (ft_print("Usage: minishell [--help | --version]", 0), 2);
    data.interactive = isatty(STDIN_FILENO);
    setvbuf(stdout, NULL, _IONBF, 0);
    if (data.interactive)
    {
        read_history(".minishell_history");
        init_autosuggestions();
    }
    if (init_pwd(&data) || init_env(&data))
        return (1);
    envp = read_stock(envp, &data, 0, 0);
    if (!envp)
        return (free(data.pwd), free(data.path), free(data.pid), 1);
    read_input(&envp, &data);
    return (data.status);
}
