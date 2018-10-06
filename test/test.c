#include <locale.h>
#include <stdio.h>
#include <limits.h>

int	ft_printf(const char *restrict format, ...);

int main(void)
{
	setlocale(LC_ALL, "en_US.UTF-8");	
	ft_printf("{%05.%}", 0);
	printf("\n");
	printf("{%05.%}", 0);
	printf("\n");
	return (0);
}
