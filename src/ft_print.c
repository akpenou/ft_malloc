/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akpenou <akpenou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 11:30:56 by akpenou           #+#    #+#             */
/*   Updated: 2017/03/20 18:46:16 by akpenou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static int	ft_putstr(char *s)
{
	int		i;
	char	*s_cpy;

	i = 0;
	s_cpy = s;
	while (s_cpy && *s_cpy && ++i)
		++s_cpy;
	return (write(1, s, i));
}

static int	ft_putnbr(size_t number, int base)
{
	const char			*alphabet = "0123456789ABCDEF";
	size_t				tmp;
	unsigned int		counter;

	tmp = base;
	counter = 0;
	while (number / tmp >= (size_t)base)
		tmp *= base;
	while (tmp)
	{
		write(1, &alphabet[number / tmp], 1);
		number %= tmp;
		tmp /= base;
		counter++;
	}
	return (counter);
}

int			ft_print_zone(char *name, void *address)
{
	int		i;

	i = 0;
	i += ft_putstr(name);
	i += ft_putstr(" : 0x");
	i += ft_putnbr((size_t)address, 16);
	i += ft_putstr("\n");
	return (i);
}

int			ft_print_block(void *addr_begin, void *addr_end, unsigned int size)
{
	int		i;

	i = 0;
	i += ft_putstr("0x");
	i += ft_putnbr((size_t)addr_begin, 16);
	i += ft_putstr(" - 0x");
	i += ft_putnbr((size_t)addr_end, 16);
	i += ft_putstr(" : ");
	i += ft_putnbr(size, 10);
	i += ft_putstr(" octets\n");
	return (i);
}

int			ft_print_total(int size)
{
	int		i;

	i = 0;
	i += ft_putstr("total :");
	i += ft_putnbr(size, 10);
	i += ft_putstr("\n");
	return (i);
}
