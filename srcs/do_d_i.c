/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_d_i.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 20:13:26 by thverney          #+#    #+#             */
/*   Updated: 2019/11/23 19:02:26 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_handle_d_zero(t_flags f, char *str, int d)
{
	char	*ret;
	char	*zero;

	zero = NULL;
	if ((f.nb < f.arg_len && f.nb * -1 < f.arg_len && d > 0) || f.after_dot > 0
	|| f.flags[1] == 'd' || f.flags[1] == 'i')
		return (sdupfr(str, 1));
	else if (d < 0 && f.nb < f.arg_len + 1 && f.nb * -1 < f.arg_len + 1
	&& f.dot == 0)
		zero = generator_str(0, ' ', 2);
	else if (d < 0 && f.nb > 0)
		zero = generator_str(f.nb - f.arg_len - 1, '0', 1);
	else if (f.nb < 0)
	{
		str = (d < 0 && f.dot == 0 ? ft_sjoin_free("-", str, 0) : str);
		f.arg_len = ft_strlen(str);
		zero = generator_str((f.nb * -1) - f.arg_len, ' ', 0);
		ret = ft_sjoin_free(str, zero, 2);
		return (ret);
	}
	else
		zero = generator_str(f.nb - f.arg_len, '0', 0);
	ret = ft_sjoin_free(zero, str, 2);
	return (ret);
}

char	*ft_handle_d_dot(t_flags f, char *str, int d)
{
	char	*ret;
	char	*zero;

	zero = NULL;
	if (f.flags[0] == '0' && f.nb > f.arg_len && f.after_dot < 0)
		return (sdupfr(str, 1));
	if (f.after_dot <= f.arg_len && d < 0)
	{
		zero = generator_str(0, ' ', 2);
		ret = ft_sjoin_free(zero, str, 2);
		return (ret);
	}
	else if ((((f.after_dot < f.arg_len) && d > 0)
	|| (f.after_dot < f.arg_len + 1 && d < 0)) || (f.nb > f.after_dot
	&& f.nb < f.arg_len && f.after_dot < f.arg_len))
		return (sdupfr(str, 1));
	else if (d < 0 && f.after_dot > f.arg_len)
		zero = generator_str(f.after_dot - f.arg_len, '0', 1);
	else
		zero = generator_str(f.after_dot - f.arg_len, '0', 0);
	ret = ft_sjoin_free(zero, str, 2);
	return (ret);
}

char	*ft_handle_d_nb(t_flags f, char *str, int d)
{
	char	*fill;

	if ((((f.arg_len >= f.nb && d > 0 && f.dot == 1) || (f.flags[0] == '0'
	&& f.dot == 0)) && f.arg_len >= (f.nb * -1)) || (f.dot == 1
	&& (f.after_dot > f.nb * -1 && f.after_dot > f.nb)) || (f.flags[0] == 'd'
	|| f.flags[0] == 'i'))
		return (sdupfr(str, 1));
	else if (f.nb > 0 && d > 0 && f.dot == 1)
		fill = generator_str(f.nb - f.arg_len, ' ', 0);
	else if (d < 0 && f.dot == 0 && f.nb > f.arg_len)
		fill = generator_str(f.nb - f.arg_len - 1, ' ', 0);
	else if (f.nb * -1 > f.arg_len)
	{
		(d < 0 && ft_strchr(f.flags, '.') == NULL ? f.arg_len++ : 0);
		fill = generator_str((f.nb * -1) - f.arg_len, ' ', 0);
	}
	else if ((f.dot == 1 && f.after_dot != 0 && f.after_dot <= f.arg_len)
	|| (f.dot == 0 && f.after_dot == 0) || (f.arg_len > f.after_dot))
		fill = generator_str(f.nb - f.arg_len, ' ', 0);
	else if (f.arg_len <= f.after_dot)
		fill = generator_str(f.nb - f.after_dot, ' ', 0);
	str = (d < 0 && f.dot == 0 ? ft_sjoin_free("-", str, 0) : str);
	return ((f.nb < 0 ? ft_sjoin_free(str, fill, 2) :
	ft_sjoin_free(fill, str, 2)));
}

char	*ft_handle_d_minus(t_flags f, char *str, int d)
{
	char	*ret;
	char	*fill;

	if ((f.flags[0] == '-' && f.flags[1] == '.') || (f.flags[1] == '-'
	&& f.flags[2] == '.') || (f.flags[0] == '-' && f.flags[1] == '0'
	&& f.flags[2] == '.'))
		return (sdupfr(str, 1));
	if (f.dot == 1 && f.after_dot > f.arg_len && f.nb >= f.after_dot)
		fill = generator_str(f.nb - f.after_dot, ' ', 0);
	else if (d < 0 && f.nb >= f.arg_len + 1 && f.dot == 0)
		fill = generator_str(f.nb - f.arg_len - 1, ' ', 0);
	else if (f.nb * -1 > f.arg_len)
	{
		(d < 0 && ft_strchr(f.flags, '.') == NULL ? f.arg_len++ : 0);
		fill = generator_str((f.nb * -1) - f.arg_len, ' ', 0);
	}
	else if (f.nb >= f.arg_len)
		fill = generator_str(f.nb - f.arg_len, ' ', 0);
	else
		fill = ft_strdup("");
	str = (d < 0 && f.dot == 0 ? ft_sjoin_free("-", str, 0) : str);
	ret = ft_sjoin_free(str, fill, 2);
	return (ret);
}

int		do_d_i(t_flags f, va_list ap)
{
	int		d;
	char	*str;

	f.dot = (ft_strchr(f.flags, '.') == NULL ? 0 : 1);
	f.nb = ft_find_nb(f, ap);
	f.after_dot = ft_find_precision_d(f, ap);
	d = (int)va_arg(ap, void *);
	str = (d < 0 ? ft_itoa(d * -1) : ft_itoa(d));
	str = (f.flags[0] == 'd' || f.flags[0] == 'i' ? ft_itoa(d) : str);
	str = ft_incase(d, f, str);
	f.arg_len = ft_strlen(str);
	str = (f.dot == 1 ? ft_handle_d_dot(f, str, d) : str);
	f.arg_len = ft_strlen(str);
	str = ((((f.flags[0] == '0' && (f.after_dot > -1 && f.dot == 1))
	|| ((f.nb > f.arg_len || (f.nb * -1) > f.arg_len) && f.flags[0] != '0'))
	&& ft_strchr(f.flags, '-') == NULL) ? ft_handle_d_nb(f, str, d) : str);
	if (f.flags[0] == '0' && (f.flags[1] != 'd' || f.flags[1] != 'i')
	&& (f.dot == 0 || f.after_dot < 0) && ft_strchr(f.flags, '-') == NULL)
		str = ft_handle_d_zero(f, str, d);
	str = (ft_strchr(f.flags, '-') != NULL && f.flags[1] != '.' && f.flags[1]
	!= 'd' && f.flags[1] != 'i') ? ft_handle_d_minus(f, str, d) : str;
	d = write(1, str, ft_strlen(str));
	(str ? free(str) : 0);
	return (d);
}
