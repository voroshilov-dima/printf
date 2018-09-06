/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/04 18:48:15 by dvoroshy          #+#    #+#             */
/*   Updated: 2018/08/04 18:48:17 by dvoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include "libft.h"

typedef struct	s_fmt {
	char	*str;
	char	type;
	int		space;
	int		minus;
	int		plus;
	int		hash;
	char	filler;
	int		width;
	int		length;
	int		precision;
	int		z;
	int		j;
}				t_fmt;

void	get_type(int *i, const char *restrict format, t_fmt *fmt);
void	parse_format(t_fmt *fmt);
// void	parse_signed_decimal(t_fmt *fmt, va_list args);
// void	parse_unsigned_decimal(t_fmt *fmt, va_list args);
// void	parse_unsigned_long(t_fmt *fmt, va_list args);
// void	parse_hex(t_fmt *fmt, va_list args);
// void	parse_octal(t_fmt *fmt, va_list args);
int		print_percent(t_fmt *fmt);
int		print_char(t_fmt *fmt, int c);
int		print_string(t_fmt *fmt, char *str);

char	*ft_itoa_base(long long int n, int base);
char	*ft_utoa_base(long long unsigned int n, int base);
int		ft_length(long long int n, int base);
int		ft_ulength(unsigned long long int n, int base);
int		ft_abs(long long int n);

#endif
