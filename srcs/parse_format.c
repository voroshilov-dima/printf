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

int		is_flag(const char *restrict f, t_fmt *fmt)
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
		length = get_precision(f, fmt);
	else if (f[fmt->pointer] >= 49 && f[fmt->pointer] <= 57)
		length = get_width(f, fmt);
	else if (f[fmt->pointer] == '0')
		fmt->filler = '0';
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

void	parsing(const char *restrict format, t_fmt *fmt, va_list args)
{
	int	flag_length;
	clear_structure(fmt);
	while (format[fmt->pointer])
	{
		flag_length = is_flag(format, fmt);
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
			ft_write(format[fmt->pointer], fmt);
			fmt->pointer++;
			return ;
		}
	}
}
