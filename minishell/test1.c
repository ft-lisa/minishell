#include "minishell.h"

// char *del_c(char *str, char c)
// {
//     int i;
//     int k;
//     char *new_s;

//     i = 0;
//     while(str[i])
//         {
//             if (str[i++] != c)
//                 k++;
//         }
//     new_s = malloc(k * sizeof(char));
//     if(!new_s)
//         return (NULL);
//     k = 0;
//     i = 0;
//     while(str[i])
//     {
//         if (str[i] != c) 
//             new_s[k++] = str[i];
//         i++;
//     }
//     new_s[k] = '\0';
//     return (new_s);
// }

// int     main(int argc, char **argv)
// {
//         printf("%s\n", del_c(argv[1], argv[2][0]));
//         return (0);
// }