/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/04 11:54:13 by dvoroshy          #+#    #+#             */
/*   Updated: 2018/08/04 20:02:42 by dvoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include <stdarg.h>
#include <stdlib.h>

#define MINUS 0x00000001


int parse_int(const char *restrict s, int start, int end)
{
	int counter;

	counter = 0;
	while (start <= end)
	{
		ft_putchar(s[start++]);
		counter++;
	}
	return (counter);
}

int (*define_parse_function(char c))(const char *restrict s, int, int)
{
	if (c == 's' ||
		c == 'S' ||
		c == 'p' ||
		c == 'd' ||
		c == 'D' ||
		c == 'i' ||
		c == 'o' ||
		c == 'O' ||
		c == 'u' ||
		c == 'U' ||
		c == 'x' ||
		c == 'X' ||
		c == 'c' ||
		c == 'C')
		return (parse_int);
	return (0);
}


int	ft_printf(const char *restrict format, ...)
{
	va_list args;
	int counter;
	int start;
	int end;
	int (*parser)(const char *restrict, int, int);

	va_start(args, format);
	counter = 0;
	start = 0;
	end = 0;
	while (format[start] != '\0')
	{
		if (format[start] == '%')
		{
			start++;
			end++;
			while (!(parser = define_parse_function(format[end])))
				end++;
			parser(format, start, end);

			//	
			//	передавать-то нужно не флаг, а переменную ебана
			//

		}
		else
		{
			ft_putchar(format[start]);
			counter++;
		}
		start++;
	}
	//printf("(%d)", counter);
	return (counter);
}
