// #include "minishell.h"
// #include <ctype.h>
// int is_operator(char c)
// {
//     if (c == '&' || c == '|')
//         return (1);
//     return -1;
// }
// int	operator_between_par(char *command)
// {
//     int i;
//     int operator;

//     i = 0;
//     while (command[i])
//     {
//         if(is_operator(command[i]) == 1)
//         {
//             i++;
//             if (is_operator(command[i]) == 1)
//                 i++;
            
//             operator++;
//         }
//         i++;
//     }
//     printf("op = %d\n",operator);
//     return -1;
// }

// int main()
// {
//     char tab0[] = "ls   &&    ls";
//     char tab1[] = "(  (ls)   &&   (ls) )";
//     char tab2[] = "(  ls   &&   (ls))";

//     char tab4[] = "(  ls      (ls))";
//     char tab5[] = "(  (ls)      (ls))";
//     char tab6[] = "(ls)";
//     char tab7[] = "ls";
//     char tab8[] = "((ls))";

//     char tab9[] = "( (ls)      (ls)   &&  ls)";
//     char tab10[] = "( (ls)   && ||  (ls)   &&  ls)";
//     char tab11[] = "( (ls)   &&   (ls)   && )";
//     char tab12[] = "( ls  && (ls && (ls)))";

//     printf("tab0 = %d\n",operator_between_par(tab0));
//     // printf("tab1 = %d\n",operator_between_par(tab1));
//     // printf("tab2 = %d\n",operator_between_par(tab2));
//     // printf("tab4 = %d\n",operator_between_par(tab4));
//     // printf("tab5 = %d\n",operator_between_par(tab5));
//     // printf("tab6 = %d\n",operator_between_par(tab6));
//     // printf("tab7 = %d\n",operator_between_par(tab7));
//     // printf("tab8 = %d\n",operator_between_par(tab8));
//     // printf("tab9 = %d\n",operator_between_par(tab9));
//     // printf("tab10 = %d\n",operator_between_par(tab10));
//     // printf("tab11 = %d\n",operator_between_par(tab11));

// }