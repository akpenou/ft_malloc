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

static int	run_mem_block(t_block *mem)
{
	t_block	*block;
	int		size;

	block = mem;
	while (block)
	{
		if (block->used)
		{
			size += block->size;
			ft_print_block(block->ptr, block->ptr + block->size, block->size);
		}
		block = block->next;
	}
	return (size);
}

void		show_alloc_mem(void)
{
	t_stdmem		*mem;
	unsigned int	count;

	mem = g_mem.min;
	count = 0;
	while (mem)
	{
		ft_print_zone("TINY", mem->mem);
		count += run_mem_block(mem->mem);
		mem = mem->next;
	}
	mem = g_mem.med;
	while (mem)
	{
		ft_print_zone("SMALL", mem->mem);
		count += run_mem_block(mem->mem);
		mem = mem->next;
	}
	if (g_mem.ext)
	{
		ft_print_zone("LARGE", g_mem.ext);
		count += run_mem_block(g_mem.ext);
	}
	ft_print_total(count);
}
