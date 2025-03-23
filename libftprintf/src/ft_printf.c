/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 12:57:34 by amalangu          #+#    #+#             */
/*   Updated: 2025/03/23 18:24:02 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libftprintf.h"

int	ft_printf(const char *s, ...)
{
	va_list	args;
	int		count;
	int		tmp;

	va_start(args, s);
	count = 0;
	if (s == 0 || s == NULL)
		return (-1);
	while (*s)
	{
		if (*s == '%')
		{
			tmp = ft_printf_specifier(args, s + 1);
			if (tmp == -1)
				return (-1);
			else
				count += tmp;
			s++;
		}
		else
			count += ft_putchar_int(*s);
		s++;
	}
	va_end(args);
	return (count);
}
