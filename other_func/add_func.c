#include "ft_printf.h"

int			ft_isflag(char ch)
{
	return ((ch == '-' || ch == '+'
		|| ch == ' ' || ch == '#' || ch == '0' || ch == '~') ? 1 : 0);
}

int			ft_isdigit(char ch)
{
	return (ch >= '0' && ch <= '9' ? 1 : 0);
}

size_t		ft_strlen(const char *s)
{
	size_t len;

	if (s == NULL)
		return (6);
	len = 0;
	while (s[len] != '\0')
		if ((len++) == SIZE_MAX)
			return (SIZE_MAX);
	return (len);
}

void		ft_bzero(void *mem, size_t n)
{
	while (n > 0)
		*((unsigned char*)mem + ((n--) - 1)) = 0;
}

void		ft_putstr(char const *s, long long fd)
{
	write(fd, s, ft_strlen(s));
}
