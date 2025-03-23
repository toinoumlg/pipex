/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_nbr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalangu <amalangu@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 09:19:12 by amalangu          #+#    #+#             */
/*   Updated: 2025/03/23 18:24:18 by amalangu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libftprintf.h"

int	ft_putnbr_base(unsigned long nbr, char *base)
{
	int		count;
	int		base_l;
	char	digits[20];
	int		i;

	count = 0;
	base_l = ft_strlen(base);
	if (nbr == 0)
		return (ft_putchar_int(base[0]));
	i = 0;
	while (nbr > 0)
	{
		digits[i++] = base[nbr % base_l];
		nbr /= base_l;
	}
	while (--i >= 0)
		count += ft_putchar_int(digits[i]);
	return (count);
}

int	ft_printf_x(unsigned int nb, char c)
{
	int	count;

	if (c == 'x')
		count = ft_putnbr_base(nb, "0123456789abcdef");
	if (c == 'X')
		count = ft_putnbr_base(nb, "0123456789ABCDEF");
	if (c == 'u')
		count = ft_putnbr_base(nb, "0123456789");
	return (count);
}

int	ft_printf_p(void *c)
{
	int		count;
	long	nbr;

	nbr = (unsigned long)c;
	if (nbr == 0)
		return (ft_putstr_int("(nil)"));
	count = ft_putstr_int("0x");
	count += ft_putnbr_base(nbr, "0123456789abcdef");
	return (count);
}

int	ft_printf_i(int nb)
{
	char	*str_nb;
	int		len;

	str_nb = ft_itoa(nb);
	len = ft_putstr_int(str_nb);
	free(str_nb);
	return (len);
}
