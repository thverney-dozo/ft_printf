/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 20:47:07 by thverney          #+#    #+#             */
/*   Updated: 2019/11/22 19:08:45 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int		digit_count(long nb)
{
	size_t	i;

	i = 0;
	while (nb)
	{
		nb /= 16;
		i++;
	}
	return (i);
}

char	*ft_itoa_base(long long int value, int param)
{
	char	*ret;
	char	*tab_base;
	int		taille;
	int		i;
	int		sign;

	tab_base = (param == 0 ? "0123456789abcdef" : "0123456789ABCDEF");
	sign = (value < 0 ? 1 : 0);
	value = (value < 0 ? -value : value);
	if (value == 0)
		return (ft_strdup("0"));
	taille = (sign ? digit_count(value) + 1 : digit_count(value));
	if (!(ret = (char *)malloc(sizeof(char) * (taille + 1))))
		return (NULL);
	i = 1;
	sign ? (ret[0] = '-') : 0;
	while (value != 0)
	{
		ret[taille - i++] = tab_base[value % 16];
		value /= 16;
	}
	ret[taille] = '\0';
	return (ret);
}
