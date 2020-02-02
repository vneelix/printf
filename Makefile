# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vneelix <vneelix@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/20 19:48:16 by vneelix           #+#    #+#              #
#    Updated: 2019/11/11 14:53:08 by vneelix          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

VPATH = ./decimal ./not_decimal ./double ./other_func

OBJS = ft_decimal.o ft_ltostr.o ft_numlen.o ft_ultostr.o ft_not_decimal.o ft_string.o\
ultoa_base.o ft_double.o ft_intpart.o ft_fracpart.o ft_number.o add_func.o ft_strjoin.o ft_strtoul.o ft_getflags.o ft_objcreate.o ft_printf.o

INCL = ft_printf.h

INCL_PATH = ./

CFLAGS = -Wall -Wextra -Werror -I$(INCL_PATH) -c

NAME = libftprintf.a

%.o: %.c $(INCL)
	gcc $(CFLAGS) $<

$(NAME): $(OBJS)
	ar rc $(NAME) $^
	ranlib $(NAME)

all: $(NAME)
	
clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all