/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_u.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 21:29:30 by thverney          #+#    #+#             */
/*   Updated: 2019/11/22 20:47:19 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_handle_u_zero(t_flags f, char *str)
{
	char	*ret;
	char	*zero;

	zero = NULL;
	if (f.nb < f.arg_len && (f.nb * -1) < f.arg_len)
		return (sdupfr(str, 1));
	else if (f.nb < 0)
		zero = generator_str(f.nb * -1 - f.arg_len, ' ', 0);
	else
		zero = generator_str(f.nb - f.arg_len, '0', 0);
	ret = (f.nb > 0 ? ft_sjoin_free(zero, str, 2) :
	ft_sjoin_free(str, zero, 2));
	return (ret);
}

char	*ft_handle_u_dot(t_flags f, char *str)
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

char	*ft_handle_u_nb(t_flags f, char *str)
{
	char	*ret;
	char	*fill;
	int		abs;

	abs = (f.after_dot > f.arg_len ? f.after_dot : f.arg_len);
	if ((f.after_dot >= f.nb && f.after_dot >= f.nb * -1 && f.after_dot > 0)
	|| (f.arg_len >= f.nb && f.arg_len >= f.nb * -1) || (f.flags[0] == '0'
	&& f.pos_dot == NULL))
		return (sdupfr(str, 1));
	else if (((f.pos_dot != NULL && f.after_dot != 0
	&& f.after_dot <= f.arg_len) || (f.pos_dot != NULL && f.after_dot == 0)
	|| (f.arg_len > f.after_dot)) && f.nb > 0)
		fill = generator_str(f.nb - f.arg_len, ' ', 0);
	else if (f.arg_len <= f.after_dot && f.nb > 0)
		fill = generator_str(f.nb - f.after_dot, ' ', 0);
	else if (f.nb < 0 && ft_strchr(f.flags, '.') == NULL
	&& f.nb * -1 > f.arg_len)
		fill = generator_str((f.nb * -1) - f.arg_len, ' ', 0);
	else if (f.nb < 0 && f.after_dot >= 0 && (f.nb * -1) > f.after_dot)
		fill = generator_str((f.nb * -1) - abs, ' ', 0);
	else if (f.nb < 0 && f.after_dot < 0)
		fill = generator_str((f.nb * -1) - abs, ' ', 0);
	ret = (f.nb > 0 ? ft_sjoin_free(fill, str, 2) :
	ft_sjoin_free(str, fill, 2));
	return (ret);
}

char	*ft_handle_u_minus(t_flags f, char *str)
{
	char	*ret;
	char	*fill;
	int		isnbnega;

	isnbnega = (f.nb > 0 ? f.nb : f.nb * -1);
	if ((f.flags[0] == '-' && f.flags[1] == '.') || (f.flags[1] == '-'
	&& f.flags[2] == '.') || (f.flags[0] == '-' && f.flags[1] == '0'
	&& f.flags[2] == '.') || (f.flags[0] == '-' && (f.flags[1] == 'd'
	|| f.flags[1] == 'i')))
		return (sdupfr(str, 1));
	if (f.pos_dot != NULL && f.after_dot > f.arg_len && f.nb > 0)
		fill = generator_str(f.nb - f.after_dot, ' ', 0);
	else if (f.pos_dot != NULL && f.after_dot > f.arg_len && f.nb < 0)
		fill = generator_str(isnbnega - f.after_dot, ' ', 0);
	else if (f.nb > 0)
		fill = generator_str(f.nb - f.arg_len, ' ', 0);
	else if (f.nb < 0)
		fill = generator_str(isnbnega - f.arg_len, ' ', 0);
	ret = ft_sjoin_free(str, fill, 2);
	return (ret);
}

int		do_u(t_flags f, va_list ap)
{
	unsigned int	d;
	char			*str;

	f.nb = ft_find_nb(f, ap);
	f.after_dot = ft_find_precision(f, ap);
	d = (unsigned int)va_arg(ap, void *);
	str = ft_convert_u(d);
	str = ft_incase(d, f, str);
	f.arg_len = ft_strlen(str);
	f.pos_dot = ft_strchr(f.flags, '.');
	if (f.pos_dot != NULL && f.after_dot >= 0)
		str = ft_handle_u_dot(f, str);
	if ((f.nb != 0 && ft_strchr(f.flags, '-') == NULL && f.flags[0] != '0')
	|| (f.flags[0] == '0' && f.after_dot >= 0 && f.pos_dot != NULL))
		str = ft_handle_u_nb(f, str);
	if (f.flags[0] == '0' && (f.pos_dot == NULL || f.after_dot < 0))
		str = ft_handle_u_zero(f, str);
	if (ft_strchr(f.flags, '-') != NULL && f.nb != 0 && f.flags[1] != '.'
	&& (f.nb > f.arg_len || (f.nb * -1) > f.arg_len))
		str = ft_handle_u_minus(f, str);
	d = write(1, str, ft_strlen(str));
	(str ? free(str) : 0);
	return (d);
}
