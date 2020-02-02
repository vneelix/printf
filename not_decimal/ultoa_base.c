/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ultoa_base.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneelix <vneelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 14:04:06 by vneelix           #+#    #+#             */
/*   Updated: 2019/11/09 15:31:01 by vneelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t		lenght(unsigned long long num, int base, t_obj *t)
{
	size_t				size;
	unsigned long long	n;

	size = (num == 0 ? 1 : 0);
	n = num;
	while (n != 0)
	{
		size += 1;
		n /= base;
	}
	if (size < t->preci)
	{
		size = t->preci;
		if (t->type == 'o')
			return (size);
	}
	if ((num != 0) && (t->flags[0] == '#'
		|| t->flags[1] == '#' || t->flags[2] == '#')
			&& (t->flags[0] != '0') && (t->flags[1] != '0')
				&& (t->flags[2] != '0') && t->type != 'b' && t->type != 'q')
		size += (t->type == 'o' ? 1 : 2);
	else if ((num == 0) && (t->type == 'p'))
		size += 2;
	return (size);
}

static char			*str_create(size_t size, t_obj *t, int f)
{
	char *string;

	if ((string = (char*)malloc(size + 1)) == NULL)
		return (NULL);
	ft_bzero(string, size + 1);
	if (t->type == 'p' || (f != 1 && (t->flags[0] == '#' || t->flags[1] == '#'
		|| t->flags[2] == '#') && t->flags[0] != '0' && t->flags[1] != '0'
			&& t->flags[2] != '0' && t->type != 'b' && t->type != 'q'))
	{
		if (t->type == 'o')
			*string = '0';
		else
		{
			*string = '0';
			*(string + 1) = (t->type == 'p' ? 'x' : t->type);
		}
	}
	return (string);
}

static void			ft_preci(char *str, size_t preci)
{
	while (preci != 0)
	{
		*str = '0';
		str -= 1;
		preci -= 1;
	}
}

static char			*digit_system(unsigned long long num, int base, t_obj *t)
{
	size_t	size;
	char	symbol;
	char	*string;

	symbol = (t->type == 'X' ? 'A' : 'a');
	size = lenght(num, base, t);
	if ((string = str_create(size, t, ((num == 0)
		&& (t->type != 'p') ? 1 : 0))) == NULL)
		return (NULL);
	size--;
	if (num == 0)
		*(string + size) = 48;
	while (num != 0)
	{
		*(string + size) =
			num % base > 9 ? (symbol + (num % base) % 10) : (48 + num % base);
		num /= base;
		size -= (size != 0 ? 1 : 0);
		t->preci -= (t->preci != 0 ? 1 : 0);
	}
	if (t->preci != 0)
		ft_preci(string + size, t->preci);
	return (string);
}

char				*ultoa_base(unsigned long long num, t_obj *t)
{
	int base;

	base = 0;
	if (t->type == 'p')
	{
		while (t->flags[base] != '#' && t->flags[base] != '\0' && base < 3)
			base += 1;
		t->flags[base] = '#';
	}
	if (t->type == 'b')
		base = 2;
	else if (t->type == 'q')
		base = 4;
	else if (t->type == 'o')
		base = 8;
	else if (t->type == 'x' || t->type == 'X' || t->type == 'p')
		base = 16;
	if (base < 2 || base > 16)
		return (NULL);
	return (digit_system(num, base, t));
}
