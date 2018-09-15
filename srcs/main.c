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

int		print_argument(t_fmt *fmt, va_list args)
{
	if (fmt->type == '%')
		return (print_percent(fmt));
	else if (fmt->type == 'c')
		return (print_char(fmt, va_arg(args, int)));
	else if (fmt->type == 's')
		return (print_string(fmt, va_arg(args, char *)));
	else if (fmt->type == 'o')
		return (print_unsigned(fmt, args, 8));
	else if (fmt->type == 'd')
		return (print_signed(fmt, args, 10));
	else if (fmt->type == 'u' || fmt->type == 'U')
		return (print_unsigned(fmt, args, 10));
	else if (fmt->type == 'x' || fmt->type == 'X' || fmt->type == 'p')
		return (print_unsigned(fmt, args, 16));
	return (0);
}

int		process_input(int *i, const char *restrict format, va_list args)
{
	int		counter;
	t_fmt	fmt;

	counter = 0;
	init_structure(&fmt);
	return (parsing(i, format, &fmt, args));
}

int		ft_printf(const char *restrict format, ...)
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
			counter += process_input(&i, format, args);
		else
		{
			ft_putchar(format[i]);
			counter++;
		}
		i++;
	}
	
	return (counter);
}
