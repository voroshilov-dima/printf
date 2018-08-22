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

#define MINUS 0x00000001

typedef struct	s_flags {
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

int print_number(char type, t_flags flags, int i)
{
	int counter;

	counter = 0;
	
	if (flags.length > 0 && flags.minus == 0)
	{
		while (flags.length > (int)ft_strlen(ft_itoa(i)))
		{
			ft_putchar(flags.filler);
			counter++;
			flags.length--;
		}
		
	}

	if (i >= 0)
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
	
	
	if (type == 'd')
		counter += printf("%d", i);
	else if (type == 'c')
		counter += printf("%c", i);
	else if (type == 'x')
		counter += printf("%x", i);
	else if (type == 'X')
		counter += printf("%X", i);
	else if (type == 'o')
		counter += printf("%o", i);
	else if (type == 'u')
		counter += printf("%u", i);
	fflush(stdout);

	if (flags.length > 0 && flags.minus == 1)
	{
		while (flags.length > (int)ft_strlen(ft_itoa(i)))
		{
			ft_putchar(flags.filler);
			counter++;
			flags.length--;
		}
	}			
	return (counter);	
}

int print_one(char type, t_flags flags, va_list args)
{
	int counter = 0;

	if (type == 'd' || type == 'c' || type == 'x' || type == 'X' || type == 'o' || type == 'u')
	{
		int i = va_arg(args, int);
		counter += print_number(type, flags, i);		
	}
	else if (type == 's')
	{
		char* s = va_arg(args, char*);
		counter += printf("%s", s);
		fflush(stdout);
	}
	else if (type == '%')
	{
		counter += printf("%%");
	}
	else if (type == 'x')
	{
		int i = va_arg(args, int);
		printf("%x", i);
		counter += printf("%%");	
	}
	else if (type == 'x')
	{
		int i = va_arg(args, int);
		printf("%X", i);
		counter += printf("%%");	
	}
	if (flags.length > counter)
	{
		ft_putchar(' ');
		counter++;
	}
	return (counter);
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
