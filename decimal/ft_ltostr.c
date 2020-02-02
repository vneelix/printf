/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltostr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneelix <vneelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 18:27:10 by vneelix           #+#    #+#             */
/*   Updated: 2019/11/10 12:47:01 by vneelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	ft_size(long long num, t_obj *t)
{
	unsigned long long	n;
	size_t				nlen;

	n = num < 0 ? num * (-1) : num;
	nlen = ft_numlen(n);
	nlen = nlen < t->preci ? t->preci : nlen;
	if ((num < 0) && (t->flags[0] != '0')
		&& (t->flags[1] != '0') && (t->flags[2] != '0'))
		nlen += 1;
	if ((num >= 0) && (t->flags[0] == ' ' ||
		t->flags[1] == ' ' || t->flags[2] == ' '
		|| t->flags[0] == '+' || t->flags[1] == '+' || t->flags[2] == '+')
			&& t->flags[0] != '0' && t->flags[1] != '0' && t->flags[2] != '0')
		nlen += 1;
	nlen = nlen < t->preci ? t->preci : nlen;
	return (nlen);
}

static char		*str_create(size_t size)
{
	char *str;

	if ((str = (char*)malloc(size + 1)) == NULL)
		return (NULL);
	ft_bzero(str, size + 1);
	return (str);
}

static void		ft_preci(long long *num, char **str, t_obj *t)
{
	while ((t->preci--) > 0)
		*(*str -= 1) = '0';
	if (*num < 0 && t->flags[0] != '0'
		&& t->flags[1] != '0' && t->flags[2] != '0')
		*(*str -= 1) = '-';
	else if ((*num >= 0) && (t->flags[0] == '+' || t->flags[1] == '+'
		|| t->flags[2] == '+' || t->flags[0] == ' ' || t->flags[1] == ' '
			|| t->flags[2] == ' ') && t->flags[0] != '0' && t->flags[1] != '0'
				&& t->flags[2] != '0')
	{
		*str -= 1;
		if (t->flags[0] == '+' || t->flags[1] == '+' || t->flags[2] == '+')
			**str = '+';
		else
			**str = ' ';
	}
}

char			*ft_ltostr(long long num, t_obj *t)
{
	unsigned long long	n;
	size_t				size;
	char				*str;

	size = ft_size(num, t);
	if ((str = str_create(size)) == NULL)
		return (NULL);
	str += (size - 1);
	n = num < 0 ? num * (-1) : num;
	if (n == 0)
	{
		*str = (t->preci_f == '1' && t->preci == 0) ? 0 : 48;
		t->preci -= t->preci > 0 ? 1 : 0;
	}
	while (n != 0)
	{
		*str = 48 + (n % 10);
		n /= 10;
		n != 0 ? str-- : str;
		t->preci -= t->preci > 0 ? 1 : 0;
	}
	ft_preci(&num, &str, t);
	return (str);
}
