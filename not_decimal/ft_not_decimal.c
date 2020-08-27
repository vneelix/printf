#include "ft_printf.h"

static void		get_data(unsigned long long *num,
								char **str, t_obj *t, va_list *arg)
{
	if (t->len_m[0] == 'h' && t->len_m[1] == 'h')
	{
		*num = (unsigned long long)((unsigned char)va_arg(*arg, unsigned int));
		*str = ultoa_base(*num, t);
	}
	else if (t->len_m[0] == 'h' && t->len_m[1] == '\0')
	{
		*num = (unsigned long long)((unsigned short)va_arg(*arg, unsigned int));
		*str = ultoa_base(*num, t);
	}
	else if (t->len_m[0] == '\0' && t->len_m[1] == '\0')
	{
		*num = (unsigned long long)va_arg(*arg, unsigned int);
		*str = ultoa_base(*num, t);
	}
	else if (t->len_m[0] == 'l' && t->len_m[1] == '\0')
	{
		*num = (unsigned long long)va_arg(*arg, unsigned long);
		*str = ultoa_base(*num, t);
	}
	else
	{
		*num = va_arg(*arg, unsigned long long);
		*str = ultoa_base(*num, t);
	}
}

static void		ft_spec(char *str, t_obj *t, size_t *size)
{
	if ((t->flags[0] == '0' || t->flags[1] == '0' || t->flags[2] == '0')
		&& (t->flags[0] == '#' || t->flags[1] == '#' || t->flags[2] == '#'))
	{
		if (t->type == 'o' || t->type == 'b')
		{
			if (*str != 0)
			{
				*size += write(t->fd, "0", 1);
				t->field -= 1;
			}
		}
		else
		{
			if (*str != '0')
			{
				*size += write(t->fd, "0", 1);
				t->type = (t->type == 'p' ? 'x' : t->type);
				*size += write(t->fd, &(t->type), 1);
				t->field -= 2;
			}
		}
	}
}

static size_t	ft_print(char *str, t_obj *t, char ch)
{
	size_t	size;

	size = ft_strlen(str);
	if (t->field > size)
	{
		t->field -= size;
		ft_spec(str, t, &size);
		if (t->flags[0] == '-' || t->flags[1] == '-' || t->flags[2] == '-')
		{
			ft_putstr(str, t->fd);
			while ((t->field--) > 0)
				size += write(t->fd, " ", 1);
			return (size);
		}
		while ((t->field--) > 0)
			size += write(t->fd, &ch, 1);
		ft_putstr(str, t->fd);
		return (size);
	}
	ft_spec(str, t, &size);
	ft_putstr(str, t->fd);
	return (size);
}

size_t			ft_pointer(t_obj *t, va_list *arg)
{
	size_t	size;
	void	*p;
	char	*str;

	p = va_arg(*arg, void*);
	if ((str = ultoa_base((unsigned long long)p, t)) == NULL)
		return (0);
	if (t->preci_f == '1' && t->preci == 0 && p == NULL)
		*(str + 2) = 0;
	if (t->flags[0] == '0' || t->flags[1] == '0' || t->flags[2] == '0')
		size = ft_print(str, t, '0');
	else
		size = ft_print(str, t, ' ');
	free(str);
	return (size);
}

size_t			ft_not_decimal(t_obj *t, va_list *arg)
{
	size_t						size;
	unsigned long long			num;
	char						*str;

	get_data(&num, &str, t, arg);
	if (str == NULL)
		return (0);
	if (t->preci_f == '1' && t->preci == 0 && num == 0)
	{
		if (t->flags[0] != '#' && t->flags[1] != '#'
			&& t->flags[2] != '#')
			*str = 0;
		else if (t->flags[0] == '#'
			|| t->flags[1] == '#' || t->flags[2] == '#')
			*(str + (t->type == 'o' ? 1 : 0)) = 0;
	}
	if (t->flags[0] == '0' || t->flags[1] == '0' || t->flags[2] == '0')
		size = ft_print(str, t, '0');
	else
		size = ft_print(str, t, ' ');
	free(str);
	return (size);
}
