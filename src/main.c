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

#include "ft_printf.h"

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
	print->fmt.precision = -1;
	print->fmt.z = 0;
	print->fmt.j = 0;

	print->arg.str = "xxxx";
	print->arg.sign = 1;
}

void parse_char(t_print *print, va_list args)
{
	int	number;
	number = va_arg(args, int);
	print->arg.len = 1;
	print->arg.str = (char *)malloc(sizeof(char) * print->arg.len);
	print->arg.str[0] = number;
}

void parse_percent(t_print *print)
{
	print->arg.str = (char *)malloc(sizeof(char) * 1);
	print->arg.str[0] = '%';
	print->arg.len = 1;
}

void parse_string(t_print *print, va_list args)
{
	char	*str;
	str = va_arg(args, char *);
	if (str == NULL)
	{
		print->arg.len = 6;
		print->arg.str = (char *)malloc(sizeof(char) * print->arg.len);
		print->arg.str[0] = '(';
		print->arg.str[1] = 'n';
		print->arg.str[2] = 'u';
		print->arg.str[3] = 'l';
		print->arg.str[4] = 'l';
		print->arg.str[5] = ')';
	}
	else
	{
		print->arg.str = str;
		print->arg.len = ft_strlen(print->arg.str);	
	}
}

void parse_argument(t_print *print, va_list args)
{
	if (print->fmt.type == 'd')
		parse_signed_decimal(print, args);
	else if (print->fmt.type == 'u')
		parse_unsigned_decimal(print, args);
	else if (print->fmt.type == 'U') // TO DO: govno
		parse_unsigned_long(print, args);
	else if (print->fmt.type == 'x' || print->fmt.type == 'X')
		parse_hex(print, args);
	else if (print->fmt.type == 'o')
		parse_octal(print, args);
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
	int		filler_length;
	char	*new_str;
	int		i;

	i = 0;
	filler_length = print->fmt.width - print->arg.len;
	if (filler_length > 0)
	{
		new_str = (char *)malloc(sizeof(char) * (print->arg.len + filler_length));
		if (print->fmt.minus)
		{
			insert_string(print->arg.str, new_str, i);
			i += print->arg.len;
			while (i < print->arg.len + filler_length)
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
		print->arg.len += filler_length;
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
		print->arg.len++;
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
		insert_string(print->arg.str, new_str, i);
		new_str[initial_length + print->fmt.space] = 0;
		print->arg.str = new_str;
		print->arg.len = ft_strlen(print->arg.str);
	}
}

void	apply_hash(t_print *print)
{
	char	*new_str;

	if ((print->fmt.type == 'x' || print->fmt.type == 'X') && print->fmt.hash == 1 && ft_atoi(print->arg.str) != 0)
	{
		new_str = (char *)malloc(sizeof(char) * (print->arg.len + 2 + 1));
		new_str[0] = '0';
		new_str[1] = 'x';
		insert_string(print->arg.str, new_str, 2);
		new_str[print->arg.len + 2] = 0;
		print->arg.str = new_str;
		print->arg.len += 2;
	}
	else if (print->fmt.type == 'o' && print->fmt.hash == 1)
	{
		new_str = (char *)malloc(sizeof(char) * (print->arg.len + 1 + 1));
		new_str[0] = '0';
		insert_string(print->arg.str, new_str, 1);
		new_str[print->arg.len + 1] = 0;
		print->arg.str = new_str;
		print->arg.len += 1;
	}
}

void	apply_case(t_print *print)
{
	int i;

	if (print->fmt.type == 'X')
	{
		i = 0;
		while (print->arg.str[i])
		{
			print->arg.str[i] = ft_toupper(print->arg.str[i]);
			i++;
		}
	}
}

void	apply_precision(t_print *print)
{
	char	*new_str;
	int		initial_length;
	int		i;

	if (print->fmt.precision != -1 && print->fmt.type != 'c')
	{
		i = 0;
		if (print->fmt.type == 's')
		{
			new_str = (char *)malloc(sizeof(char) * (print->fmt.precision + 1));
			while (i < print->fmt.precision)
			{
				 new_str[i] = print->arg.str[i];
				 i++;
			}
			new_str[i] = 0;
			print->arg.str = new_str;			
		}
		else
		{
			initial_length = ft_strlen(print->arg.str);
			if (print->fmt.precision > initial_length)
			{
				new_str = (char *)malloc(sizeof(char) * (print->fmt.precision + 1));
				while (i < print->fmt.precision - initial_length)
					new_str[i++] = '0';
				insert_string(print->arg.str, new_str, i);
				new_str[print->fmt.precision] = 0;
				print->arg.str = new_str;
			}
			else if (print->fmt.precision == 0 && ft_atoi(print->arg.str) == 0 && print->fmt.type != '%')
			{
				new_str = (char *)malloc(sizeof(char));
				new_str[0] = 0;
				print->arg.str = new_str;
			}
		}
		print->arg.len = ft_strlen(print->arg.str);
	}
}

void	apply_formats(t_print *print)
{
	apply_precision(print);
	apply_hash(print);
	apply_spaces(print);
	apply_plus(print);
	apply_width(print);
	apply_case(print);
}

int	printing(t_print *print)
{
	int i;

	i = 0;
	while (i < print->arg.len)
	{
		ft_putchar(print->arg.str[i]);
		i++;
	}
	return (print->arg.len);
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
	return (printing(&print));
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
