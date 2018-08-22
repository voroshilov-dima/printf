#include <stdio.h>

int	ft_printf(const char *restrict format, ...);

int main(void)
{
	printf("%x", -42);
	printf("\n");
	ft_printf("%x", -42);
	printf("\n");
}
