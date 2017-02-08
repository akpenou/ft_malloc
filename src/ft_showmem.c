/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_showmem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akpenou <akpenou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 18:01:57 by akpenou           #+#    #+#             */
/*   Updated: 2017/02/05 16:21:50 by akpenou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static int	ft_print_zone(char *name, void *address)
{
	int		i;

	i = 0;
	i += ft_putstr(name);
	i += ft_putstr(" : 0x");
	i += ft_putnbr((size_t)address, 16);
	i += ft_putstr("\n");
	return (i);
}

static int	ft_print_block(void *addr_begin, void *addr_end, unsigned int size,
		bool show_mem)
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
	if (show_mem)
		ft_print_memory(addr_begin, size);
	return (i);
}

static int	ft_print_total(int size)
{
	int		i;

	i = 0;
	i += ft_putstr("total :");
	i += ft_putnbr(size, 10);
	i += ft_putstr("\n");
	return (i);
}

static int	run_mem_block(t_block *mem, bool show_mem)
{
	t_block	*block;
	int		size;

	block = mem;
	size = 0;
	while (block)
	{
		if (block->used)
		{
			size += block->size;
			ft_print_block(block->ptr, block->ptr + block->size, block->size,
					show_mem);
		}
		block = block->next;
	}
	return (size);
}

void		show_alloc(bool show_mem)
{
	t_stdmem		*mem;
	unsigned int	count;

	mem = g_mem.min;
	count = 0;
	while (mem)
	{
		ft_print_zone("TINY", mem->mem);
		count += run_mem_block(mem->mem, show_mem);
		mem = mem->next;
	}
	mem = g_mem.med;
	while (mem)
	{
		ft_print_zone("SMALL", mem->mem);
		count += run_mem_block(mem->mem, show_mem);
		mem = mem->next;
	}
	if (g_mem.ext)
	{
		ft_print_zone("LARGE", g_mem.ext);
		count += run_mem_block(g_mem.ext, show_mem);
	}
	ft_print_total(count);
}
