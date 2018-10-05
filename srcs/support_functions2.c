/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support_functions2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 09:48:52 by dvoroshy          #+#    #+#             */
/*   Updated: 2018/09/15 09:48:53 by dvoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	set_filler(t_fmt *fmt)
{
	if (fmt->precision == -1)
		fmt->filler = '0';
}

void	print_filler(t_fmt *fmt, int filler_length)
{
	int	i;

	i = 0;
	while (i < filler_length)
	{
		ft_write(fmt->filler, fmt);
		i++;
	}
}

void	apply_hash(t_fmt *fmt)
{
	if (fmt->hash == 1)
	{
		if ((fmt->type == 'o' || fmt->type == 'O') && (fmt->null == 0 || fmt->precision == 0)) 
			ft_write('0', fmt);
		else if ((fmt->null != 1 && fmt->type == 'x') || fmt->type == 'p')
		{
			ft_write('0', fmt);
			ft_write('x', fmt);
		}
		else if (fmt->null != 1 && fmt->type == 'X')
		{
			ft_write('0', fmt);
			ft_write('X', fmt);
		}
	}
}

void	clear_structure(t_fmt *fmt)
{
	fmt->type = 0;
	fmt->space = 0;
	fmt->plus = 0;
	fmt->minus = 0;
	fmt->hash = 0;
	fmt->filler = ' ';
	fmt->width = 0;
	fmt->length = 0;
	fmt->precision = -1;
	fmt->z = 0;
	fmt->j = 0;
	fmt->null = 0;
	fmt->negative = 0;
	fmt->printed_current = 0;
}

int	get_width(const char *restrict f, t_fmt *fmt, va_list args)
{
	int	i;
	int wildcard;

	i = 0;
	wildcard = 0;
	while ((f[fmt->pointer + i] >= 48 && f[fmt->pointer + i] <= 57) || f[fmt->pointer + i] == 42)
	{
		if (f[fmt->pointer + i] == 42)
		{
			fmt->width = va_arg(args, int);
			if (fmt->width < 0)
			{
				fmt->minus = 1;
				fmt->width = -fmt->width;
			}
			wildcard = 1;
		}
		else if (wildcard)
		{
			fmt->width = f[fmt->pointer + i] - 48;
			wildcard = 0;
		}
		else
			fmt->width = fmt->width * 10 + f[fmt->pointer + i] - 48;
		i++;
	}
	return (i);	
}

int	get_precision(const char *restrict f, t_fmt *fmt, va_list args)
{
	int	i;
	int wildcard;

	i = 1;
	wildcard = 0;
	fmt->precision = 0;
	while ((f[fmt->pointer + i] >= 48 && f[fmt->pointer + i] <= 57) || f[fmt->pointer + i] == 42)
	{
		if (f[fmt->pointer + i] == 42)
		{
			fmt->precision = va_arg(args, int);
			if (fmt->precision < 0)
				fmt->precision = -1;
			wildcard = 1;
		}
		else if (fmt->precision == -1 || wildcard)
		{
			fmt->precision = f[fmt->pointer + i] - 48;
			wildcard = 0;
		}
		else
			fmt->precision = fmt->precision * 10 + f[fmt->pointer + i] - 48;
		i++;
	}
	if (fmt->precision != -1)
		fmt->filler = ' ';
	return (i);
}
