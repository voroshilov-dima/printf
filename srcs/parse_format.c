/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_format.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 09:11:00 by dvoroshy          #+#    #+#             */
/*   Updated: 2018/09/15 09:11:06 by dvoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		is_specifier(char c, t_fmt *fmt)
{
	if (c == 's' || c == 'S' || c == 'p' || c == 'd' ||
		c == 'D' || c == 'i' || c == 'o' || c == 'O' ||
		c == 'u' || c == 'U' || c == 'x' || c == 'X' ||
		c == 'c' || c == 'C' || c == '%')
	{
		fmt->type = c;
		return (1);
	}
	return (0);
}

int		is_flag(const char *restrict f, t_fmt *fmt, va_list args)
{
	int	length;

	length = 1;
	if (f[fmt->pointer] == ' ')
		fmt->space += 1;
	else if (f[fmt->pointer] == '-')
		fmt->minus = 1;
	else if (f[fmt->pointer] == '+')
		fmt->plus = 1;
	else if (f[fmt->pointer] == '.')
		length = get_precision(f, fmt, args);
	else if ((f[fmt->pointer] >= 49 && f[fmt->pointer] <= 57) || f[fmt->pointer] == 42)
		length = get_width(f, fmt, args);
	else if (f[fmt->pointer] == '0')
		set_filler(fmt);
	else if (f[fmt->pointer] == 'l')
		fmt->length++;
	else if (f[fmt->pointer] == 'h')
		fmt->length--;
	else if (f[fmt->pointer] == '#')
		fmt->hash = 1;
	else if (f[fmt->pointer] == 'z')
		fmt->z = 1;
	else if (f[fmt->pointer] == 'j')
		fmt->j = 1;
	else
		length = 0;
	return (length);
}

void	print_unvalid(const char *restrict format, t_fmt *fmt)
{
	int	filler_length;

	filler_length = fmt->width - 1;
	if (filler_length && fmt->minus == 0)
		print_filler(fmt, filler_length);
	ft_write(format[fmt->pointer], fmt);
	if (filler_length && fmt->minus)
		apply_postfix(fmt);
}

void	parsing(const char *restrict format, t_fmt *fmt, va_list args)
{
	int	flag_length;
	clear_structure(fmt);
	while (format[fmt->pointer])
	{
		flag_length = is_flag(format, fmt, args);
		if (flag_length)
			fmt->pointer += flag_length;
		else if (is_specifier(format[fmt->pointer], fmt))
		{
			print_argument(fmt, args);
			fmt->pointer++;
			return ;
		}
		else
		{
			print_unvalid(format, fmt);
			fmt->pointer++;
			return ;
		}
	}
}
