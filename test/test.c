#include <stdio.h>

int	ft_printf(const char *restrict format, ...);

int main(void)
{
	//printf("%.0d", 1);
	//printf("\n");
	printf("%d", ft_printf("%c", 0));
	printf("\n");
}
