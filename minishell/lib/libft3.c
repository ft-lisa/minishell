#include "../minishell.h"

char	*ft_strchr(const char *str, int search_str)
{
	int				i;
	unsigned char	s_str;

	i = 0;
	s_str = (unsigned char)search_str;
	while (str[i] != s_str && str[i] != '\0')
		i++;
	if (str[i] == s_str)
		return ((char *)(str + i));
	else
		return (NULL);
}

int	ft_isalnum_under_plus(char *str)
{
        int     i;
        char    c;

        i = 0;
        while (str[i])
        {
                c = str[i];
                if ((c > 64 && c < 91) || (c > 96 && c < 123) || (c > 47 && c < 58) ||
                        c == '_')
                        i++;
                else
                        break;
        }
        if (str[i] && str[i] == '+' && str[i + 1] == '\0')
                return (2);
        else if (str[i] == '\0')
                return (1);
        else
                return (0);
	
}

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strcat(char *dest, const char *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (dest[j] != '\0')
		j++;
	while (src[i] != '\0')
	{
		dest[j + i] = src[i];
		i++;
	}
	dest[j + i] = '\0';
	return (dest);
}

char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (i != n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}
