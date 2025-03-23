/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 22:10:31 by amalangu          #+#    #+#             */
/*   Updated: 2025/03/23 18:12:59 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include "libft.h"
# include <limits.h>
# include <stdarg.h>
# include <stdio.h>

int	ft_putchar_int(char c);
int	ft_putstr_int(char *s);

int	ft_printf(const char *s, ...);
int	ft_printf_specifier(va_list args, const char *s);
int	ft_check_specifier(va_list args, const char *s);

int	ft_printf_c(char c);
int	ft_printf_s(char *c);
int	convert_base(int nbr, char *base);

int	ft_printf_i(int nb);
int	ft_printf_x(unsigned int nb, char c);

int	ft_printf_p(void *c);
int	ft_putnbr_base(unsigned long nbr, char *base);

#endif
