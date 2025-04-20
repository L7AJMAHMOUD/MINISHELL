

#include "minishell.h"


void    and_or(char *command)
{
    int i;

    i = 0;
    while  (command[i])
    {
        if (command[i] == '&')
        {
            if (command[i + 1] == '&')
                return ;
            else
                printf("bash: syntax error near unexpected token `&'\n");
        }
        i++;
    }
}
int dsq_detector(char *command)
{
    int i;
    int count;
    int c;

    i = 0;
    count = 0;
    c = 0;
    while (command[i])
    {
        if (command[i] == '"' || command[i] == '\'')
        {
            if (c == 0)
                c = command[i];
            if (c == command[i]) 
                count++;
            if(count == 2)
                c = 0;
        }
        i++;
    }
    return (count);
}
void    pipe_detector(char *command)
{
    int i;

    i = 0;
    while (command[i])
    {
		if (i == 0)
		{
			while (command[i] == ' ')
                i++;
			if(command[i] == '|')
				printf("SYNTAX ERROR \n");
		}
        if(command[i] == '|')
        {
            while (command[++i] == ' ')
                i++;
            if (command[i] == '\0')
                printf("SYNTAX ERROR \n");
        }
        i++;
    }
}

void    command_analyze(char *command)
{
    int sdq;

    sdq = dsq_detector(command);
    if (sdq % 2 != 0)
        printf("SYNTAX ERROR \n");
    pipe_detector(command);
    and_or(command);
}

void    read_input()
{
    char *command;
	t_node *node;

    while (1)
    {
        command = readline("▄︻デ══━一💥 > ");
        if (!command)
            break ;
        if (command && *command)
            add_history(command);
        // if(command_analyze(command) == 0);
			node = command_tokenization(command);
		while(node)
		{
			printf("command : %s\n", node->command);
			printf("flags : %s\n", node->flags);
			printf("arg : %s\n", node->arg);
			printf("---------\n");
			node = node->next; 
		}
    }
}
