#include <stdio.h>

int	ft_printf(const char *restrict format, ...);

int main(void)
{
	ft_printf("@moulitest: %5.d %5.0d", 0, 0);
	return (0);
}
