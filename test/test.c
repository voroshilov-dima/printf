#include <stdio.h>

int	ft_printf(const char *restrict format, ...);

int main(void)
{
	ft_printf("%.2s is a string", "this");
	printf("\n");
	//ft_printf("%lld", -9223372036854775808);
	//printf("\n");
}
