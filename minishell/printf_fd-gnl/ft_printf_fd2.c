/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smendez- <smendez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 18:52:23 by smendez-          #+#    #+#             */
/*   Updated: 2025/02/06 11:48:49 by smendez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	msize1(long int a, char *base)
{
	long int	lenb;
	long int	i;
	long int	b;

	i = 1;
	b = a;
	lenb = ft_strlen(base);
	if (a < 0)
	{
		b = -b;
		i++;
	}
	while (lenb <= b)
	{
		b = b / lenb;
		i++;
	}
	return (i);
}

static char	*motor1(long int nbr, char *base, char *final, int index)
{
	long int	size;
	long int	k;
	long int	nb;
	long int	i;

	size = ft_strlen(base);
	i = index;
	k = msize1(nbr, base) - 1;
	nb = nbr;
	if (nb < 0)
	{
		nb = -nb;
		final[i] = '-';
	}
	while (k > 0 && nb >= size)
	{
		final[k + i] = base[nb % size];
		nb = nb / size;
		k--;
	}
	final[k + i] = base[nb];
	return (final);
}

char	*ft_nbrchardec(int nbr, int unsigned1, char *mainmalloc, int index)
{
	char	*base;

	base = "0123456789";
	if (unsigned1 == 1)
	{
		mainmalloc = motor1((unsigned int)nbr, base, mainmalloc, index);
		return (mainmalloc);
	}
	mainmalloc = motor1(nbr, base, mainmalloc, index);
	return (mainmalloc);
}

int	ft_sizenbr_base(long int numb, char *base, int unsigned1)
{
	long int	i;
	long int	sizeb;

	i = 1;
	sizeb = ft_strlen(base);
	if (unsigned1 == 1)
	{
		numb = (unsigned int)numb;
	}
	if (numb == -2147483648)
		numb = -2147483647;
	if (numb < 0)
	{
		i++;
		numb = numb * -1;
	}
	if ((numb / sizeb) == 0)
		return (i);
	while ((numb / sizeb) > 0)
	{
		numb = numb / sizeb;
		i++;
	}
	return (i);
}

char	*ft_straddend1(char *malloc1, char *toadd, int index)
{
	int		i;
	int		j;
	char	*a;

	i = index;
	j = 0;
	a = "(null)";
	if (!toadd)
	{
		while (a[j])
		{
			malloc1[i + j] = a[j];
			j++;
		}
		return (malloc1);
	}
	while (toadd[j])
	{
		malloc1[i + j] = toadd[j];
		j++;
	}
	return (malloc1);
}
