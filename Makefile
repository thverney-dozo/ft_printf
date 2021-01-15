# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thverney <thverney@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/14 03:05:05 by thverney          #+#    #+#              #
#    Updated: 2019/11/21 13:21:13 by thverney         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

INCLUDE = ft_printf.h

FILES = 		ft_printf.c \
				do_c.c \
				do_x.c \
				do_s.c \
				do_d_i.c \
				do_p.c \
				do_mod.c \
				do_u.c \
				utils.c \
				utils_2.c \
				libft/ft_atoi.c \
                libft/ft_bzero.c \
                libft/ft_isalnum.c \
                libft/ft_isalpha.c \
                libft/ft_isascii.c \
                libft/ft_isdigit.c \
                libft/ft_isprint.c \
                libft/ft_memccpy.c \
                libft/ft_memcpy.c \
                libft/ft_memset.c \
                libft/ft_strdup.c \
                libft/ft_strlen.c \
                libft/ft_strncmp.c \
                libft/ft_tolower.c \
                libft/ft_toupper.c \
                libft/ft_memmove.c \
        		libft/ft_strnstr.c \
                libft/ft_calloc.c \
            	libft/ft_memchr.c \
                libft/ft_memcmp.c \
                libft/ft_strchr.c \
                libft/ft_strrchr.c \
                libft/ft_strdup.c \
                libft/ft_strjoin.c \
                libft/ft_substr.c \
                libft/ft_putchar_fd.c \
				libft/ft_putstr_fd.c \
				libft/ft_putendl_fd.c \
                libft/ft_putnbr_fd.c \
                libft/ft_split.c \
                libft/ft_strtrim.c \
            	libft/ft_strlcat.c \
                libft/ft_strlcpy.c \
                libft/ft_strmapi.c \
				libft/ft_itoa.c \
				libft/ft_putnbr.c \
				libft/ft_putstr.c \
				libft/ft_putchar.c \
				libft/ft_itoa_base.c \

OBJECTS = $(FILES:.c=.o)

CC= gcc -Wall -Wextra -Werror

all : $(NAME)

$(NAME) : $(OBJECTS)
						ar rc $(NAME) $(OBJECTS)

clean : 
			/bin/rm -f *.o */*.o

fclean : clean
			/bin/rm -f $(NAME)

re : fclean all

.PHONY: clean fclean all re
