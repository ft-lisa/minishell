#include "../minishell.h"

static char	*remove_surrounding_quotes(const char *s)
{
	size_t	len;
	char	*res;

	len = strlen(s);
	if (len >= 2 && ((s[0] == '\"' && s[len - 1] == '\"') ||
		(s[0] == '\'' && s[len - 1] == '\'')))
	{
		res = malloc(len - 1);
		if (!res)
			return (NULL);
		ft_memcpy(res, s + 1, len - 2);
		res[len - 2] = '\0';
		return (res);
	}
	res = strdup(s);
	return (res);
}

static char	*process_backslashes(const char *s)
{
	size_t	i;
	size_t	j;
	char	*res;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == '\\' && s[i + 1])
		{
			i += 2;
			j++;
		}
		else
		{
			i++;
			j++;
		}
	}
	res = malloc(j + 1);
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == '\\' && s[i + 1])
		{
			res[j++] = s[i + 1];
			i += 2;
		}
		else
			res[j++] = s[i++];
	}
	res[j] = '\0';
	return (res);
}

char	*parcing_export(char *str)
{
	char	*eq;
	char	*key;
	char	*value;
	char	*tmp;
	char	*res;
	size_t	key_len;

	eq = ft_strchr(str, '=');
	if (!eq)
		return (ft_strdup(str));
	key_len = (size_t)(eq - str);
	key = malloc(key_len + 1);
	if (!key)
		return (NULL);
	ft_strncpy(key, str, key_len);
	key[key_len] = '\0';
	value = remove_surrounding_quotes(eq + 1);
	if (!value)
	{
		free(key);
		return (NULL);
	}
	tmp = process_backslashes(value);
	free(value);
	if (!tmp)
	{
		free(key);
		return (NULL);
	}
	res = malloc(ft_strlen(key) + ft_strlen(tmp) + 2);
	if (!res)
	{
		free(key);
		free(tmp);
		return (NULL);
	}
	ft_strcpy(res, key);
	ft_strcat(res, "=");
	ft_strcat(res, tmp);
	free(key);
	free(tmp);
	return (res);
}

int     export_valid(char *str)
{
        char **temp;
	int r;

        // if (ft_strchr(str, '=') == NULL)
        //         return (0);
	if (str[0] >= '0' && str[0] <= '9')
		return (0);
	if (str[0] == '-' && str[1])
		return (3);
        temp = ft_split(str, '=');
        if (!temp)
                return (-1);
        r = ft_isalnum_under_plus(temp[0]);
        cleanexit(temp);
        return (r);
}

static char	*extract_key(char *s)
{
	char	*p;
	char	*key;
	size_t	len;

	p = ft_strstr(s, "+=");
	if (!p)
		return (NULL);
	len = p - s;
	key = malloc(len + 1);
	if (!key)
		return (NULL);
	ft_strncpy(key, s, len);
	key[len] = '\0';
	return (key);
}

static int	update_existing(char ***env, char *key, char *new_val)
{
	int		i;
	size_t	klen;
	char	*old;
	char	*comb;
	char	*entry;

	klen = ft_strlen(key);
	i = 0;
	while ((*env)[i])
	{
		if (strncmp((*env)[i], key, klen) == 0 && (*env)[i][klen] == '=')
		{
			old = (*env)[i] + klen + 1;
			comb = malloc(ft_strlen(old) + ft_strlen(new_val) + 1);
			if (!comb)
				return (-1);
			ft_strcpy(comb, old);
			ft_strcat(comb, new_val);
			entry = malloc(ft_strlen(key) + 1 + ft_strlen(comb) + 1);
			if (!entry)
			{
				free(comb);
				return (-1);
			}
			ft_strcpy(entry, key);
			ft_strcat(entry, "=");
			ft_strcat(entry, comb);
			free(comb);
			free((*env)[i]);
			(*env)[i] = entry;
			return (1);
		}
		i++;
	}
	return (0);
}

int	add_plus(char ***env, char *add)
{
	char	*key;
	char	*new_val;
	int		ret;
	char	*entry;

	key = extract_key(add);
	if (!key)
		return (0);
	new_val = add + (ft_strlen(key) + 2);
	ret = update_existing(env, key, new_val);
	if (ret == 1)
	{
		free(key);
		return (1);
	}
	if (ret == -1)
	{
		free(key);
		return (0);
	}
	entry = malloc(strlen(key) + 1 + strlen(new_val) + 1);
	if (!entry)
	{
		free(key);
		return (0);
	}
	ft_strcpy(entry, key);
	ft_strcat(entry, "=");
	ft_strcat(entry, new_val);
	free(key);
	if (add_last_2d(env, entry) != 0)
	{
		free(entry);
		return (0);
	}
	free(entry);
	return (1);
}

// int	add_plus_fixed(char ***str2, char *add)
// {
// 	char	*temp;

// 	add_plus(str2, temp);
// 	temp = (remove_surrounding_quotes())
// }

void export1(t_list *pip, char **str)
{
        int     i;
        char    *temp;

        i = 1;
        if (!str[1])
                while ((*(pip->data->envp))[i])
			ft_printf_fd(1, "%s\n", (*(pip->data->envp))[i++]);
        else
        {
                while(str[i])
                {
                        temp = parcing_export(str[i]);
			// printf("str |%s| parced |%s| \n", str[i], temp);
                        if (export_valid(str[i]) == 2)
                                add_plus(pip->data->envp, temp);
                        else if (export_valid(str[i]) == 1)
                                add_last_2d(pip->data->envp, temp);
			else if (export_valid(str[i]) == 0)
			{
				ft_printf_fd(2, "bash: export: ʻ%s': not a valid identifier\n", str[i]);
				pip->data->new_exit = 1;
			}
			else if (export_valid(str[i]) == 3)
			{
				ft_printf_fd(2, "bash: export: %c%c: invalid option\n", str[i][0], str[i][1]);
				pip->data->new_exit = 2;
			}
                        if (temp)
                                free(temp);
			// if (export_valid(str[i]) == 3 || export_valid(str[i]) == 0)
			// 	break;
                        i++;
                }
        }
}
