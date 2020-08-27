#include "ft_printf.h"

static void					ft_pow(unsigned short **n, int power)
{
	int i;
	int j;

	i = 0;
	if ((*n = (unsigned short*)malloc(sizeof(unsigned short) * 5120)) == NULL)
		return ;
	ft_bzero(*n, 5120 * 2);
	**n = 1;
	while (i < power)
	{
		j = 0;
		while (j < 5120)
			(*n)[j++] *= 2;
		j = 0;
		while (j < 5119)
		{
			if ((*n)[j] > 9)
			{
				(*n)[j + 1] += ((*n)[j] / 10);
				(*n)[j] %= 10;
			}
			j += 1;
		}
		i += 1;
	}
}

static void					ft_sum(unsigned short *res, unsigned short *n)
{
	int i;

	i = 0;
	i = 0;
	while (i < 5120)
	{
		res[i] += n[i];
		i += 1;
	}
	i = 0;
	while (i < 5119)
	{
		if (res[i] > 9)
		{
			res[i + 1] += (res[i] / 10);
			res[i] %= 10;
		}
		i += 1;
	}
}

unsigned short				*ft_intpart(void *num, int exp)
{
	int				i;
	unsigned short	*n;
	unsigned short	*res;

	i = 63;
	if ((res = (unsigned short*)malloc(sizeof(unsigned short) * 5120)) == NULL)
		return (NULL);
	ft_bzero(res, 5120 * 2);
	while (i >= 0 && exp >= 0)
	{
		if ((*(__uint128_t*)num & ((__uint128_t)1 << (i--))) != 0)
		{
			ft_pow(&n, exp);
			if (n == NULL)
			{
				free(res);
				return (NULL);
			}
			ft_sum(res, n);
			free(n);
		}
		exp -= 1;
	}
	return (res);
}
