/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_x.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 23:04:30 by thverney          #+#    #+#             */
/*   Updated: 2019/11/22 20:38:56 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_handle_x_zero(t_flags f, char *str)
{
	char	*ret;
	char	*zero;

	zero = NULL;
	if (f.nb < f.arg_len && (f.nb * -1) < f.arg_len)
		return (sdupfr(str, 1));
	else if (f.after_dot <= 0 && f.nb < 0)
	{
		zero = generator_str((f.nb * -1) - f.arg_len, ' ', 0);
		ret = ft_sjoin_free(str, zero, 2);
	}
	else
	{
		zero = generator_str(f.nb - f.arg_len, '0', 0);
		ret = ft_sjoin_free(zero, str, 2);
	}
	return (ret);
}

char	*ft_handle_x_dot(t_flags f, char *str)
{
	char	*ret;
	char	*zero;

	zero = NULL;
	if (f.after_dot < f.arg_len)
		return (sdupfr(str, 1));
	else
	{
		zero = generator_str(f.after_dot - f.arg_len, '0', 0);
		ret = ft_sjoin_free(zero, str, 2);
	}
	return (ret);
}

char	*ft_handle_x_nb(t_flags f, char *str)
{
	char	*ret;
	char	*fill;

	if ((f.after_dot > f.nb && f.after_dot > f.nb * -1) || (f.arg_len >= f.nb
	&& f.arg_len >= f.nb * -1)
	|| (f.flags[0] == '0' && f.pos_dot == NULL))
		return (sdupfr(str, 1));
	else if (((f.pos_dot != NULL && f.after_dot != 0
	&& f.after_dot <= f.arg_len) || (f.pos_dot != NULL && f.after_dot == 0)
	|| (f.arg_len > f.after_dot)) && f.nb >= f.arg_len)
		fill = generator_str(f.nb - f.arg_len, ' ', 0);
	else if (f.arg_len <= f.after_dot && f.nb >= f.after_dot)
	{
		fill = generator_str(f.nb - f.after_dot, ' ', 0);
	}
	else if ((f.nb * -1) > f.after_dot && f.nb < 0)
	{
		fill = f.after_dot <= 0 ? generator_str((f.nb * -1) - f.arg_len
		, ' ', 0) : generator_str((f.nb * -1) - f.arg_len, ' ', 0);
		ret = ft_sjoin_free(str, fill, 2);
		return (ret);
	}
	ret = ft_sjoin_free(fill, str, 2);
	return (ret);
}

char	*ft_handle_x_minus(t_flags f, char *str)
{
	char	*ret;
	char	*fill;
	int		afd;

	afd = (f.after_dot > f.arg_len ? 1 : 0);
	if ((f.flags[0] == '-' && f.flags[1] == '.') || (f.flags[1] == '-'
	&& f.flags[2] == '.') || (f.flags[0] == '-' && f.flags[1] == '0'
	&& f.flags[2] == '.') || (f.flags[0] == '-' && (f.flags[1] == 'd'
	|| f.flags[1] == 'i')) || (f.nb < f.arg_len && f.nb * -1 < f.arg_len))
		return (sdupfr(str, 1));
	if (f.pos_dot != NULL && f.after_dot < f.nb && f.nb > 0)
		fill = (f.after_dot > 0 && afd == 1 ? generator_str(f.nb - f.after_dot
		, ' ', 0) : generator_str(f.nb - f.arg_len, ' ', 0));
	else if (f.pos_dot != NULL && (f.after_dot < f.nb * -1) && f.nb < 0
	&& (f.nb * -1) > f.arg_len)
		fill = (f.after_dot > 0 && afd == 1 ? generator_str((f.nb * -1) -
		f.after_dot, ' ', 0) : generator_str((f.nb * -1) - f.arg_len, ' ', 0));
	else if (f.nb > 0)
		fill = (f.after_dot > 0 && afd == 1 ? generator_str(f.nb - f.after_dot
		, ' ', 0) : generator_str(f.nb - f.arg_len, ' ', 0));
	else if (f.nb < 0)
		fill = (f.after_dot > 0 && afd == 1 ? generator_str(f.nb - f.after_dot
		, ' ', 0) : generator_str(f.nb * -1 - f.arg_len, ' ', 0));
	ret = ft_sjoin_free(str, fill, 2);
	return (ret);
}

int		do_x(t_flags f, va_list ap)
{
	unsigned int	x;
	char			*str;

	f.nb = ft_find_nb(f, ap);
	f.after_dot = ft_find_precision(f, ap);
	x = va_arg(ap, unsigned int);
	str = (f.type == 'x' ? ft_itoa_base(x, 0) : ft_itoa_base(x, 1));
	str = ft_incase(x, f, str);
	f.arg_len = ft_strlen(str);
	f.pos_dot = ft_strchr(f.flags, '.');
	str = (f.pos_dot != NULL ? ft_handle_x_dot(f, str) : str);
	f.arg_len = ft_strlen(str);
	if (((((f.flags[0] >= '1' && f.flags[0] <= '9') || f.flags[0] == '*')
	&& (ft_strchr(f.flags, '-') == NULL)) && (f.nb >= f.after_dot
	|| f.nb * -1 >= f.after_dot)) || (f.flags[0] == '0' && f.after_dot >= 0))
		str = ft_handle_x_nb(f, str);
	if (f.flags[0] == '0' && ft_strchr(f.flags, '-') == NULL
	&& ((f.pos_dot != NULL && f.after_dot < 0) || f.pos_dot == NULL))
		str = ft_handle_x_zero(f, str);
	if (ft_strchr(f.flags, '-') != NULL && f.nb != 0 && f.flags[1] != '.'
	&& (f.nb > f.after_dot || (f.nb * -1) > f.after_dot))
		str = ft_handle_x_minus(f, str);
	x = write(1, str, ft_strlen(str));
	(str ? free(str) : 0);
	return ((int)x);
}
