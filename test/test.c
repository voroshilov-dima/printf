#include <stdio.h>

int	ft_printf(const char *restrict format, ...);

int main(void)
{
	printf("%+05d", -42);
	printf("\n");
	ft_printf("%+05d", -42);
	printf("\n");
}
