# include "../minishell.h"

int     ft_isalldigit(char* str)
{
    int i;

    i = 0;
    printf("v2: %s\n", str);
    if (str[0] == '-' || str[0] == '+') 
        i++;     
    while(str[i])
    {
        if ((str[i] < 48 || str[i] > 57))
            return (0);        
        i++;
    }
    return (1);
}


int check_long_long(char *str)
{
       unsigned long long num;
       int i;


       i = 0;
       num = 0;
       if (str[i] == '+' || str[i] == '-')
               i++;
       while(str[i])
       {
               num = num * 10 + str[i] - 48;
               if ((num > 9223372036854775808ULL) || (num > 9223372036854775807) && str[i] != '-')
                       return(0);
               i++;
       }
       return(1);
}
int check_exit(char** str)
{
       if (str[1] == NULL)
               return(1);
        printf("%s\n", str[1]);
       if(ft_isalldigit(str[1]) == 0)
               return(printf("bash: exit: %s: numeric argument required\n", str[1]), 1);
       if(check_long_long(str[1]) == 0)
               return(printf("bash: exit: %s: numeric argument required\n", str[1]), 1);
       if(str[2] != NULL)
               return(printf("bash: exit: too many arguments\n"), 0);
       return(0);
}
