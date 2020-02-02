/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneelix <vneelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 19:58:22 by vneelix           #+#    #+#             */
/*   Updated: 2019/11/04 12:26:43 by vneelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_spec(const char *format)
{
	if (*format == 'd' || *format == 'i'
		|| *format == 'o' || *format == 'u'
			|| *format == 'x' || *format == 'X'
				|| *format == 'f' || *format == 'c'
					|| *format == 's' || *format == 'p'
						|| *format == 'b' || *format == 'q')
		return ((int)*format);
	else if (*format == '%')
		return ((int)*format);
	return (0);
}

static int	ft_valid(const char *format)
{
	while (ft_isflag(*format))
		format += 1;
	while (ft_isdigit(*format))
		format += 1;
	format += *format == '*' ? 1 : 0;
	while (ft_isdigit(*format))
		format += 1;
	if (*format == '.')
	{
		format += 1;
		while (ft_isdigit(*format))
			format += 1;
		format += *format == '*' ? 1 : 0;
	}
	if (*format == 'h' && *(format + 1) == 'h')
		format += 2;
	else if (*format == 'l' && *(format + 1) == 'l')
		format += 2;
	else if (*format == 'l' || *format == 'L'
		|| *format == 'h' || *format == 'z')
		format += 1;
	return (ft_spec(format));
}

static int	ft_print_format(const char *format, va_list *arg)
{
	char		ch;
	size_t		i;
	const char	*begin;

	i = 0;
	begin = format;
	while (*format != '\0')
	{
		if (*format == '%' && (ch = ft_valid(format + 1)))
		{
			i += write(1, begin, ((format++) - begin));
			i += ft_convertation(ch, &format, arg);
			begin = format;
		}
		else
		{
			format += 1;
			begin += (*begin == '%' ? 1 : 0);
			if (*format == '\0')
				i += write(1, begin, (format - begin));
		}
	}
	return (i);
}

int			ft_printf(const char *format, ...)
{
	int		i;
	va_list	arg;

	va_start(arg, format);
	i = ft_print_format(format, &arg);
	va_end(arg);
	return (i);
}
