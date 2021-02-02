/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_c.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 20:31:08 by thverney          #+#    #+#             */
/*   Updated: 2019/11/22 20:44:05 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_handle_c_nb(t_flags f, char *str)
{
	char	*ret;
	char	*fill;

	if (f.nb > 0)
		fill = generator_str(f.nb - 1, ' ', 0);
	else if (f.nb < 0)
		fill = generator_str((f.nb * -1) - 1, ' ', 0);
	ret = (f.nb > 0 ? ft_sjoin_free(fill, str, 2) :
	ft_sjoin_free(str, fill, 2));
	return (ret);
}

char	*ft_handle_c_minus(t_flags f, char *str)
{
	char	*ret;
	char	*fill;

	if ((f.flags[0] == '-' && f.flags[1] == '.') || (f.flags[1] == '-'
	&& f.flags[2] == '.') || (f.flags[0] == '-' && f.flags[1] == '0'
	&& f.flags[2] == '.') || (f.flags[0] == '-' && f.flags[1] == 'c'))
		return (sdupfr(str, 1));
	else if (f.nb < 0)
	{
		fill = generator_str((f.nb * -1) - 1, ' ', 0);
		ret = ft_sjoin_free(str, fill, 2);
	}
	else
	{
		fill = generator_str(f.nb - 1, ' ', 0);
		ret = ft_sjoin_free(str, fill, 2);
	}
	return (ret);
}

int		ft_backzero(t_flags f)
{
	int		length;

	length = (f.nb > 0 ? f.nb : 1);
	length = (f.nb < 0 ? (f.nb * -1) : length);
	if ((f.flags[0] != '0' && f.nb != 0 && ft_strchr(f.flags, '-') == NULL))
		while (f.nb-- > 1)
			ft_putchar(' ');
	if (f.flags[0] == '0' && ft_strchr(f.flags, '-') == NULL)
		while (f.nb-- > 1)
			ft_putchar('0');
	ft_putchar('\0');
	if (ft_strchr(f.flags, '-') != NULL && f.nb > 0)
		while (f.nb-- > 1)
			ft_putchar(' ');
	else if (((ft_strchr(f.flags, '-') != NULL) || (f.flags[0] != '0'
	&& f.nb != 0 && ft_strchr(f.flags, '-') == NULL)) && f.nb < 0)
	{
		while (f.nb++ < -1 && f.flags[0] == '-')
			ft_putchar(' ');
		while (f.nb++ < -1 && f.flags[0] != '-')
			ft_putchar(' ');
	}
	return (length);
}

int		do_c(t_flags f, va_list ap)
{
	char	c;
	char	*str;
	int		i;

	f.nb = ft_find_nb(f, ap);
	f.after_dot = ft_find_precision(f, ap);
	c = va_arg(ap, int);
	if (c == '\0')
		return (ft_backzero(f));
	if (!(str = (char*)malloc(sizeof(char) * 2)))
		return (0);
	str[0] = c;
	str[1] = '\0';
	if (f.flags[0] != '0' && ft_strchr(f.flags, '-') == NULL && f.nb != 0)
		str = ft_handle_c_nb(f, str);
	if (ft_strchr(f.flags, '-') != NULL)
		str = ft_handle_c_minus(f, str);
	i = write(1, str, ft_strlen(str));
	free(str);
	return (i);
}
