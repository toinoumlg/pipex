/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_specifier.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 08:11:20 by amalangu          #+#    #+#             */
/*   Updated: 2025/03/23 18:24:14 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libftprintf.h"

int	ft_printf_specifier(va_list args, const char *s)
{
	if (*s == 'c')
		return (ft_putchar_int((char)va_arg(args, int)));
	else if (*s == 's')
		return (ft_putstr_int(va_arg(args, char *)));
	else if (*s == 'p')
		return (ft_printf_p(va_arg(args, void *)));
	else if (*s == 'd' || *s == 'i')
		return (ft_printf_i(va_arg(args, int)));
	else if (*s == 'u')
		return (ft_printf_x(va_arg(args, unsigned long), *s));
	else if (*s == 'x')
		return (ft_printf_x(va_arg(args, unsigned long), *s));
	else if (*s == 'X')
		return (ft_printf_x(va_arg(args, unsigned long), *s));
	else if (*s == '%')
		return (ft_putchar_int('%'));
	return (-1);
}
