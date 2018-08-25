#include <stdio.h>

int	ft_printf(const char *restrict format, ...);

int main(void)
{
	ft_printf("%10.5d", 4242);
	printf("\n");
	//ft_printf("%lld", -9223372036854775808);
	//printf("\n");
}
