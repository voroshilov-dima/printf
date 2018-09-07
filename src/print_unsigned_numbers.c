#include "ft_printf.h"

void apply_hash(t_fmt *fmt)
{
	if (fmt->hash == 1)
	{
		if (fmt->type == 'o')
			ft_write('0', fmt);
		else if (fmt->null != 1 && fmt->type == 'x')
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

static int	calculate_filler_length(t_fmt *fmt, int len)
{
	int i;

	i = fmt->width - len;
	if (fmt->null == 1 && fmt->precision == 0)
		i++;
	if (fmt->hash == 1)
	{
		if (fmt->type == 'o') 
			i -= 1;
		else if (fmt->type == 'x' || fmt->type == 'X')
			i -= 2;
		if (fmt->precision != -1)
			i -= (fmt->precision - len);
	}
	return (i);
}

static void	apply_prefix(t_fmt *fmt, int len)
{
	int		i;
	int		filler_length;
	
	i = 0;
	filler_length = calculate_filler_length(fmt, len);
	if (fmt->filler == '0')
	{
		apply_hash(fmt);
		if (fmt->negative == 0 && fmt->plus == 1)
			ft_write('+', fmt);
		if (fmt->negative == 1)
			ft_write('-', fmt);	
	}
	if (fmt->minus == 0)
		while (i < filler_length)
		{
			ft_write(fmt->filler, fmt);
			i++;
		}
	if (fmt->filler == ' ')
	{
		if (fmt->negative == 0 && fmt->plus == 1)
			ft_write('+', fmt);
		if (fmt->negative == 1)
			ft_write('-', fmt);
		apply_hash(fmt);
	}
}

void	apply_case(char buf[64], t_fmt *fmt, int len)
{
	int i;

	if (fmt->type == 'X')
	{
		i = 0;
		while (i < len)
		{
			buf[64 - len + i] = ft_toupper(buf[64 - len + i]);
			i++;
		}
	}
}

long long unsigned apply_unsigned_cast(t_fmt *fmt, va_list args)
{
	uintmax_t number;

	if (fmt->z)
		number = va_arg(args, size_t);
	else if (fmt->j)
		number = va_arg(args, uintmax_t);
	else if (fmt->length == -2)
		number = (unsigned char)va_arg(args, unsigned int);
	else if (fmt->length == -1)
		number = (unsigned short)va_arg(args, unsigned int);
	else if (fmt->length == 0)
		number = va_arg(args, unsigned int);
	else if (fmt->length == 1)
		number = va_arg(args, unsigned long);
	else
		number = va_arg(args, unsigned long long);
	return (number);
}

int print_unsigned(t_fmt *fmt, va_list args, int base)
{
	int					len;
	char				buf[64];
	long long unsigned	number;

	number = apply_unsigned_cast(fmt, args);
	fmt->null = (number ? 0 : 1);
	len = ft_utoa_base(number, base, buf);
	apply_prefix(fmt, len);
	apply_case(buf, fmt, len);
	print_buf(buf, fmt, len);
	apply_postfix(fmt);
	return (fmt->printed);
}