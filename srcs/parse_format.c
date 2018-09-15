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

int		is_flag(const char *restrict f, int i, t_fmt *fmt)
{
	int	result;

	result = 1;
	if (f[i] == ' ')
		fmt->space += 1;
	else if (f[i] == '-')
		fmt->minus = 1;
	else if (f[i] == '+')
		fmt->plus = 1;
	else if (f[i] >= 49 && f[i] <= 57 && fmt->width == 0 && fmt->precision == -1)
		fmt->width = ft_atoi(f + i);
	else if (f[i] == '0' && fmt->width == 0 && fmt->minus != 1 && fmt->type != 's')
		fmt->filler = '0';
	else if (f[i] == '.')
	{
		fmt->precision = ft_atoi(f + i + 1);
		fmt->filler = ' ';
	}
	else if (f[i] == 'l')
		fmt->length++;
	else if (f[i] == 'h')
		fmt->length--;
	else if (f[i] == '#')
		fmt->hash = 1;
	else if (f[i] == 'z')
		fmt->z = 1;
	else if (f[i] == 'j')
		fmt->j = 1;
	else
		i = 0;
	return (result);
}

int		parsing(int *i, const char *restrict format, t_fmt *fmt, va_list args)
{
	int		j;
	char	c;

	j = 1;
	while (format[*i + j])
	{
		c = format[*i + j];
		if (is_specifier(c, fmt))
		{
			*i += j;
			return (print_argument(fmt, args));
		}
		else if (is_flag(format, *i + j, fmt))
			j++;
		else
		{
			print_char(fmt, c);
			return (0);
		}
	}
	return (0);
}
