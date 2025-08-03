#include "minishell.h"

static void	skip_dollar_signs(t_command *arr, int *i, int *j, int *p)
{
	while (arr[*i].command[*j] == '$')
	{
		*j = *j + 1;
		*p = *p + 1;
	}
}

static void	helprs_handl_dol(int *p, int *m, int j)
{
	*p = 0;
	*m = j;
}

static void	helprs_handl_doll(t_indexes *indx, int p, int i)
{
	indx->i = i;
	indx->p = p;
}

static void	handle_positional(t_command *arr, int i, t_indexes *indxx, int *j)
{
	remove_positional_parameter(arr, i, &indxx->p, *j);
	*j = indxx->m;
}

void	handle_dollar(t_command *arr, int i, int j, t_data *data)
{
	t_indexes	indx;
	t_indexes	indxx;

	while (arr[i].command[j])
	{
		if (arr[i].command[j++] == '$')
		{
			helprs_handl_dol(&indxx.p, &indxx.m, j);
			skip_dollar_signs(arr, &i, &j, &indxx.p);
			if (arr[i].command[j] <= 32 && !arr[i + 1].command)
				continue ;
			if (arr[i].q == 39 || indxx.p % 2
				|| (arr[i].command[j] >= '0' && arr[i].command[j] <= '9'))
			{
				handle_positional(arr, i, &indxx, &j);
			}
			else if (arr[i].command[j] == '?')
				expand_exit_status(arr, i, &j, indxx.p);
			else
			{
				helprs_handl_doll(&indx, indxx.p, i);
				expand_env_variable(arr, indx, &j, data);
			}
		}
	}
}
