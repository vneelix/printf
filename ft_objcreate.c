#include "ft_printf.h"

static unsigned long long	ft_asterisk(t_obj *t, va_list *arg, char type)
{
	int			i;
	long long	num;

	num = va_arg(*arg, int);
	if (type == 'f')
	{
		if (num < 0)
		{
			i = 0;
			while (*(t->flags + i) != '-' && *(t->flags + i) != '\0')
				i += 1;
			*(t->flags + i) = '-';
		}
		return (num < 0 ? (unsigned long long)(num * (-1)) : num);
	}
	else
	{
		if (t->type == 'f')
			return (num < 0 ? 6 : num);
		if (num < 0)
			t->preci_f = 0;
	}
	return (num < 0 ? 0 : num);
}

static void					ft_object(t_obj *t, const char **ft)
{
	if (**ft == '\0')
		return ;
	if ((**ft == 'h' && *(*ft + 1) == 'h')
		|| (**ft == 'l' && *(*ft + 1) == 'l'))
	{
		t->len_m[0] = **ft;
		t->len_m[1] = *(*ft + 1);
		(*ft) += 2;
	}
	else if (**ft == 'l' || **ft == 'L'
		|| **ft == 'h' || **ft == 'z')
	{
		t->len_m[0] = **ft;
		(*ft) += 1;
	}
	(*ft) += 1;
}

static void					ft_iniz(t_obj *t, va_list *arg, const char **ft)
{
	ft_getflags(t, ft);
	if (ft_isdigit(**ft) || **ft == '*')
	{
		t->field = **ft == '*' ? ft_asterisk(t, arg, 'f') : 0;
		*ft += **ft == '*' ? 1 : 0;
		t->field = ft_isdigit(**ft) ? ft_strtoul(*ft) : t->field;
		while (ft_isdigit(**ft))
			*ft += 1;
	}
	if (**ft == '.')
	{
		t->preci_f = '1';
		(*ft) += 1;
		if (ft_isdigit(**ft) || **ft == '*')
		{
			t->preci = **ft == '*' ?
				ft_asterisk(t, arg, 'p') : ft_strtoul(*ft);
			while (ft_isdigit(**ft))
				(*ft) += 1;
			*ft += **ft == '*' ? 1 : 0;
		}
	}
	ft_object(t, ft);
}

static int					ft_printobj(t_obj *t, va_list *arg)
{
	long long fd;

	if (t->flags[0] == '~' || t->flags[1] == '~' || t->flags[2] == '~')
	{
		fd = va_arg(*arg, long long);
		t->fd = fd <= 0 ? 1 : fd;
	}
	if (t->type == 'd' || t->type == 'i')
		return (ft_decimal_signed(t, arg));
	else if (t->type == 'u')
		return (ft_decimal_unsigned(t, arg));
	else if (t->type == 'b' || t->type == 'q'
		|| t->type == 'o' || t->type == 'x' || t->type == 'X')
		return (ft_not_decimal(t, arg));
	else if (t->type == 'p')
		return (ft_pointer(t, arg));
	else if (t->type == 's')
		return (ft_string(t, arg));
	else if (t->type == 'c' || t->type == '%')
		return (ft_char(t, arg));
	else if (t->type == 'f')
		return (ft_double(t, arg));
	return (0);
}

int							ft_convertation(char ch,
											const char **ft, va_list *arg)
{
	int		i;
	t_obj	t;

	t.flags[0] = 0;
	t.flags[1] = 0;
	t.flags[2] = 0;
	t.field = 0;
	t.preci = 0;
	t.preci_f = '\0';
	t.len_m[0] = 0;
	t.len_m[1] = 0;
	t.type = ch;
	t.fd = 1;
	ft_iniz(&t, arg, ft);
	i = 0;
	while (i < 3 && t.preci_f == '1' && t.type != 'f'
		&& t.type != 's' && t.type != 'c' && t.type != 'p')
	{
		t.flags[i] = t.flags[i] == 48 ? 0 : t.flags[i];
		i += 1;
	}
	return (ft_printobj(&t, arg));
}
