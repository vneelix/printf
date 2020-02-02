/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vneelix <vneelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 12:53:34 by vneelix           #+#    #+#             */
/*   Updated: 2019/11/09 15:25:01 by vneelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

/*
** standart libary
*/
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

/*
** structs
*/
typedef struct
{
	char			flags[3];
	unsigned long	field;
	unsigned long	preci;
	char			preci_f;
	char			len_m[2];
	char			type;
	long			fd;
}					t_obj;

/*
** general		func
*/
int					ft_printf(const char *format, ...);

/*
** secondary	func
*/
int					ft_convertation(char ch, const char **format, va_list *arg);
void				ft_getflags(t_obj *t, const char **format);
unsigned long long	ft_strtoul(const char *str);
size_t				ft_print_decimal(char *str, t_obj *t, char ch, size_t size);

/*
** decimal
*/
size_t				ft_decimal_signed(t_obj *t, va_list *arg);
size_t				ft_decimal_unsigned(t_obj *t, va_list *arg);
char				*ft_ltostr(long long num, t_obj *t);
size_t				ft_numlen(unsigned long long num);
char				*ft_ultostr(unsigned long long num, t_obj *t);

/*
** not_decimal
*/
size_t				ft_not_decimal(t_obj *t, va_list *arg);
size_t				ft_pointer(t_obj *t, va_list *arg);
char				*ultoa_base(unsigned long long num, t_obj *t);
size_t				ft_string(t_obj *t, va_list *arg);
size_t				ft_char(t_obj *t, va_list *arg);

/*
** double
*/
size_t				ft_double(t_obj *t, va_list *arg);
unsigned short		*ft_intpart(void *num, int exp);
char				*ft_frac(long double *num, int *exp, t_obj *t);
char				*ft_number(unsigned short *intpart,
								char *frac, t_obj *t, int f);

/*
** add			func
*/
int					ft_isflag(char ch);
int					ft_isdigit(char ch);
size_t				ft_strlen(const char *s);
void				ft_bzero(void *s, size_t n);
void				ft_putstr(char const *s, long long fd);
char				*ft_strjoin(char *s1, char *s2);
#endif
