/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 21:18:59 by thverney          #+#    #+#             */
/*   Updated: 2019/11/22 20:21:35 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_convert_u(unsigned int a)
{
	long long d;

	d = (long long)a;
	if (d == -0 || d == 0)
		return (ft_strdup("0"));
	else if (d <= -2)
	{
		d *= -1;
		return (ft_itoa(4294967296 - d));
	}
	else if (d == -1)
		return (ft_itoa(4294967295));
	if (d > 0)
		return (ft_itoa((long long int)d));
	return (ft_strdup("0"));
}

int		ft_find_precision_d(t_flags f, va_list ap)
{
	int i;
	int ret;
	int len;

	len = ft_strlen(f.flags);
	while (f.flags[len] != '.' && len > 0)
		len--;
	if (f.flags[len] != '.')
		return (0);
	if (f.flags[len + 1] == '*')
	{
		ret = va_arg(ap, int);
		return (ret);
	}
	i = len + 1;
	ret = ft_atoi(f.flags + i);
	return (ret);
}

char	*ft_prefix(char *str)
{
	int		i;
	char	*ret;
	int		size;
	int		j;

	size = ft_strlen(str);
	if (!(ret = (char*)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	i = 2;
	j = 0;
	ret[0] = '0';
	ret[1] = 'x';
	while (i <= size + 2)
	{
		ret[i++] = str[j++];
	}
	ret[i] = '\0';
	free(str);
	return (ret);
}

char	*sdupfr(char *s1, size_t n)
{
	int		i;
	char	*dest;

	i = 0;
	if (s1 == NULL)
		return (NULL);
	while (s1[i])
		i++;
	if (!(dest = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	i = -1;
	while (s1[++i] != '\0')
		dest[i] = s1[i];
	dest[i] = '\0';
	n == 1 ? free(s1) : 1;
	return (dest);
}

char	*ft_sjoin_free(char const *dst, char const *src, size_t n)
{
	char	*new;
	int		i;
	int		j;
	int		k;

	if (!dst || !src)
		return (NULL);
	i = 0;
	j = 0;
	k = 0;
	if (!(new = (char *)malloc(sizeof(char) *
					(ft_strlen(src) + ft_strlen(dst) + 1))))
		return (NULL);
	while (dst[i] || src[j])
	{
		if (dst[i])
			new[k++] = dst[i++];
		else
			new[k++] = src[j++];
	}
	new[k] = '\0';
	(void)n;
	n >= 1 ? free((void*)dst) : 1;
	n == 2 || n == 0 ? free((void*)src) : 1;
	return (new);
}
