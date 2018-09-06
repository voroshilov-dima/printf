#include <stdio.h>

int	ft_printf(const char *restrict format, ...);

int main(void)
{
	ft_printf("%5.2s is a string", "this");
	printf("\n");
	//printf("%d", ft_printf("%c", 0));
	//printf("\n");
}
