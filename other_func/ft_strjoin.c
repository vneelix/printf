#include "ft_printf.h"

char			*ft_strjoin(char *s1, char *s2)
{
	size_t		len;
	size_t		len2;
	char		*str;
	char		*s1_b;
	char		*s2_b;

	if ((s1 == NULL) || (s2 == NULL))
		return (NULL);
	s1_b = s1;
	s2_b = s2;
	len = ft_strlen(s1);
	len2 = ft_strlen(s2);
	str = (char*)malloc(len + len2 + 1);
	if (str == NULL)
		return (NULL);
	while (*s1 != '\0')
		*(str++) = *(s1++);
	while (*s2 != '\0')
		*(str++) = *(s2++);
	*str = '\0';
	str -= (len + len2);
	free(s1_b);
	free(s2_b);
	return (str);
}
