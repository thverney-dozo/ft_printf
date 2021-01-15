/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_mod.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 20:56:22 by thverney          #+#    #+#             */
/*   Updated: 2019/11/22 20:44:23 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_handle_mod_zero(t_flags f, char *str)
{
	char	*ret;
	char	*zero;

	zero = NULL;
	if (f.nb < 1)
		return (sdupfr(str, 1));
	else
	{
		zero = generator_str(f.nb - 1, '0', 0);
		ret = ft_sjoin_free(zero, str, 2);
	}
	return (ret);
}

char	*ft_handle_mod_nb(t_flags f, char *str)
{
	char	*ret;
	char	*fill;

	ret = NULL;
	if (f.nb == 0 || f.flags[0] == '0')
		return (sdupfr(str, 1));
	else if (f.nb > 0)
	{
		fill = generator_str(f.nb - 1, ' ', 0);
		ret = ft_sjoin_free(fill, str, 2);
	}
	else if (f.nb < 0)
	{
		fill = generator_str((f.nb * -1) - 1, ' ', 0);
		ret = ft_sjoin_free(str, fill, 2);
	}
	return (ret);
}

char	*ft_handle_mod_minus(t_flags f, char *str)
{
	char	*ret;
	char	*fill;

	if ((f.flags[0] == '-' && f.flags[1] == '.') || (f.flags[1] == '-'
	&& f.flags[2] == '.') || (f.flags[0] == '-' && f.flags[1] == '0'
	&& f.flags[2] == '.') || (f.flags[0] == '-' && f.flags[1] == '%')
	|| (f.nb == 0))
		return (sdupfr(str, 1));
	if (f.nb > 0)
		fill = generator_str(f.nb - 1, ' ', 0);
	else if (f.nb < 0)
		fill = generator_str((f.nb * -1) - 1, ' ', 0);
	ret = ft_sjoin_free(str, fill, 2);
	return (ret);
}

int		do_mod(t_flags f, va_list ap)
{
	char	*str;
	int		d;

	f.nb = ft_find_nb(f, ap);
	f.after_dot = ft_find_precision(f, ap);
	if (!(str = (char*)malloc(sizeof(char) * 2)))
		return (0);
	str[0] = '%';
	str[1] = '\0';
	if (((f.flags[0] >= '1' && f.flags[0] <= '9') || f.flags[0] == '*')
	|| (f.nb != 0 && ft_strchr(f.flags, '-') == NULL))
		str = ft_handle_mod_nb(f, str);
	if (f.flags[0] == '0' && ft_strchr(f.flags, '-') == NULL)
		str = ft_handle_mod_zero(f, str);
	if (ft_strchr(f.flags, '-') != NULL)
		str = ft_handle_mod_minus(f, str);
	ft_putstr(str);
	d = ft_strlen(str);
	(str ? free(str) : 0);
	return (d);
}
