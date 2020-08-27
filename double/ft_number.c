#include "ft_printf.h"

static size_t	num_len(unsigned short *num, t_obj *t, int f)
{
	int		i;
	size_t	len;

	i = 5119;
	len = 1;
	if (t->flags[0] != '0' && t->flags[1] != '0' && t->flags[2] != '0')
		if ((f == 1) || (num >= 0 && (t->flags[0] == ' '
			|| t->flags[1] == ' ' || t->flags[2] == ' ' || t->flags[0] == '+'
				|| t->flags[1] == '+' || t->flags[2] == '+')))
			len += 1;
	while (num[i] == 0 && i > 0)
		i -= 1;
	len += 5120 - (5120 - i);
	return (len);
}

static void		ft_int(unsigned short *num, int f, char *intpart, t_obj *t)
{
	size_t len;

	len = num_len(num, t, f);
	if (t->preci_f == '1' && t->preci == 0
		&& t->flags[0] != '#' && t->flags[1] != '#' && t->flags[2] != '#')
		*(intpart + len) = 0;
	else
		*(intpart + len) = '.';
	if (t->flags[0] != '0' && t->flags[1] != '0' && t->flags[2] != '0')
	{
		if (f == 1)
			*(intpart++) = '-';
		else if (t->flags[0] == ' ' || t->flags[1] == ' ' || t->flags[2] == ' ')
			*(intpart++) = ' ';
		else if (t->flags[0] == '+' || t->flags[1] == '+' || t->flags[2] == '+')
			*(intpart++) = '+';
	}
	while (num[len] == 0 && len != 0)
		len -= 1;
	while (len > 0)
	{
		*intpart = num[len--] + 48;
		intpart += 1;
	}
	*intpart = *num + 48;
}

char			*ft_number(unsigned short *intpart, char *frac, t_obj *t, int f)
{
	size_t	len;
	char	*intstr;

	len = num_len(intpart, t, f);
	if ((intstr = (char*)malloc(len + 2)) == NULL)
	{
		free(frac);
		return (NULL);
	}
	ft_bzero(intstr, len + 2);
	ft_int(intpart, f, intstr, t);
	return (ft_strjoin(intstr, frac));
}
