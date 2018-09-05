#include <stdio.h>

int	ft_printf(const char *restrict format, ...);

int main(void)
{
	ft_printf("%#08x", 42);
	printf("\n");
	//printf("%d", ft_printf("%c", 0));
	//printf("\n");
}
