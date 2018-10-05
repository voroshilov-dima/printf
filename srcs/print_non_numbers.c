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
	if (fmt->length == 1)
		printf("here\n");
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

void		print_unicode_buf(t_fmt *fmt, char buf[4], int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		ft_write(buf[i], fmt);
		i++;
	}
}

// REWORK: use unicode_char_len
void		print_unicode_char(t_fmt *fmt, wchar_t c)
{
	char 	buf[4];
	int		len;

	if (c < 128)
	{
		len = 1;
		buf[0] = c;
	}
	else if (c < 2048)
	{
		len = 2;
		buf[1] = (c & 0b111111) | 0b10000000;
		c >>= 6;
		buf[0] = (c & 0b11111) | 0b11000000;
	}
	else if (c < 65536)
	{
		len = 3;
		buf[2] = (c & 0b111111) | 0b10000000;
		c >>= 6;
		buf[1] = (c & 0b111111) | 0b10000000;
		c >>= 6;
		buf[0] = (c & 0b11111) | 0b11100000;
	}
	else
	{
		len = 4;
		buf[3] = (c & 0b111111) | 0b10000000;
		c >>= 6;
		buf[2] = (c & 0b111111) | 0b10000000;
		c >>= 6;
		buf[1] = (c & 0b111111) | 0b10000000;
		c >>= 6;
		buf[0] = (c & 0b11111) | 0b11110000;
	}
	print_unicode_buf(fmt, buf, len);
}

int		unicode_char_len(wchar_t c)
{
	int	len;

	if (c < 128)
		len = 1;
	else if (c < 2048)
		len = 2;
	else if (c < 65536)
		len = 3;
	else
		len = 4;
	return (len);
}

int		ft_strlen_unicode(wchar_t *s)
{
	int	len;
	int i;

	len = 0;
	i = 0;
	while (s[i] != '\0')
	{
		len += unicode_char_len(s[i]);
		i++;
	}
	return (len);
}

void		print_unicode_string(t_fmt *fmt, wchar_t *str)
{
	int		filler_length;
	
	if (str == NULL)
	{
		ft_putstr("(null)");
		fmt->printed += 6;
		return ;
	}
	filler_length = fmt->width - ft_strlen_unicode(str);
	if (filler_length && fmt->minus == 0)
		print_filler(fmt, filler_length);
	while (*str)
	{
		print_unicode_char(fmt, *str);
		str++;
	}
	if (filler_length && fmt->minus)
		apply_postfix(fmt);
}
