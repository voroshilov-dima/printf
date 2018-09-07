#include "ft_printf.h"

int print_octal(t_fmt *fmt, long long unsigned int number)
{
	number--;
	fmt->type = 'c';
	return (1);
}