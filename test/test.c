#include <locale.h>
#include <stdio.h>
#include <limits.h>

int	ft_printf(const char *restrict format, ...);

int main(void)
{
	setlocale(LC_ALL, "en_US.UTF-8");	
	ft_printf("%#.3o", 1);
	printf("\n");
	printf("%#.3o", 1);
	printf("\n");
	return (0);
}
