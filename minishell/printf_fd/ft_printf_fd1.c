/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smendez- <smendez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 10:42:16 by smendez-          #+#    #+#             */
/*   Updated: 2025/02/06 11:48:49 by smendez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	sizearg(const char format, va_list args)
{
	int	j;

	j = 0;
	if (format == 'c')
	{
		(void)va_arg(args, int);
		j = 1;
	}
	else if (format == 's')
		j = ft_strlennull(va_arg(args, char *));
	else if (format == 'p')
		j = ft_print_adress(va_arg(args, void *));
	else if (format == 'd' || format == 'i')
		j = ft_sizenbr_base(va_arg(args, int), "0123456789", 0);
	else if (format == 'u')
		j = ft_sizenbr_base(va_arg(args, int), "0123456789", 1);
	else if (format == 'x')
		j = ft_sizenbr_base(va_arg(args, int), "0123456789abcdef", 1);
	else if (format == 'X')
		j = ft_sizenbr_base(va_arg(args, int), "0123456789ABCDEF", 1);
	else if (format == '%')
		j = 1;
	return (j);
}

char	*argchar(const char format, va_list args, char *mainmalloc, int index)
{
	if (format == 'c')
		mainmalloc[index] = (char)va_arg(args, int);
	else if (format == 's')
		mainmalloc = ft_straddend1(mainmalloc, va_arg(args, char *), index);
	else if (format == 'p')
		mainmalloc = ft_adresschar(va_arg(args, void *), mainmalloc, index);
	else if (format == 'd' || format == 'i')
		mainmalloc = ft_nbrchardec(va_arg(args, int), 0, mainmalloc, index);
	else if (format == 'u')
		mainmalloc = ft_nbrchardec(va_arg(args, int), 1, mainmalloc, index);
	else if (format == 'x')
		mainmalloc = ft_nbrcharhex(va_arg(args, int), "0123456789abcdef",
				mainmalloc, index);
	else if (format == 'X')
		mainmalloc = ft_nbrcharhex(va_arg(args, int), "0123456789ABCDEF",
				mainmalloc, index);
	else if (format == '%')
		mainmalloc[index] = '%';
	return (mainmalloc);
}

char	*printmotor(char *chr, const char *format, va_list args)
{
	va_list	args1;
	int		i;
	int		index;

	va_copy(args1, args);
	i = 0;
	index = 0;
	while (format[i])
	{
		if (format[i] == '%' && isformat(format[i + 1]))
		{
			chr = argchar(format[i + 1], args1, chr, index);
			index += sizearg(format[i + 1], args);
			i += 2;
		}
		else
			chr[index++] = format[i++];
	}
	chr[index] = '\0';
	va_end(args);
	va_end(args1);
	return (chr);
}

int	sizeprintf(const char *format, va_list args)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (format[i])
	{
		if (format[i] == '%' && isformat(format[i + 1]))
		{
			j += sizearg(format[i + 1], args);
			i += 2;
		}
		else
		{
			i++;
			j++;
		}
	}
	return (j);
}

int	ft_printf_fd(int fd, const char *format, ...)
{
	va_list	args;
	va_list	args1;
	char	*chr;
	int		sz;

	va_start(args, format);
	va_copy(args1, args);
	sz = sizeprintf(format, args);
	chr = malloc((sz + 1) * sizeof(char));
	if (!chr)
		return (0);
	chr = printmotor(chr, format, args1);
	ft_putstr_fd(chr, fd, sz);
	free(chr);
	return (sz);
}

/* #include <stdio.h>
int	main(void)
{
	int	result;
	int	result_native;
	char	c = '\0';
	char	*s = NULL;
	int a = -13634;
	//int *p = &a;
	// int t1 =  ft_printf("Our result      : %c   %s   %p %d %i %u %x %X%%|\n",
			
	c, s, s, a, a, a, a, a);
	// int t2 =     printf("Intended result : %c   %s   %p %d %i %u %x %X%%|\n",
	c, s, s, a, a, a, a, a);
	int t2 =     printf("|Intended result : %c%c%c|\n", '0', 0, '1');
	int t1 =  ft_printf("|Our result      : %c%c%c|\n", '0', 0, '1');
	printf("\nNcharacters\nOurs: %d\nintended: %d\n", t1, t2);
	return (0);
} */
/* #include <stdio.h>
#include <limits.h>

int	main(void)
{
    int res1, res2;

    // Test null pointer
    res1 = ft_printf("Custom: %p\n", NULL);
    res2 = printf("Native: %p\n", NULL);
    printf("Custom: %d, Native: %d\n\n", res1, res2);

    // Test valid pointer
    int x = 42;
    res1 = ft_printf("Custom: %p\n", &x);
    res2 = printf("Native: %p\n", &x);
    printf("Custom: %d, Native: %d\n\n", res1, res2);

    // Test LONG_MIN and LONG_MAX
    res1 = ft_printf("Custom: %p %p\n", (void *)LONG_MIN, (void *)LONG_MAX);
    res2 = printf("Native: %p %p\n", (void *)LONG_MIN, (void *)LONG_MAX);
    printf("Custom: %d, Native: %d\n\n", res1, res2);

    // Test ULONG_MAX
    res1 = ft_printf("Custom: %p\n", (void *)ULONG_MAX);
    res2 = printf("Native: %p\n", (void *)ULONG_MAX);
    printf("Custom: %d, Native: %d\n\n", res1, res2);

    return (0);
} */
