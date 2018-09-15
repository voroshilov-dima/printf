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

int		get_type(int *i, const char *restrict format, t_fmt *fmt)
{
	int		j;
	char	type;

	j = 1;
	type = 0;
	while (format[*i + j])
	{
		type = format[*i + j];
		if (type == 's' || type == 'S' || type == 'p' || type == 'd' ||
			type == 'D' || type == 'i' || type == 'o' || type == 'O' ||
			type == 'u' || type == 'U' || type == 'x' || type == 'X' ||
			type == 'c' || type == 'C' || type == '%')
		{
			fmt->str = ft_strsub(format, *i, j);
			fmt->type = type;
			*i += j;
			return (1);
		}
		j++;
	}

	return (0);
}

void	parsing_routine1(t_fmt *fmt, int i)
{
	if (fmt->str[i] == ' ')
		fmt->space += 1;
	else if (fmt->str[i] == '-')
		fmt->minus = 1;
	else if (fmt->str[i] == '+' && fmt->type == 'd')
		fmt->plus = 1;
	else if (fmt->width == 0 && fmt->precision == -1 && fmt->str[i] >= 49
		&& fmt->str[i] <= 57)
		fmt->width = ft_atoi(fmt->str + i);
	else if (fmt->str[i] == '0' && fmt->width == 0 && fmt->minus != 1
		&& fmt->type != 's')
		fmt->filler = '0';
}

void	parsing_routine2(t_fmt *fmt, int i)
{
	if (fmt->str[i] == '.')
	{
		fmt->precision = ft_atoi(fmt->str + i + 1);
		fmt->filler = ' ';
	}
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
}

void	parse_format(t_fmt *fmt)
{
	int	i;

	i = 0;
	while (fmt->str[i])
	{
		parsing_routine1(fmt, i);
		parsing_routine2(fmt, i);
		i++;
	}
}
