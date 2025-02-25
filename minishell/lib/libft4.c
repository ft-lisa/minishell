#include "../minishell.h"

char	*ft_strstr(char *str, char *to_find)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (to_find[i] == '\0')
		return (str);
	while (str[i] != '\0')
	{
		while (str[i + j] == to_find[j])
		{
			if (to_find[j + 1] == '\0')
			{
				return (&str[i]);
			}
			j++;
		}
		i++;
		j = 0;
	}
	return (0);
}

void	*ft_memcpy(void *dest_str, const void *src_str, size_t n)
{
	size_t			i;
	unsigned char	*ptr;
	const char		*src;

	if (n == 0)
		return (dest_str);
	if (dest_str == NULL && src_str == NULL)
		return (NULL);
	i = 0;
	ptr = dest_str;
	src = src_str;
	while (i < n)
	{
		ptr[i] = src[i];
		i++;
	}
	return (dest_str);
}

int	ft_isalnum(int c)
{
	if ((c > 64 && c < 91) || (c > 96 && c < 123) || (c > 47 && c < 58))
		return (1);
	else
		return (0);
}

int	count_c(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!str || !str[0] || !c)
		return (0);
	while(str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}
