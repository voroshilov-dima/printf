#include <stdio.h>

int	ft_printf(const char *restrict format, ...);

int main(void)
{
	printf("%%");
	printf("\n");
	ft_printf("%%");
	printf("\n");
}
