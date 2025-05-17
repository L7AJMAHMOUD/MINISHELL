#include "minishell.h"

int ultra_redirect_parse(char *command)
{
	int i;
	int j;
	
	char *tmp;
	i = 0;
	j = 0;
	if (!command)
		return (1);
	tmp = ft_strstr_pare(command);
	if (tmp)
		command = tmp;
	while (command[i])
	{
		if (command[i] == 32)
			j++;
		i++;
	}
	if (i == j)
		return (1);
	i = 0;
	if (ft_strstr(command, "&&"))
		return(ultra_redirect_parse(ft_strstr(command, "&&")));
	else if (ft_strstr(command, "||"))
		return(ultra_redirect_parse(ft_strstr(command, "||")));
	return (i);
}

int ultra_redirect_parsee(char *command)
{
	int i;
	i = 0;
	while(command[i])
	{
		skip_inside_quotes(command, &i);
		if (command[i++] == ')')
		{
			while(command[i] == 32)
				i++;
			if(command[i] && (command[i] != '|' && command[i] != '&' && command[i] != ')'))
				return 1;
		}
	}
	return 0;
}
