#include <stdio.h>

int	ft_printf(const char *restrict format, ...);

int main(void)
{
	printf("%s is a string", "this");
	printf("\n");
	ft_printf("%s is a string", "this");
	printf("\n");
}
