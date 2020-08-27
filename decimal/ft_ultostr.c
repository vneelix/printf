#include "ft_printf.h"

static char		*str_create(size_t size)
{
	char *str;

	if ((str = (char*)malloc(size + 1)) == NULL)
		return (NULL);
	ft_bzero(str, size + 1);
	return (str);
}

char			*ft_ultostr(unsigned long long num, t_obj *t)
{
	size_t			size;
	char			*str;

	size = ft_numlen(num);
	size = size < t->preci ? t->preci : size;
	if ((str = str_create(size)) == NULL)
		return (NULL);
	str += (size - 1);
	if (num == 0)
	{
		*str = (t->preci_f == '1' && t->preci == 0) ? 0 : 48;
		t->preci -= t->preci > 0 ? 1 : 0;
	}
	while (num != 0)
	{
		*str = 48 + (num % 10);
		num /= 10;
		num != 0 ? str-- : str;
		t->preci -= t->preci > 0 ? 1 : 0;
	}
	while ((t->preci--) > 0)
		*(str -= 1) = '0';
	return (str);
}
