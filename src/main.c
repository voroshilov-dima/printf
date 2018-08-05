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


int	ft_printf(const char *restrict format, ...)
{
	va_list args;
	va_start(args, format);
	int counter;
	counter = 0;
	while (*format != '\0')
	{
		if ('%' == *format)
		{
			format++;	
			if (*format == 'c')
			{
				char c = va_arg(args, int); // is't ok?
				counter += printf("%c", c);
			}
			else if (*format == 's')
			{
				char *s = va_arg(args, char *); // is't ok?
				counter += printf("%s", s);
			}
			else if (*format == 'd' || *format == 'i')
			{
				int i = va_arg(args, int);
				counter += printf("%d", i);
			}
			else if (*format == '%')
			{
				counter += 1;
				ft_putchar('%');
			}
			else
			{
				printf("Unknown modifier. List of supported modifiers: sSpdDioOuUxXcC\n");
				exit(1);
			}
		}
		else
		{
			counter += printf("%c", *format);
		}
		format++;
	}
	//printf("(%d)", counter);
	return (counter);
}
