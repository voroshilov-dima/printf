#include "ft_printf.h"

void ft_write(char c, t_fmt *fmt)
{
	ft_putchar(c);
	fmt->printed++;
}

void print_buf(char buf[64], t_fmt *fmt, int len)
{
	int	i;
	int precision;

	if (fmt->null == 1 && fmt->precision == 0)
		return ;
	
	i = 0;
	precision = fmt->precision - len;
	while (i < precision)
	{
		ft_write('0', fmt);
		i++;
	}
	i = 0;
	while (i < len)
	{
		ft_write(buf[64 - len + i], fmt);
		i++;
	}
}

void apply_postfix(t_fmt *fmt)
{
	int i;
	int filler_length;

	i = 0;
	filler_length = fmt->width - fmt->printed;
	if (fmt->minus)
	{
		while (i < filler_length)
		{
			ft_write(fmt->filler, fmt);
			i++;
		}
	}
}

int	ft_utoa_base(uintmax_t n, int base, char buf[64])
{
	int		i;
	char	char_base[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

	i = 0;
	if (n == 0)
	{
		buf[64 - i - 1] = '0';
		return (1);
	}
	while (n)
	{
		buf[64 - i - 1] = char_base[n % base];
		n = n / base;
		i++;	
	}
	return (i);
}