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
#include <stdarg.h>
#include <stdlib.h>

int	ft_printf(const char *restrict format, ...)
{
	va_list args;
	va_start(args, format);
	while (*format != '\0')
	{
		if ('%' == *format)
		{
			format++;	
			if (*format == 'c')
			{
				char c = va_arg(args, int); // is't ok?
				printf("%c\n", c);
			}
			else if (*format == 'd' || *format == 'i')
			{
				int i = va_arg(args, int);
				printf("%d\n", i);
			}
			else
			{
				printf("%c", *format);
				printf("Unknown modifier. List of supported modifiers: sSpdDioOuUxXcC\n");
				exit(1);
			}
		}
		printf("%c", *format);
		format++;
	}
	return (0);
}
