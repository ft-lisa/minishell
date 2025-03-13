#include "../minishell.h"

static char	*remove_surrounding_quotes(const char *s)
{
	size_t	len;
	char	*res;

	len = strlen(s);
	if (len >= 2 && ((s[0] == '\"' && s[len - 1] == '\"') ||
		(s[0] == '\'' && s[len - 1] == '\'')))
	{
		res = malloc(len - 1); // good
		if (!res)
			return (NULL);
		ft_memcpy(res, s + 1, len - 2);
		res[len - 2] = '\0';
		return (res);
	}
	res = strdup(s);
	return (res);
}

char* m_process_backslashes(const char *s)
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
	return(res);
}

static char	*process_backslashes(const char *s)
{
	size_t	i;
	size_t	j;
	char	*res;


	i = 0;
	j = 0;
	res = m_process_backslashes(s);
	if (!res)
		return(NULL);
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

char	*parcing_export_2(char *value, char* key, char* res)
{
	char* tmp;

	tmp = process_backslashes(value);
	free(value);
	if (!tmp)
		return (free(key), NULL);
	res = malloc(ft_strlen(key) + ft_strlen(tmp) + 2);
	if (!res)
		return (free(key), free(tmp), NULL);
	ft_strcpy(res, key);
	ft_strcat(res, "=");
	ft_strcat(res, tmp);
	free(key);
	free(tmp);
	return(res);
}

char	*parcing_export(char *str, size_t key_len)
{
	char	*eq;
	char	*key;
	char	*value;
	char	*tmp;
	char	*res;
	

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
		return (free(key), NULL);
	
	return (parcing_export_2(value, key, res));
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

char* update_existing_2(char ***env, char *key, char *comb, int i)
{
	char* entry;

	entry = malloc(ft_strlen(key) + 1 + ft_strlen(comb) + 1);
	if (!entry)
		return (free(comb), NULL);
	ft_strcpy(entry, key);
	ft_strcat(entry, "=");
	ft_strcat(entry, comb);
	free(comb);
	free((*env)[i]);
	(*env)[i] = entry;
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
			entry = update_existing_2(env, key, comb, i);
			if(!entry)
				return(-1);
			return (1);
		}
		i++;
	}
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
		return (free(key), 1);
	if (ret == -1)
		return (free(key), 0);
	entry = malloc(strlen(key) + 1 + strlen(new_val) + 1);
	if (!entry)	
		return (free(key), 0);
	ft_strcpy(entry, key);
	ft_strcat(entry, "=");
	ft_strcat(entry, new_val);
	free(key);
	if (add_last_2d(env, entry) != 0)	
		return (free(entry), 0);
	
	return (free(entry), 1);
}
void export2(t_list *pip, char **str, int i)
{
	char* temp;

	temp = parcing_export(str[i], 0);
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
                        
}


void export1(t_list *pip, char **str)
{
        int     i;

        i = 1;
        if (!str[1])
                while ((*(pip->data->envp))[i])
			ft_printf_fd(1, "%s\n", (*(pip->data->envp))[i++]);
        else
        {
                while(str[i])
                {
			export2(pip, str, i);
			i++;
                }
        }
}
