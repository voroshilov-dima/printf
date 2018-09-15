#include <stdio.h>

int	ft_printf(const char *restrict format, ...);

int main(void)
{
	//printf("% Zoooo\n");
	ft_printf("%+u", 4294967295);
	//printf("%05Z");
	return (0);
}
