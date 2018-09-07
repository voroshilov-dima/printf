#include "ft_printf.h"

void get_type(int *i, const char *restrict format, t_fmt *fmt)
{
	int		j;
	char	type;

	j = 0;
	type = 0;
	while (format[*i + j])
	{
		type = format[*i + j];
		if (type == 's' ||
			type == 'S' ||
			type == 'p' ||
			type == 'd' ||
			type == 'D' ||
			type == 'i' ||
			type == 'o' ||
			type == 'O' ||
			type == 'u' ||
			type == 'U' ||
			type == 'x' ||
			type == 'X' ||
			type == 'c' ||
			type == 'C' ||
			type == '%')
		{
			fmt->str = ft_strsub(format, *i, j);
			fmt->type = type;
			*i += j;
			return ;
		}
		j++;
	}
	ft_putstr("Following flags are supported: sSpdDioOuUxXcC\n");
	exit(1);	
}

void parse_format(t_fmt *fmt)
{
	int	i;

	i = 0;
	while (fmt->str[i])
	{
		if (fmt->str[i] == ' ')
			fmt->space += 1;
		else if (fmt->str[i] == '-')
			fmt->minus = 1;
		else if (fmt->str[i] == '+' && fmt->type == 'd')
			fmt->plus = 1;
		else if (fmt->width == 0 && fmt->precision == -1 && fmt->str[i] >= 49 && fmt->str[i] <= 57)
			fmt->width = ft_atoi(fmt->str + i);
		else if (fmt->str[i] == '0' && fmt->width == 0 && fmt->minus != 1 && fmt->type != 's') // TO DO: rework
			fmt->filler = '0';
		else if (fmt->str[i] == '.')
		{
			fmt->precision = ft_atoi(fmt->str + i + 1);
			fmt->filler = ' ';
		}
		else if (fmt->str[i] == 'l')
			fmt->length++;
		else if (fmt->str[i] == 'h')
			fmt->length--;
		else if (fmt->str[i] == '#')
			fmt->hash = 1;
		else if (fmt->str[i] == 'z')
			fmt->z = 1;
		else if (fmt->str[i] == 'j')
			fmt->j = 1;
		i++;
	}
}