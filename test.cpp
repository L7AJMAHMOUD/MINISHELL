#include "minishell.h"
#include <ctype.h>
int is_operator(char c)
{
    if (c == '&' || c == '|')
        return (1);
    return -1;
}
int	operator_between_par(char *command)
{
    int i;
    int operator;
    int closed;

    i = 0;
    while (command[i])
    {
        if (command[i] == ')')
            closed = 1;
        if(is_operator(command[i]) == 1)
        {
            i++;
            if (is_operator(command[i]) == 1)
                i++;
            while (command[i] == ' ')
                i++;
            
        }
        i++;
    }
    printf("op = %d\n",operator);
    return -1;
}

int main()
{
    char tab1[] = "(  (ls)&&(ls) )";
    char tab2[] = "(  ls   &&   (ls))";

    char tab3[] = "(  ls      (ls))";
    char tab4[] = "(  (ls)      (ls))";
    char tab5[] = "(ls)";
    char tab6[] = "((ls))";

    char tab7[] = "( (ls)      (echo)   &&  ls)";
    char tab8[] = "( (ls)   && ||  (ls)   &&  ls)";
    char tab9[] = "( (ls)   &&   (ls)   && )";
    char tab10[] = "( ls  && (ls && (ls)))";
    char tab11[] = "( (ls)   &&   (echo)     ls)";

    printf("tab0 = %d\n",operator_between_par(tab1));

}