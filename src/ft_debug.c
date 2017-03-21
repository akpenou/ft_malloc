/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_debug.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akpenou <akpenou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 11:00:24 by akpenou           #+#    #+#             */
/*   Updated: 2017/03/21 11:26:44 by akpenou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_malloc.h>

void	ft_debug(char *file, char *function, unsigned int line)
{
	ft_putstr(file);
	ft_putstr(" - ");
	ft_putstr(function);
	ft_putstr(" - ");
	ft_putnbr(line, 10);
	ft_putstr("\n");
}

void	ft_debug_addr(char *message, void *ptr)
{
	ft_putstr(message);
	ft_putnbr((size_t)ptr, 16);
	ft_putstr("\n");
}
