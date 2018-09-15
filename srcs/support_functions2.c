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

void	apply_hash(t_fmt *fmt)
{
	if (fmt->hash == 1)
	{
		if (fmt->type == 'o')
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

void	init_structure(t_fmt *fmt)
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
	fmt->null = 0;
	fmt->negative = 0;
	fmt->printed = 0;
}


int		get_width(const char *restrict f, int i, t_fmt *fmt)
{
	int	j;

	j = 0;
	while (f[i + j] >= 48 && f[i + j] <= 57)
	{
		fmt->width = fmt->width * 10 + f[i + j] - 48;
		j++;
	}
	return (j);
}

int		get_precision(const char *restrict f, int i, t_fmt *fmt)
{
	int	j;

	j = 1;
	fmt->precision = 0;
	while (f[i + j] >= 48 && f[i + j] <= 57)
	{
		fmt->precision = fmt->precision * 10 + f[i + j] - 48;
		j++;
	}
	fmt->filler = ' ';
	return (j);
}
