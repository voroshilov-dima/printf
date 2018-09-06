#include "ft_printf.h"

void parse_signed_decimal(t_print *print, va_list args)
{	
	if (print->fmt.z == 1)
		print->arg.str = ft_itoa_base(va_arg(args, size_t), 10);
	else if (print->fmt.j == 1)
		print->arg.str = ft_itoa_base(va_arg(args, intmax_t), 10);
	else if (print->fmt.length == 0)
		print->arg.str = ft_itoa_base((int)va_arg(args, int), 10);
	else if (print->fmt.length == 1)
		print->arg.str = ft_itoa_base((long)va_arg(args, long int), 10);
	else if (print->fmt.length == 2)
		print->arg.str = ft_itoa_base(va_arg(args, long long int), 10);
	else if (print->fmt.length == -1)
		print->arg.str = ft_itoa_base((short)va_arg(args, int), 10);
	else if (print->fmt.length == -2)
		print->arg.str = ft_itoa_base((char)va_arg(args, int), 10);
	print->arg.len = ft_strlen(print->arg.str);
	// важно, будет ли минус в финальной строке,
	// а не изначальной, пример printf("%   hhd", 128);
	if (print->arg.str[0] == '-')
		print->arg.sign = -1;
}

void parse_unsigned_decimal(t_print *print, va_list args)
{	
	if (print->fmt.j == 1)
		print->arg.str = ft_utoa_base(va_arg(args, uintmax_t), 10);
	else if (print->fmt.length == 0)
		print->arg.str = ft_utoa_base(va_arg(args, unsigned int), 10);
	else if (print->fmt.length == 1)
		print->arg.str = ft_utoa_base(va_arg(args, long unsigned int), 10);
	else if (print->fmt.length == 2)
		print->arg.str = ft_utoa_base(va_arg(args, long long unsigned int), 10);
	print->arg.len = ft_strlen(print->arg.str);
}

void parse_unsigned_long(t_print *print, va_list args)
{	
	print->arg.str = ft_utoa_base(va_arg(args, unsigned long), 10);
	print->arg.len = ft_strlen(print->arg.str);
}

void parse_hex(t_print *print, va_list args)
{	
	if (print->fmt.j == 1)
		print->arg.str = ft_itoa_base(va_arg(args, intmax_t), 16);
	else if (print->fmt.length == 0)
		print->arg.str = ft_itoa_base(va_arg(args, unsigned int), 16);
	else if (print->fmt.length == 1)
		print->arg.str = ft_itoa_base(va_arg(args, long unsigned int), 16);
	else if (print->fmt.length == 2)
		print->arg.str = ft_itoa_base(va_arg(args, long long unsigned int), 16);
	else if (print->fmt.length == -1)
		print->arg.str = ft_itoa_base((short)va_arg(args, int), 16);
	else if (print->fmt.length == -2)
		print->arg.str = ft_itoa_base((char)va_arg(args, int), 16);
	print->arg.len = ft_strlen(print->arg.str);
}

void parse_octal(t_print *print, va_list args)
{
	if (print->fmt.j == 1)
		print->arg.str = ft_itoa_base(va_arg(args, uintmax_t), 8);
	else if (print->fmt.length == 0)
		print->arg.str = ft_itoa_base(va_arg(args, unsigned int), 8);
	else if (print->fmt.length == 1)
		print->arg.str = ft_itoa_base(va_arg(args, long unsigned int), 8);
	else if (print->fmt.length == 2)
		print->arg.str = ft_itoa_base(va_arg(args, long long unsigned int), 8);
	print->arg.len = ft_strlen(print->arg.str);
}