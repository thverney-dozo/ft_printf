/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 04:34:02 by thverney          #+#    #+#             */
/*   Updated: 2019/11/23 17:48:43 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_incase(int d, t_flags f, char *str)
{
	if (d == 0 && ft_strchr(f.flags, '.') != NULL && f.after_dot == 0)
	{
		free(str);
		return (ft_strdup(""));
	}
	if (d == 0 && ft_strchr(f.flags, '.') == NULL)
		return (ft_strdup(str));
	if (f.dot == 1 && f.flags[0] == '0' && f.nb > f.arg_len && f.after_dot < 0)
		return (sdupfr(str, 1));
	if (f.dot == 1)
		return (sdupfr(str, 1));
	if (d < 0 && (f.flags[0] == '0' || ((unsigned int)f.nb <= ft_strlen(str)
	|| ((unsigned int)f.nb * (-1) <= ft_strlen(str)))) && (f.flags[1] == 'd'
	|| f.flags[1] == 'i') && (f.flags[0] != '.' && (f.flags[1] != 'd'
	|| f.flags[1] != 'i')))
		return (ft_sjoin_free("-", str, 0));
	if (d < 0 && ((unsigned int)f.nb <= ft_strlen(str)
	|| ((unsigned int)f.nb * -1 <= ft_strlen(str))) && (f.flags[0] >= '1'
	&& f.flags[0] <= '9' && f.flags[0] >= '0' && f.flags[0] <= '9')
	&& (f.flags[2] == 'd' || f.flags[2] == 'i'))
		return (ft_sjoin_free("-", str, 0));
	return (sdupfr(str, 1));
}

char	*generator_str(int len, int c, int p)
{
	char *str;

	if (len < 0)
		return (ft_strdup(""));
	if (len < 1 && p == 1)
		return (ft_strdup("-"));
	if (p == 1 || p == 2)
		len++;
	if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	str[len] = '\0';
	if (p == 2)
		str[--len] = '-';
	if (p == 1)
		while (len-- > 1)
			str[len] = c;
	else
		while (len--)
			str[len] = c;
	if (p == 1)
		str[len] = '-';
	return (str);
}

int		ft_find_nb(t_flags f, va_list ap)
{
	int i;
	int ret;

	ret = 0;
	i = 0;
	while (f.flags[i] != '\0' && !(f.flags[i] >= '1' && f.flags[i] <= '9'))
	{
		if (f.flags[i] == '.')
			return (0);
		if (f.flags[i] == '*')
		{
			ret = va_arg(ap, int);
			return (ret);
		}
		i++;
	}
	if (f.flags[i] == '\0')
		return (0);
	ret = cestlebon(f, ap, i, ret);
	return (ret);
}

int		cestlebon(t_flags f, va_list ap, int i, int ret)
{
	if (f.flags[i] == '*')
	{
		ret = va_arg(ap, int);
		i++;
	}
	else
	{
		ret = ft_atoi(&f.flags[i]);
		while (isnb(f.flags[i]) == 1)
			i++;
	}
	while (isnb(f.flags[i]) == 0 && f.flags[i] != '\0')
	{
		if (f.flags[i] == '*')
			break ;
		if (f.flags[i] == '.')
			return (ret);
		i++;
	}
	if (f.flags[i] == '\0')
		return (ret);
	else
		return (cestlebon(f, ap, i, ret));
}

int		ft_find_precision(t_flags f, va_list ap)
{
	int i;
	int ret;

	i = 0;
	while (f.flags[i] != '\0' && f.flags[i] != '.')
		i++;
	if (f.flags[i] == '\0')
		return (0);
	if (f.flags[i] == '.')
		i++;
	if (f.flags[i] == '*')
	{
		ret = va_arg(ap, int);
		return (ret);
	}
	ret = ft_atoi(f.flags + i);
	return (ret);
}
