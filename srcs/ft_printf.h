/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 18:18:43 by thverney          #+#    #+#             */
/*   Updated: 2021/02/02 15:08:43 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>
# include "../libft/libft.h"

typedef struct		s_flags
{
	char	*type_data;
	char	*flag_data;
	char	*flags;
	char	*pos_dot;
	int		arg_len;
	int		nb;
	int		after_dot;
	char	type;
	int		count;
	int		i;
	int		dot;
}					t_flags;
int					ft_printf(const char *format, ...);
void				ft_splitf(t_flags *f, const char *s, va_list ap);
void				ft_type(char c, va_list ap, t_flags f);
int					ft_parse(t_flags f, va_list ap);
int					ft_find_nb(t_flags f, va_list ap);
int					ft_find_precision(t_flags f, va_list ap);
int					ft_find_precision_d(t_flags f, va_list ap);
char				*generator_str(int len, int c, int p);
char				*ft_incase(int d, t_flags f, char *str);
char				*ft_prefix(char *str);
char				*ft_convert_u(unsigned int d);
int					ft_backzero(t_flags f);
int					cestlebon(t_flags f, va_list ap, int i, int ret);
char				*sdupfr(char *s1, size_t n);
char				*ft_sjoin_free(char const *dst, char const *src, size_t n);
int					do_d_i(t_flags f, va_list ap);
int					do_c(t_flags f, va_list ap);
int					do_p(t_flags f, va_list ap);
int					do_u(t_flags f, va_list ap);
int					do_x(t_flags f, va_list ap);
int					do_s(t_flags f, va_list ap);
int					do_mod(t_flags f, va_list ap);
char				*ft_handle_d_minus(t_flags f, char *str, int d);
char				*ft_handle_c_minus(t_flags f, char *str);
char				*ft_handle_s_minus(t_flags f, char *str);
char				*ft_handle_p_minus(t_flags f, char *str);
char				*ft_handle_u_minus(t_flags f, char *str);
char				*ft_handle_x_minus(t_flags f, char *str);
char				*ft_handle_mod_minus(t_flags f, char *str);
char				*ft_handle_u_dot(t_flags f, char *str);
char				*ft_handle_s_dot(t_flags f, char *str);
char				*ft_handle_p_dot(t_flags f, char *str);
char				*ft_handle_d_dot(t_flags f, char *str, int d);
char				*ft_handle_x_dot(t_flags f, char *str);
char				*ft_handle_u_zero(t_flags f, char *str);
char				*ft_handle_d_zero(t_flags f, char *str, int d);
char				*ft_handle_x_zero(t_flags f, char *str);
char				*ft_handle_mod_zero(t_flags f, char *str);
char				*ft_handle_d_nb(t_flags f, char *str, int d);
char				*ft_handle_c_nb(t_flags f, char *str);
char				*ft_handle_s_nb(t_flags f, char *str);
char				*ft_handle_p_nb(t_flags f, char *str);
char				*ft_handle_u_nb(t_flags f, char *str);
char				*ft_handle_x_nb(t_flags f, char *str);
char				*ft_handle_mod_nb(t_flags f, char *str);

#endif
