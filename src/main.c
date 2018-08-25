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

typedef struct	s_format {
	char	*str;
	char	type;
	int		space;
	int		minus;
	int		plus;
	int		hash;
	char	filler;
	int		width;
	int		length;
	int		z;
	int		j;
}				t_format;

typedef struct	s_argument {
	char	*str;
	int		sign;
}				t_argument;

typedef struct	s_print {
	t_format	fmt;
	t_argument	arg;
}				t_print;

static int	ft_length(long long int n)
{
	int len;

	len = 0;
	while (n && ++len)
		n = n / 10;
	return (len);
}

static int	ft_ulength(unsigned long long int n)
{
	int len;

	len = 0;
	while (n && ++len)
		n = n / 10;
	return (len);
}

static int	ft_abs(long long int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

char		*ft_itoa_base(long long int n, int base)
{
	int		i;
	int		len;
	char	*str;

	base = 0;
	i = 0;
	len = ft_length(n);
	str = 0;
	if (n <= 0)
		len++;
	if ((str = (char *)malloc(sizeof(char) * (len + 1))))
	{
		str[len] = 0;
		if (n == 0 && (str[0] = '0'))
			return (str);
		if (n < 0)
			str[0] = '-';
		while (n && i < len)
		{
			str[len - i - 1] = ft_abs(n % 10) + 48;
			n = n / 10;
			i++;
		}
	}
	return (str);
}

char		*ft_utoa_base(long long unsigned int n, int base)
{
	int		i;
	int		len;
	char	*str;

	base = 0;
	i = 0;
	len = ft_ulength(n);
	str = 0;
	if ((str = (char *)malloc(sizeof(char) * (len + 1))))
	{
		str[len] = 0;
		if (n == 0 && (str[0] = '0'))
			return (str);
		while (n && i < len)
		{
			str[len - i - 1] = ft_abs(n % 10) + 48;
			n = n / 10;
			i++;
		}
	}
	return (str);
}

void init_structure(t_print *print)
{
	print->fmt.type = 0;
	print->fmt.space = 0;
	print->fmt.plus = 0;
	print->fmt.minus = 0;
	print->fmt.hash = 0;
	print->fmt.filler = ' ';
	print->fmt.width = 0;
	print->fmt.length = 0;
	print->fmt.z = 0;
	print->fmt.j = 0;

	print->arg.str = "xxxx";
	print->arg.sign = 1;
}

void get_type(int *i, const char *restrict format, t_print *print)
{
	int		j;
	char	type;

	j = 0;
	type = 0;
	while (format[*i + j])
	{
		type = format[*i + j];
		if (type == 's' ||
			type == 'S' ||
			type == 'p' ||
			type == 'd' ||
			type == 'D' ||
			type == 'i' ||
			type == 'o' ||
			type == 'O' ||
			type == 'u' ||
			type == 'U' ||
			type == 'x' ||
			type == 'X' ||
			type == 'c' ||
			type == 'C' ||
			type == '%')
		{
			print->fmt.str = ft_strsub(format, *i, j);
			print->fmt.type = type;
			*i += j;
			return ;
		}
		j++;
	}
	printf("Usage: xxxx\n");
	exit(1);	
}



void parse_format(t_format *fmt)
{
	int	i;

	i = 0;
	while (fmt->str[i])
	{
		if (fmt->str[i] == ' ' && fmt->type == 'd')
			fmt->space += 1;
		else if (fmt->str[i] == '-')
			fmt->minus = 1;
		else if (fmt->str[i] == '+' && fmt->type == 'd')
			fmt->plus = 1;
		else if (fmt->str[i] == '0' && fmt->minus != 1 && fmt->type != 's') // TO DO: rework
			fmt->filler = '0';
		else if (fmt->str[i] >= 49 && fmt->str[i] <= 57)
			fmt->width = ft_atoi(fmt->str + i); // TO DO: rework
		else if (fmt->str[i] == 'l')
			fmt->length++;
		else if (fmt->str[i] == 'h')
			fmt->length--;
		else if (fmt->str[i] == '#')
			fmt->hash = 1;
		else if (fmt->str[i] == 'z')
			fmt->z = 1;
		else if (fmt->str[i] == 'j')
			fmt->j = 1;
		i++;
	}
}

void parse_signed_number(t_print *print, va_list args)
{	
	if (print->fmt.z == 1)
		print->arg.str = ft_itoa_base(va_arg(args, size_t), 10);
	else if (print->fmt.j == 1)
		print->arg.str = ft_itoa_base(va_arg(args, intmax_t), 10);
	else if (print->fmt.length == 0)
		print->arg.str = ft_itoa_base((int)va_arg(args, int), 10);
	else if (print->fmt.length == 1)
		print->arg.str = ft_itoa_base((long)va_arg(args, long int), 10);
	else if (print->fmt.length == 2)
		print->arg.str = ft_itoa_base(va_arg(args, long long int), 10);
	else if (print->fmt.length == -1)
		print->arg.str = ft_itoa_base((short)va_arg(args, int), 10);
	else if (print->fmt.length == -2)
		print->arg.str = ft_itoa_base((char)va_arg(args, int), 10);
	
	// важно, будет ли минус в финальной строке,
	// а не изначальной, пример printf("%   hhd", 128);
	if (print->arg.str[0] == '-')
		print->arg.sign = -1;
}

void parse_unsigned_number(t_print *print, va_list args)
{	
	if (print->fmt.j == 1)
		print->arg.str = ft_utoa_base(va_arg(args, uintmax_t), 10);
	else if (print->fmt.length == 0)
		print->arg.str = ft_utoa_base(va_arg(args, unsigned int), 10);
	else if (print->fmt.length == 1)
		print->arg.str = ft_utoa_base(va_arg(args, long unsigned int), 10);
	else if (print->fmt.length == 2)
		print->arg.str = ft_utoa_base(va_arg(args, long long unsigned int), 10);
}

void parse_char(t_print *print, va_list args)
{
	int	number;
	number = va_arg(args, int);
	print->arg.str = (char *)malloc(sizeof(char) * 2);
	print->arg.str[0] = number;
	print->arg.str[1] = 0;
}

void parse_percent(t_print *print)
{
	print->arg.str = (char *)malloc(sizeof(char) * 2);
	print->arg.str[0] = '%';
	print->arg.str[1] = 0;
}

void parse_string(t_print *print, va_list args)
{
	char	*str;
	str = va_arg(args, char *);
	print->arg.str = str;
}

void parse_argument(t_print *print, va_list args)
{
	
	if (print->fmt.type == 'd')
		parse_signed_number(print, args);
	else if (print->fmt.type == 'u')
		parse_unsigned_number(print, args);
	else if (print->fmt.type == 'c')
		parse_char(print, args);
	else if (print->fmt.type == '%')
		parse_percent(print);
	else if (print->fmt.type == 's')
		parse_string(print, args);
}

void	insert_string(char *src, char *dest, int place)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[place + i] = src[i];
		i++;
	}
}

void	apply_width(t_print *print)
{
	int		initial_length;
	int		filler_length;
	char	*new_str;
	int		i;

	i = 0;
	initial_length = ft_strlen(print->arg.str);
	filler_length = print->fmt.width - initial_length;
	if (filler_length > 0)
	{

		new_str = (char *)malloc(sizeof(char) * (initial_length + filler_length + 1));
		new_str[initial_length + filler_length] = 0;
		if (print->fmt.minus)
		{
			insert_string(print->arg.str, new_str, i);
			i += initial_length;
			while (i < initial_length + filler_length)
				new_str[i++] = print->fmt.filler;
		}
		else
		{
			// TO DO: govnokod
			if (print->fmt.filler == '0' && print->arg.sign == -1)
			{
				new_str[i++] = '-';
				while (i < filler_length + 1)
					new_str[i++] = print->fmt.filler;
				insert_string(print->arg.str + 1, new_str, i);
			}
			else if (print->fmt.filler == '0' && print->fmt.plus == 1)
			{
				new_str[i++] = '+';
				while (i < filler_length + 1)
					new_str[i++] = print->fmt.filler;
				insert_string(print->arg.str + 1, new_str, i);
			}
			else
			{
				while (i < filler_length)
					new_str[i++] = print->fmt.filler;
				insert_string(print->arg.str, new_str, i);
			}

			
			
		}
		print->arg.str = new_str;
	}
}

void	apply_plus(t_print *print)
{
	int		initial_length;
	char	*new_str;

	initial_length = ft_strlen(print->arg.str);
	if (print->arg.sign == 1 &&
		print->fmt.plus == 1)
	{
		new_str = (char *)malloc(sizeof(char) * (initial_length + 1 + 1));
		new_str[0] = '+';
		new_str[initial_length + 1] = 0;
		insert_string(print->arg.str, new_str, 1);
		print->arg.str = new_str;
	}
}

void	apply_spaces(t_print *print)
{
	int		initial_length;
	char	*new_str;
	int		i;

	i = 0;
	initial_length = ft_strlen(print->arg.str);
	if (print->arg.sign == 1 &&
		print->fmt.plus == 0 &&
		print->fmt.minus == 0 &&
		print->fmt.space > 0)
	{

		new_str = (char *)malloc(sizeof(char) * (initial_length + print->fmt.space + 1));
		while (i < print->fmt.space)
			new_str[i++] = ' ';
		new_str[initial_length + print->fmt.space] = 0;
		insert_string(print->arg.str, new_str, i);
		print->arg.str = new_str;
	}
}


void	apply_formats(t_print *print)
{
	apply_spaces(print);
	apply_plus(print);
	apply_width(print);
}

int	printing(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		ft_putchar(str[i++]);
	return (i);
}

int	process_input(int *i, const char *restrict format, va_list args)
{
	int		counter;
	t_print	print;

	counter = 0;
	init_structure(&print);
	get_type(i, format, &print);
	parse_format(&(print.fmt));
	parse_argument(&print, args);
	apply_formats(&print);
	return (printing(print.arg.str));
}

int	ft_printf(const char *restrict format, ...)
{
	va_list		args;
	int			i;
	int			counter;
	
	va_start(args, format);
	i = 0;
	counter = 0;
	while (format[i] != '\0')
	{	
		if (format[i] == '%')
		{
			i++;
			counter += process_input(&i, format, args);
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
