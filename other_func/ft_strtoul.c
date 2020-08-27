#include "ft_printf.h"

static const char			*ft_strtol_check(const char *str)
{
	while (*str == '\t' || *str == '\v' || *str == '\f' ||
			*str == '\r' || *str == '\n' || *str == ' ')
		str++;
	if (ft_isdigit(*str) == 0)
		return (NULL);
	return (str);
}

unsigned long long			ft_strtoul(const char *str)
{
	unsigned long long	num;

	str = ft_strtol_check(str);
	if (str == NULL)
		return (0);
	num = 0;
	while (ft_isdigit(*str))
	{
		if (num >= 1000000000000000000ULL)
			return (0);
		num = num * 10 + ((unsigned long long)(*str) - 48);
		str++;
	}
	return (num);
}
