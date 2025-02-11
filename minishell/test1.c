// #include "minishell.h"

// size_t	ft_strlen(const char *c)
// {
// 	size_t	i;

// 	i = 0;
// 	while (c[i] != '\0')
// 		i++;
// 	return (i);
// }

// int	echo_var(char *envp[], char *p1)
// {
// 	int		i;
// 	int		j;
//         int             k;
//         int             len_p1;

// 	i = 0;
//         k = 0;
//         len_p1 = ft_strlen(p1);
//         while (len_p1 > -1)
//         {
//                 if(isalnum(p1[len_p1 - 1]) == 0)
//                 {
//                         len_p1--;
//                         k++;
//                 }
//                 else
//                         break;
//         }
// 	while (envp[i])
// 	{
// 		j = 0;
// 		while (envp[i][j] == p1[j])
// 			j++;
// 		if (j == len_p1)
// 		{
// 			printf("%s",envp[i] + j + 1);
//                         printf("%s", p1 + len_p1);
//                         return (1);
// 		}
// 		i++;
// 	}
//         printf("%s", p1);
//         return (0);
// }

// int     main(int argc, char **argv, char **envp)
// {
//         echo_var(envp, argv[1]);
//         return (0);
// }
