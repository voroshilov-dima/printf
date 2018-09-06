#include "ft_printf.h"

char		*ft_itoa_base(long long int n, int base)
{
	int			i;
	int			len;
	char		*str;
	char		char_base[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

	i = 0;
	len = ft_length(n, base);
	str = 0;
	if (n <= 0)
		len++;
	if ((str = (char *)malloc(sizeof(char) * (len + 1))))
	{
		str[len] = 0;
		if (n == 0 && (str[0] = '0'))
			return (str);
		if (n < 0)
			str[0] = '-';
		while (n && i < len)
		{
			str[len - i - 1] = char_base[ft_abs(n % base)];
			n = n / base;
			i++;
		}
	}
	return (str);
}

char		*ft_utoa_base(long long unsigned int n, int base)
{
	int		i;
	int		len;
	char	*str;
	char	char_base[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

	i = 0;
	len = ft_ulength(n, base);
	str = 0;
	if ((str = (char *)malloc(sizeof(char) * (len + 1))))
	{
		str[len] = 0;
		if (n == 0 && (str[0] = '0'))
			return (str);
		while (n && i < len)
		{
			str[len - i - 1] = char_base[ft_abs(n % base)];
			n = n / 10;
			i++;
		}
	}
	return (str);
}

int	ft_length(long long int n, int base)
{
	int len;

	len = 0;
	while (n && ++len)
		n = n / base;
	return (len);
}

int	ft_ulength(unsigned long long int n, int base)
{
	int len;

	len = 0;
	while (n && ++len)
		n = n / base;
	return (len);
}

int	ft_abs(long long int n)
{
	if (n < 0)
		return (-n);
	return (n);
}