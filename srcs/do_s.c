/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_s.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 19:48:55 by thverney          #+#    #+#             */
/*   Updated: 2019/11/22 20:46:56 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_handle_s_dot(t_flags f, char *str)
{
	char	*ret;
	char	*zero;
	int		i;
	int		dex;

	zero = NULL;
	i = 0;
	dex = (f.after_dot < f.arg_len ? f.after_dot : f.arg_len);
	if (!(ret = (char *)malloc(sizeof(char) * (dex + 1))))
		return (NULL);
	while (dex > 0)
	{
		ret[i] = str[i];
		dex--;
		i++;
	}
	ret[i] = '\0';
	free(str);
	return (ret);
}

char	*ft_handle_s_nb(t_flags f, char *str)
{
	char	*ret;
	char	*fill;

	if ((f.nb <= f.arg_len || f.flags[0] == '0') && (f.nb * -1) < f.arg_len)
		return (sdupfr(str, 1));
	else if (f.nb * -1 > f.arg_len)
	{
		fill = generator_str((f.nb * -1) - f.arg_len, ' ', 0);
		ret = ft_sjoin_free(str, fill, 2);
		return (ret);
	}
	else
		fill = generator_str(f.nb - f.arg_len, ' ', 0);
	ret = ft_sjoin_free(fill, str, 2);
	return (ret);
}

char	*ft_handle_s_minus(t_flags f, char *str)
{
	char	*ret;
	char	*fill;

	if ((f.flags[0] == '-' && f.flags[1] == '.') || (f.flags[1] == '-'
	&& f.flags[2] == '.') || (f.flags[0] == '-' && f.flags[1] == '0'
	&& f.flags[2] == '.') || (f.flags[0] == '-' && (f.flags[1] == 'd'
	|| f.flags[1] == 'i')))
		return (sdupfr(str, 1));
	if (f.pos_dot != NULL && f.nb > f.arg_len)
		fill = generator_str(f.nb - f.arg_len, ' ', 0);
	else if (f.nb * -1 > f.arg_len)
	{
		fill = generator_str((f.nb * -1) - f.arg_len, ' ', 0);
		ret = ft_sjoin_free(str, fill, 2);
		return (ret);
	}
	else
		fill = generator_str(f.nb - f.arg_len, ' ', 0);
	ret = ft_sjoin_free(str, fill, 2);
	return (ret);
}

int		do_s(t_flags f, va_list ap)
{
	char	*str;
	int		d;

	f.nb = ft_find_nb(f, ap);
	f.after_dot = ft_find_precision(f, ap);
	str = (char*)va_arg(ap, void *);
	str = sdupfr(str, 0);
	if (str == NULL)
		str = ft_strdup("(null)");
	f.arg_len = ft_strlen(str);
	f.pos_dot = ft_strchr(f.flags, '.');
	if (f.pos_dot != NULL && f.after_dot < f.arg_len && f.after_dot >= 0)
		str = ft_handle_s_dot(f, str);
	f.arg_len = ft_strlen(str);
	if (((f.flags[0] != '0' && f.nb > f.arg_len) || (f.nb * -1) > f.arg_len)
	&& f.nb != 0 && ft_strchr(f.flags, '-') == NULL)
		str = ft_handle_s_nb(f, str);
	f.arg_len = ft_strlen(str);
	if (ft_strchr(f.flags, '-') != NULL && f.nb != 0 && f.flags[1] != '.'
	&& (f.nb > f.arg_len || (f.nb * -1) > f.arg_len))
		str = ft_handle_s_minus(f, str);
	d = write(1, str, ft_strlen(str));
	(str ? free(str) : 0);
	return (d);
}
