#include <locale.h>
#include <stdio.h>
#include <limits.h>

int	ft_printf(const char *restrict format, ...);

int main(void)
{
	setlocale(LC_ALL, "en_US.UTF-8");	
	ft_printf("%4.1S", L"Jambon");
	printf("\n");
	printf("%4.1S", L"Jambon");
	printf("\n");
	return (0);
}
