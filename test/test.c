#include <stdio.h>

int	ft_printf(const char *restrict format, ...);

int main(void)
{
	//printf("% c", 0);
	//printf("\n");
	ft_printf("% c", 42);
	printf("\n");
}
