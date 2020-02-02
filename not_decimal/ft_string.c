/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneelix <vneelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 17:44:05 by vneelix           #+#    #+#             */
/*   Updated: 2019/11/10 14:24:48 by vneelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	ft_printfield(t_obj *t, size_t size)
{
	char	ch;
	size_t	count;

	count = 0;
	ch = (t->flags[0] == '0'
		|| t->flags[1] == '0'
			|| t->flags[2] == '0') ? '0' : ' ';
	t->field -= size;
	while (t->field > 0)
	{
		write(t->fd, &ch, 1);
		count += 1;
		t->field -= 1;
	}
	return (count);
}

static void		ft_putstrzu(char *str, size_t size, long long fd)
{
	if (str == NULL)
		write(fd, "(null)", size);
	else
		write(fd, str, size);
}

size_t			ft_char(t_obj *t, va_list *arg)
{
	size_t			count;
	unsigned char	ch;

	count = 1;
	if (t->type == '%')
		ch = '%';
	else
		ch = (unsigned char)va_arg(*arg, unsigned int);
	if (t->field > 1)
	{
		if (t->flags[0] == '-' || t->flags[1] == '-' || t->flags[2] == '-')
		{
			write(1, &ch, 1);
			count += ft_printfield(t, 1);
		}
		else
		{
			count += ft_printfield(t, 1);
			write(1, &ch, 1);
		}
	}
	else
		write(1, &ch, 1);
	return (count);
}

size_t			ft_string(t_obj *t, va_list *arg)
{
	size_t			size;
	size_t			count;
	char			*string;

	string = va_arg(*arg, char*);
	size = ft_strlen(string);
	count = 0;
	size = (t->preci_f == '1' && t->preci < size) ? t->preci : size;
	if (t->field > size)
	{
		if (t->flags[0] == '-' || t->flags[1] == '-' || t->flags[2] == '-')
		{
			ft_putstrzu(string, size, t->fd);
			count = ft_printfield(t, size);
		}
		else
		{
			count = ft_printfield(t, size);
			ft_putstrzu(string, size, t->fd);
		}
	}
	else
		ft_putstrzu(string, size, t->fd);
	return (size + count);
}
