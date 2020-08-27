#include "ft_printf.h"

size_t	ft_numlen(unsigned long long num)
{
	size_t			len;

	len = 0;
	while ((num /= 10) != 0)
		len += 1;
	return (len + 1);
}
