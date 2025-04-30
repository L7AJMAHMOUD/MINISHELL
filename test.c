#include "minishell.h"

int is_operator(char c)
{
    if (c == '&' || c == '|')
        return (1);
    return -1;
}
int	operator_between_par(char *command)
{
    int i;
    int op;

    i = 0;
    op = 0;
    while (command[i])
    {
        if(is_operator(command[i]) == 1 && command[++i] == 1)
            op = 1;
        i++;
    }
    return -1;
}

int main()
{
    char tab0[] = "ls   &&   ls";
    char tab1[] = "(  (ls)   &&   (ls) )";
    char tab2[] = "(  ls   &&   (ls))";
    char tab4[] = "(  ls      (ls))";
    char tab5[] = "(  (ls)      (ls))";
    char tab6[] = "(ls)";
    char tab7[] = "ls";
    char tab8[] = "((ls))";
    char tab9[] = "(  (ls)      (ls)   &&  ls)";

    printf("tab 0 = %d\n",operator_between_par(tab2));

}