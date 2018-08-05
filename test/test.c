#include <stdio.h>

int	ft_printf(const char *restrict format, ...);

int main(void)
{
	printf("%  +d", 42);
	printf("\n");
	ft_printf("%  +d", 42);
	printf("\n");
}
