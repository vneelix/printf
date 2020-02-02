/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fracpart.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneelix <vneelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 13:05:52 by vneelix           #+#    #+#             */
/*   Updated: 2019/11/10 19:52:52 by vneelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static long double	ft_cutfrac(void *p, int exp)
{
	int				i;
	long double		num;

	i = 63;
	num = (exp > 63) ? 0 : *((long double*)p);
	p = &num;
	if (exp >= 0 && exp < 64)
	{
		*((unsigned long*)p) <<= (exp + 1);
		exp -= (exp + 1);
		while ((*((unsigned long*)p) & (1UL << 63)) == 0)
		{
			i -= 1;
			exp -= 1;
			*((unsigned long*)p) <<= 1;
			if (i < 0)
				break ;
		}
		*((unsigned short*)p + 4) = exp + 16383;
	}
	return (num);
}

static int			ft_preci(char *str, t_obj *t)
{
	unsigned long i;

	i = t->preci == 0 ? 2 : t->preci - 1;
	if (str[i + 1] >= '5')
	{
		while (str[i] == '9')
		{
			str[i + 1] = '0';
			if (i == 0)
			{
				str[i] = '0';
				return (1);
			}
			i -= 1;
		}
		str[i] += 1;
	}
	str[i + 1] = '0';
	return (t->preci == 0 && *str >= '5' ? 1 : 0);
}

static	void		get_frac_exact(long double num, size_t len, char *frac)
{
	size_t		i;
	__uint128_t	m;

	i = 1;
	m = 10;
	while (i < len)
	{
		m *= 10;
		i += 1;
	}
	num *= m;
	m = (__uint128_t)num;
	while (len > 0)
	{
		*(frac + (len - 1)) = (m % 10) + 48;
		m /= 10;
		len -= 1;
	}
}

static void			get_frac_approxim(long double num, size_t len, char *frac)
{
	while (len > 0)
	{
		num *= 10;
		*frac = 48 + (long long)num;
		num -= (long long)num;
		frac += 1;
		len -= 1;
	}
}

char				*ft_frac(long double *num, int *exp, t_obj *t)
{
	size_t		len_f;
	char		*frac;
	long double	real;

	len_f = t->preci == 0 ? 2 : t->preci + 1;
	if ((frac = (char*)malloc(len_f + 1)) == NULL)
		return (NULL);
	ft_bzero(frac, len_f + 1);
	real = ft_cutfrac(num, *exp);
	real = real < 0 ? real * (-1) : real;
	if (len_f >= 19)
		get_frac_approxim(real, len_f, frac);
	else
		get_frac_exact(real, len_f, frac);
	if (ft_preci(frac, t) != 0)
	{
		(*num) += (*num) < 0 ? (-1) : 1;
		*exp = (unsigned short)(*((unsigned short*)num + 4) << 1);
		*exp >>= 1;
		*exp -= 16383;
	}
	*(frac + t->preci) = 0;
	return (frac);
}
