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

typedef struct	s_format {
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
}				t_format;

typedef struct	s_argument {
	char	*str;
	int		sign;
	int 	len;
}				t_argument;

typedef struct	s_print {
	t_format	fmt;
	t_argument	arg;
}				t_print;

void	get_type(int *i, const char *restrict format, t_print *print);
void	parse_format(t_format *fmt);
void	parse_signed_decimal(t_print *print, va_list args);
void	parse_unsigned_decimal(t_print *print, va_list args);
void	parse_unsigned_long(t_print *print, va_list args);
void	parse_hex(t_print *print, va_list args);
void	parse_octal(t_print *print, va_list args);
char	*ft_itoa_base(long long int n, int base);
char	*ft_utoa_base(long long unsigned int n, int base);
int		ft_length(long long int n, int base);
int		ft_ulength(unsigned long long int n, int base);
int		ft_abs(long long int n);

#endif
