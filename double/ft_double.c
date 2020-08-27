#include "ft_printf.h"

static void		get_data(void *num, int *exp, t_obj *t, va_list *arg)
{
	if (t->preci_f == 0)
		t->preci = 6;
	if ((t->len_m[0] == '\0' && t->len_m[1] == '\0')
		|| (t->len_m[0] == 'l' && t->len_m[1] == '\0'))
		*((long double*)num) = va_arg(*arg, double);
	else if (t->len_m[0] == 'L' && t->len_m[1] == '\0')
		*((long double*)num) = va_arg(*arg, long double);
	*exp = (unsigned short)(*((unsigned short*)num + 4) << 1);
	*exp >>= 1;
	*exp -= 16383;
}

static size_t	ft_print(long double num,
							t_obj *t, unsigned short *intpart, char *frac)
{
	char	*str;
	size_t	size;

	size = 0;
	if ((str = ft_number(intpart, frac, t, (num < 0 ? 1 : 0))) == NULL)
		return (0);
	if (num < 0 && (t->flags[0] == '0'
		|| t->flags[1] == '0' || t->flags[2] == '0'))
		size = ft_print_decimal(str, t, '-', 0);
	else if (num >= 0 && (t->flags[0] == '0'
		|| t->flags[1] == '0' || t->flags[2] == '0'))
	{
		if (t->flags[0] == ' ' || t->flags[1] == ' ' || t->flags[2] == ' ')
			size = ft_print_decimal(str, t, ' ', 0);
		else if (t->flags[0] == '+' || t->flags[1] == '+' || t->flags[2] == '+')
			size = ft_print_decimal(str, t, '+', 0);
		else
			size = ft_print_decimal(str, t, '\0', 0);
	}
	else
		size = ft_print_decimal(str, t, '\0', 0);
	free(str);
	free(intpart);
	return (size);
}

size_t			ft_double(t_obj *t, va_list *arg)
{
	int				exp;
	long double		num;
	char			*frac;
	unsigned short	*intpart;

	get_data(&num, &exp, t, arg);
	if ((frac = ft_frac(&num, &exp, t)) == NULL)
		return (0);
	if ((intpart = ft_intpart(&num, exp)) == NULL)
	{
		free(frac);
		return (0);
	}
	return (ft_print(num, t, intpart, frac));
}
