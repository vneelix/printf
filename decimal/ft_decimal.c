/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_decimal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneelix <vneelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 11:33:33 by vneelix           #+#    #+#             */
/*   Updated: 2019/11/09 15:29:57 by vneelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		get_data_signed(long long *num,
									t_obj *t, va_list *arg)
{
	if (t->len_m[0] == 'h' && t->len_m[1] == 'h')
		*num = (long long)((char)va_arg(*arg, int));
	else if (t->len_m[0] == 'h' && t->len_m[1] == '\0')
		*num = (long long)((short)va_arg(*arg, int));
	else if (t->len_m[0] == '\0' && t->len_m[1] == '\0')
		*num = (long long)va_arg(*arg, int);
	else if (t->len_m[0] == 'l' && t->len_m[1] == '\0')
		*num = (long long)va_arg(*arg, long);
	else
		*num = va_arg(*arg, long long);
}

static void		get_data_unsigned(unsigned long long *num,
									t_obj *t, va_list *arg)
{
	if (t->len_m[0] == 'h' && t->len_m[1] == 'h')
		*num = (unsigned long long)((unsigned char)va_arg(*arg, unsigned int));
	else if (t->len_m[0] == 'h' && t->len_m[1] == '\0')
		*num = (unsigned long long)((unsigned short)va_arg(*arg, unsigned int));
	else if (t->len_m[0] == '\0' && t->len_m[1] == '\0')
		*num = (unsigned long long)va_arg(*arg, unsigned int);
	else if (t->len_m[0] == 'l' && t->len_m[1] == '\0')
		*num = (unsigned long long)va_arg(*arg, unsigned long);
	else if (t->len_m[0] == 'z' && t->len_m[1] == '\0')
		*num = (unsigned long long)va_arg(*arg, size_t);
	else
		*num = va_arg(*arg, unsigned long long);
}

size_t			ft_print_decimal(char *str, t_obj *t, char ch, size_t size)
{
	size = ft_strlen(str);
	if (t->field > size)
	{
		t->field -= size + (ch != '\0' ? 1 : 0);
		if (t->flags[0] == '-' || t->flags[1] == '-' || t->flags[2] == '-')
		{
			ft_putstr(str, t->fd);
			while ((t->field--) > 0)
				size += write(t->fd, " ", 1);
			return (size);
		}
		if (ch != '\0')
			size += write(t->fd, &ch, 1);
		ch = ((t->flags[0] == '0' || t->flags[1] == '0'
			|| t->flags[2] == '0') ? '0' : ' ');
		while ((t->field--) > 0)
			size += write(t->fd, &ch, 1);
		ft_putstr(str, t->fd);
		return (size);
	}
	if (ch != '\0')
		size += write(t->fd, &ch, 1);
	ft_putstr(str, t->fd);
	return (size);
}

size_t			ft_decimal_unsigned(t_obj *t, va_list *arg)
{
	unsigned long long	num;
	char				*str;
	size_t				size;

	size = 0;
	get_data_unsigned(&num, t, arg);
	if ((str = ft_ultostr(num, t)) == NULL)
		return (0);
	size += ft_print_decimal(str, t, '\0', 0);
	free(str);
	return (size);
}

size_t			ft_decimal_signed(t_obj *t, va_list *arg)
{
	long long	num;
	char		*str;
	size_t		size;

	size = 0;
	get_data_signed(&num, t, arg);
	if ((str = ft_ltostr(num, t)) == NULL)
		return (0);
	if (num < 0 && (t->flags[0] == '0'
		|| t->flags[1] == '0' || t->flags[2] == '0'))
		size += ft_print_decimal(str, t, '-', 0);
	else if (num >= 0 && (t->flags[0] == '0'
		|| t->flags[1] == '0' || t->flags[2] == '0'))
	{
		if (t->flags[0] == ' ' || t->flags[1] == ' ' || t->flags[2] == ' ')
			size += ft_print_decimal(str, t, ' ', 0);
		else if (t->flags[0] == '+' || t->flags[1] == '+' || t->flags[2] == '+')
			size += ft_print_decimal(str, t, '+', 0);
		else
			size += ft_print_decimal(str, t, '\0', 0);
	}
	else
		size += ft_print_decimal(str, t, '\0', 0);
	free(str);
	return (size);
}
