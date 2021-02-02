/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 19:08:19 by thverney          #+#    #+#             */
/*   Updated: 2021/02/02 15:08:59 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
#include <unistd.h>

int		ft_parse(t_flags f, va_list ap)
{
	int i;

	i = ft_strlen(f.flags) - 1;
	f.count = 0;
	f.type = f.flags[i];
	f.count = (f.type == 'c' ? do_c(f, ap) : f.count);
	f.count = (f.type == 's' ? do_s(f, ap) : f.count);
	f.count = (f.type == 'p' ? do_p(f, ap) : f.count);
	f.count = (f.type == 'd' || f.type == 'i' ? do_d_i(f, ap) : f.count);
	f.count = (f.type == 'u' ? do_u(f, ap) : f.count);
	f.count = (f.type == 'x' || f.type == 'X' ? do_x(f, ap) : f.count);
	f.count = (f.type == '%' ? do_mod(f, ap) : f.count);
	return (f.count);
}

void	ft_splitf(t_flags *f, const char *s, va_list ap)
{
	while (ft_strchr(f->type_data, s[f->i]) == NULL)
		f->i++;
	f->flags = ft_substr(s + 1, 0, f->i);
	f->count += ft_parse(*f, ap);
	free(f->flags);
}

int		ft_printf(const char *s, ...)
{
	t_flags		f;
	va_list		ap;

	f.count = 0;
	f.type_data = "cspdiuxX%";
	va_start(ap, s);
	while (*s)
	{
		f.i = 1;
		if (*s == '%')
		{
			ft_splitf(&f, s, ap);
			s++;
		}
		else
		{
			ft_putchar(*s);
			f.count++;
		}
		s += f.i;
	}
	va_end(ap);
	return (f.count);
}
