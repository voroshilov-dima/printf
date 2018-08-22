/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/04 11:54:13 by dvoroshy          #+#    #+#             */
/*   Updated: 2018/08/04 20:02:42 by dvoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include <stdarg.h>
#include <stdlib.h>

typedef struct	s_flags {
	char	*buf;
	int		space;
	int		minus;
	int		plus;
	int		hash;
	char	filler;
	int		length;
}				t_flags;

void init_flags(t_flags *flags)
{
	flags->space = 0;
	flags->minus = 0;
	flags->plus = 0;
	flags->hash = 0;
	flags->filler = ' ';
	flags->length = 0;
}

t_flags parse_args(const char *restrict s, int start, int end)
{
	t_flags	flags;
	init_flags(&flags);

	while (start <= end)
	{
		if (s[start] == ' ')
			flags.space += 1;
		else if (s[start] == '0')
			flags.filler = '0';
		else if (s[start] == '-')
			flags.minus = 1;
		else if (s[start] == '+')
			flags.plus = 1;
		else if (s[start] >= 49 && s[start] <= 57)
			flags.length = s[start] - 48;
		else if (s[start] == '#')
			flags.hash = 1;
		start++;
	}
	return (flags);
}

char get_type(char c)
{
	if (c == 's' ||
		c == 'S' ||
		c == 'p' ||
		c == 'd' ||
		c == 'D' ||
		c == 'i' ||
		c == 'o' ||
		c == 'O' ||
		c == 'u' ||
		c == 'U' ||
		c == 'x' ||
		c == 'X' ||
		c == 'c' ||
		c == 'C' ||
		c == '%')
		return (c);
	return (0);
}

int print_filler(t_flags *flags, int mode)
{
	int counter;

	counter = 0;
	if (flags->length > 0 && ((mode == -1 && flags->minus == 0) ||
							  (mode == 1  && flags->minus == 1)))
	{
		while (flags->length > (int)ft_strlen(flags->buf))
		{
			ft_putchar(flags->filler);
			counter++;
			flags->length--;
		}
	}
	return (counter);
}

int printing(char type, t_flags flags)
{
	int counter;

	counter = 0;
	
	if (flags.buf[0] != '-') // TO DO: not good
	{
		if (flags.plus)
		{
			ft_putchar('+');
			counter++;
		}
		else
		{
			while (flags.space-- > 0)
			{
				ft_putchar(' ');
				counter++;
			}
		}
	}

	counter += print_filler(&flags, -1);
	if (type == 'd' || type == 's' || type == 'c' || type == 'x' || type == 'X' || type == 'o' || type == 'u')
	{
		counter += printf("%s", flags.buf);
		fflush(stdout);
	}
	counter += print_filler(&flags, 1);

	
	return (counter);	
}

int print_one(char type, t_flags flags, va_list args)
{
	int counter = 0;

	if (type == 'd' || type == 'c' || type == 'x' || type == 'X' || type == 'o' || type == 'u')
	{
		flags.buf = ft_itoa(va_arg(args, int));
		//counter += print_number(type, flags, i);		
	}
	else if (type == 's')
	{
		flags.buf = va_arg(args, char *);
		//counter += printf("%s", s);
		//fflush(stdout);
	}
	else if (type == '%')
	{
		counter += printf("%%");
	}
	// if (flags.length > counter)
	// {
	// 	ft_putchar(' ');
	// 	counter++;
	// }
	
	return (printing(type, flags));
}

int	ft_printf(const char *restrict format, ...)
{
	va_list	args;
	t_flags	flags;
	int		counter;
	int		i;
	int		j;
	char	type;

	va_start(args, format);
	counter = 0;
	i = 0;
	while (format[i] != '\0')
	{	
		if (format[i] == '%')
		{
			j = 1;
			while (!(type = get_type(format[i + j])))
				j++;
			flags = parse_args(format, i, i + j);
			counter += print_one(type, flags, args);
			i += j;
		}
		else
		{
			ft_putchar(format[i]);
			counter++;
		}
		i++;
	}
	return (counter);
}
