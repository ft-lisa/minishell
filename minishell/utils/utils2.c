#include "../minishell.h"

char *del_c(char *str, char c)
{
        int i;
        int k;
        char *new_s;

        i = 0;
        k = 0;
        if (!str || str == NULL)
                return (NULL);
        while(str[i])
                if (str[i++] != c)
                        k++;
        if (k == 0)
                return (str);
        new_s = malloc((k + 1) * sizeof(char));
        if(!new_s)
                return (NULL);
        k = 0;
        i = 0;
        while(str[i])
        {
        if (str[i] != c) 
                new_s[k++] = str[i];
        i++;
        }
        new_s[k] = '\0';
        free(str);
        return (new_s);
}
