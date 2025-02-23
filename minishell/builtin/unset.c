#include "../minishell.h"

int	rmv_str_2d(char ***str2, char *rmv)
{
	char	**t;
	char	*temp;
	int		i;
	int		j;
	int		nitems;

	j = 0;
	nitems = str_len_2d(*str2);
	if (!rmv)
		return (0);
	if (isin_2d_delim((*str2), rmv, '=') == 0)
		return (0);
	t = malloc((nitems) * sizeof(char *));
	if (t == NULL)
		return (1);
	j = 0;
	i = 0;
	while ((*str2)[j])
	{
                temp = copy_until((*str2)[j], '=');
		if (!temp)
			return (cleanexit(t), 1);
		if(ft_strcmp(temp, rmv) != 0)
			t[i++] = ft_strdup((*str2)[j]);
                free(temp);
		j++;
	}
	t[i] = NULL;
	cleanexit(*str2);
	*str2 = t;
	return (0);
}

int     unset_valid(char *str)
{
	int r;

        // if (ft_strchr(str, '=') == NULL)
        //         return (0);
	if (str[0] >= '0' && str[0] <= '9')
		return (0);
	if (str[0] == '-' && str[1])
		return (3);
        r = ft_isalnum_under_plus(str);
        if (r == 2)
                return (0);
        return (r);
}

int     unset1(t_list *pip, char **str)
{
        int     i;

        i = 1;
        while (str[i])
        {
                if (unset_valid(str[i]) == 1)
                        rmv_str_2d(pip->data->envp, str[i]);
                else if (unset_valid(str[i]) == 0)
                        ft_printf_fd(2, "bash: unset: ʻ%s': not a valid identifier\n", str[i]);
                else if (unset_valid(str[i]) == 3)
                        ft_printf_fd(2, "bash: unset: %c%c: invalid option\n", str[i][0], str[i][1]);
                i++;
        }
}