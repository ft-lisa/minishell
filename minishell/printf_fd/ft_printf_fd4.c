/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smendez- <smendez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:30:01 by smendez-          #+#    #+#             */
/*   Updated: 2025/02/06 11:48:49 by smendez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*motoradress(unsigned long address, char *mainmalloc, int index)
{
	unsigned long	tmp;
	int				j;

	j = 0;
	tmp = address;
	while (tmp)
	{
		j++;
		tmp /= 16;
	}
	while (j-- > 0)
	{
		mainmalloc[index + j] = "0123456789abcdef"[address % 16];
		address /= 16;
	}
	return (mainmalloc);
}

char	*ft_adresschar(void *ptr, char *mainmalloc, int index)
{
	unsigned long	address;
	char			*nil1;
	int				i;

	address = (unsigned long)ptr;
	nil1 = "(nil)";
	i = 0;
	if (!ptr)
	{
		while (nil1[i])
		{
			mainmalloc[index + i] = nil1[i];
			i++;
		}
		return (mainmalloc);
	}
	mainmalloc[index++] = '0';
	mainmalloc[index++] = 'x';
	mainmalloc = motoradress(address, mainmalloc, index);
	return (mainmalloc);
}

int	isformat(const char c)
{
	int		i;
	char	*set;

	i = 0;
	set = "cspdiuxX%";
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	ft_print_adress(void *ptr)
{
	unsigned long	address;
	int				size;

	address = (unsigned long)ptr;
	if (!ptr)
		return (5);
	size = 2;
	while (address)
	{
		address /= 16;
		size++;
	}
	return (size);
}

int	ft_putstr_fd(char *s, int fd, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (s[i] == '\0')
			write(fd, "\0", 1);
		else
			write(fd, &s[i], 1);
		i++;
	}
	return (i);
}
