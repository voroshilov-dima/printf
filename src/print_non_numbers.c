#include "ft_printf.h"

static int ft_printfiller(t_fmt *fmt, int filler_length)
{
	int	i;

	i = 0;
	while (i < filler_length)
	{
		ft_putchar(fmt->filler);
		i++;
	}
	return (i);
}

int print_percent(t_fmt *fmt)
{
	int i;

	i = 1;
	ft_putchar('%');
	fmt->type = 'p'; // remove
	return (i);
}

int print_char(t_fmt *fmt, int c)
{
	ft_putchar(c);
	fmt->type = 'p'; // remove
	return (1);
}

int print_string(t_fmt *fmt, char *str)
{
	int		counter;
	int		filler_length;

	counter = 0;
	if (str == NULL)
	{
		ft_putstr("(null)");
		return(6);
	}
	if (fmt->precision != -1)
		str = ft_strsub(str, 0, fmt->precision);
	filler_length = fmt->width - ft_strlen(str);
	if (filler_length && fmt->minus == 0)
		counter += ft_printfiller(fmt, filler_length);
	while (*str)
	{
		ft_putchar(*str);
		counter++;
		str++;
	}
	if (filler_length && fmt->minus)
		counter += ft_printfiller(fmt, filler_length);
	return (counter);
}