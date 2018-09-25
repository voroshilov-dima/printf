/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_non_numbers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 09:11:13 by dvoroshy          #+#    #+#             */
/*   Updated: 2018/09/15 09:11:15 by dvoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		print_percent(t_fmt *fmt)
{
	int		filler_length;

	filler_length = fmt->width - 1;
	if (filler_length && fmt->minus == 0)
		print_filler(fmt, filler_length);
	ft_write('%', fmt);
	if (filler_length && fmt->minus)
		apply_postfix(fmt);
}

void		print_char(t_fmt *fmt, int c)
{
	int		filler_length;

	filler_length = fmt->width - 1;
	if (filler_length && fmt->minus == 0)
		print_filler(fmt, filler_length);
	ft_write(c, fmt);
	if (filler_length && fmt->minus)
		apply_postfix(fmt);
}

void		print_string(t_fmt *fmt, char *str)
{
	int		filler_length;

	if (str == NULL)
	{
		ft_putstr("(null)");
		fmt->printed += 6;
		return ;
	}
	if (fmt->precision != -1)
		str = ft_strsub(str, 0, fmt->precision);
	filler_length = fmt->width - ft_strlen(str);
	if (filler_length && fmt->minus == 0)
		print_filler(fmt, filler_length);
	while (*str)
	{
		ft_write(*str, fmt);
		str++;
	}
	if (filler_length && fmt->minus)
		apply_postfix(fmt);
}
