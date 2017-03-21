/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akpenou <akpenou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 11:30:56 by akpenou           #+#    #+#             */
/*   Updated: 2017/03/21 16:11:42 by akpenou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

int		ft_repeat_char(char c, unsigned int n)
{
	unsigned int	i;

	i = -1;
	if ((int)n < 0)
		return (0);
	while (++i < n)
		write(1, &c, 1);
	return ((int)n);
}

int		ft_putstr(char *s)
{
	int		i;
	char	*s_cpy;

	i = 0;
	s_cpy = s;
	while (s_cpy && *s_cpy && ++i)
		++s_cpy;
	return (write(1, s, i));
}

int		ft_putnbr(size_t number, int base)
{
	const char			*alphabet = "0123456789ABCDEF";
	unsigned int		counter;
	size_t				tmp;

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

void	ft_print_memory(void *mem, size_t size)
{
	char	*mem_cpy;
	char	tab[64];
	size_t	i;

	i = -1;
	mem_cpy = mem;
	while (++i < size)
	{
		if (!(i % 64))
		{
			if (i)
				write(1, tab, 64);
			ft_putstr("\n");
			ft_memcpy(tab, &mem_cpy[i], 64);
		}
		ft_putnbr(mem_cpy[i], 10);
		ft_putstr(" ");
		if (!(0x20 <= mem_cpy[i] && mem_cpy[i] <= 0x7E))
			tab[i % 64] = '.';
	}
	ft_repeat_char(' ', 64 - i);
	write(1, tab, i % 64);
	ft_putstr("\n");
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*src_cpy;
	unsigned char	*dest_cpy;

	i = -1;
	src_cpy = (unsigned char*)src;
	dest_cpy = (unsigned char*)dest;
	while (++i < n)
		dest_cpy[i] = src_cpy[i];
	return (dest_cpy);
}
