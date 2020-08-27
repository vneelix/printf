#include "ft_printf.h"

static int	ft_change(t_obj *t, const char ch)
{
	int i;

	i = 0;
	while (i < 3)
	{
		if ((t->flags[i] == '0') || (t->flags[i] == ' '))
		{
			if ((ch == '-') && (t->flags[i] == '0'))
			{
				t->flags[i] = '-';
				return (1);
			}
			else if ((ch == '+') && (t->flags[i] == ' '))
			{
				t->flags[i] = '+';
				return (1);
			}
		}
		i++;
	}
	return (0);
}

static int	ft_check(t_obj *t, const char ch)
{
	int i;

	if ((ch == '-') || (ch == '+'))
		if (ft_change(t, ch))
			return (0);
	i = 0;
	if ((ch == '0') || (ch == ' '))
		while (i < 3)
		{
			if (((ch == '0') && (t->flags[i] == '-'))
				|| ((ch == ' ') && (t->flags[i] == '+')))
				return (0);
			i++;
		}
	i = 0;
	while (i < 3)
		if (ch == t->flags[i++])
			return (0);
	return (1);
}

void		ft_getflags(t_obj *t, const char **format)
{
	int i;

	i = 0;
	while (**format != '\0' && ft_isflag(**format))
	{
		if (ft_check(t, **format) == 0)
		{
			(*format) += 1;
			continue ;
		}
		t->flags[i] = **format;
		(*format) += 1;
		i++;
	}
}
