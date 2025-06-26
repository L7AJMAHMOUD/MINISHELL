#include "minishell.h"

// int main(void) {
//     DIR *dir = opendir(".");
//     struct dirent *entry;

//     if (!dir) {
//         perror("opendir");
//         return 1;
//     }

//     while ((entry = readdir(dir)) != NULL) {
//         printf("%s\n", entry->d_name);
//     }

//     closedir(dir);
//     return 0;
// }
