/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_p.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 20:26:03 by thverney          #+#    #+#             */
/*   Updated: 2019/11/22 20:45:54 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_handle_p_dot(t_flags f, char *str)
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

char	*ft_handle_p_nb(t_flags f, char *str)
{
	char	*ret;
	char	*fill;

	if ((f.after_dot >= f.nb && f.after_dot >= f.nb * -1) || (f.arg_len
	>= f.nb && f.arg_len >= f.nb * -1) || (f.flags[0] == '0'
	&& f.pos_dot == NULL))
		return (sdupfr(str, 1));
	else if ((f.pos_dot != NULL && f.after_dot != 0
	&& f.after_dot <= f.arg_len) || (f.pos_dot != NULL && f.after_dot == 0)
	|| (f.arg_len > f.after_dot))
	{
		fill = (f.nb > 0 ? generator_str(f.nb - f.arg_len, ' ', 0) :
		generator_str((f.nb * -1) - f.arg_len, ' ', 0));
	}
	else if (f.arg_len <= f.after_dot)
		fill = generator_str(f.nb - f.after_dot, ' ', 0);
	ret = (f.nb > 0 ? ft_sjoin_free(fill, str, 2) :
	ft_sjoin_free(str, fill, 2));
	return (ret);
}

char	*ft_handle_p_minus(t_flags f, char *str)
{
	char	*ret;
	char	*fill;

	if ((f.flags[0] == '-' && f.flags[1] == '.') || (f.flags[1] == '-'
	&& f.flags[2] == '.') || (f.flags[0] == '-' && f.flags[1] == '0'
	&& f.flags[2] == '.') || (f.flags[0] == '-' && (f.flags[1] == 'd'
	|| f.flags[1] == 'i')))
		return (sdupfr(str, 1));
	if (f.pos_dot != NULL && f.after_dot > f.arg_len)
		fill = generator_str(f.nb - f.after_dot, ' ', 0);
	else if (f.nb < 0)
		fill = generator_str((f.nb * -1) - f.arg_len, ' ', 0);
	else
		fill = generator_str(f.nb - f.arg_len, ' ', 0);
	ret = ft_sjoin_free(str, fill, 2);
	return (ret);
}

int		do_p(t_flags f, va_list ap)
{
	long long int	p;
	char			*str;

	f.nb = ft_find_nb(f, ap);
	f.after_dot = ft_find_precision(f, ap);
	p = va_arg(ap, long long int);
	str = ft_itoa_base(p, 0);
	f.arg_len = ft_strlen(str);
	f.pos_dot = ft_strchr(f.flags, '.');
	if (f.pos_dot != NULL && f.after_dot != 0)
		str = ft_handle_p_dot(f, str);
	f.arg_len = ft_strlen(str) + 2;
	str = ft_prefix(str);
	if (((f.flags[0] >= '1' && f.flags[0] <= '9')
	|| (f.nb != 0 && ft_strchr(f.flags, '-') == NULL)) && (f.nb > f.after_dot
	|| f.nb * -1 > f.after_dot))
		str = ft_handle_p_nb(f, str);
	if (ft_strchr(f.flags, '-') != NULL && f.nb != 0 && f.flags[1] != '.'
	&& (f.nb > f.arg_len || f.nb * -1 > f.arg_len))
		str = ft_handle_p_minus(f, str);
	ft_putstr(str);
	p = ft_strlen(str);
	(str ? free(str) : 0);
	return (p);
}
