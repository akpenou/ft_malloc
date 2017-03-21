/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akpenou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/18 16:52:27 by akpenou           #+#    #+#             */
/*   Updated: 2017/03/21 16:24:03 by akpenou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

t_mem			g_mem = {0, 0, 0, 0};

static t_block		*ft_extmem(size_t size)
{
	t_block		*tmp;
	t_block		*new;

	new = mmap(NULL, size + sizeof(t_block), MALLOCPROT, MALLOCMAP, -1, 0);
	new->ptr = (void *)new + sizeof(t_block);
	new->size = size;
	new->next = NULL;
	if (!g_mem.ext)
	{
		g_mem.ext = new;
		new->prev = NULL;
	}
	else
	{
		tmp = g_mem.ext;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
	return (new);
}

t_block				*ft_block(t_block *prev, size_t size)
{
	t_block	*tmp;

	if ((prev->size) <= size + sizeof(t_block))
		return (prev);
	tmp = (void *)((char *)prev->ptr + size);
	tmp->size = prev->size - (size + sizeof(t_block));
	tmp->ptr = (void *)tmp + sizeof(t_block);
	prev->size = prev->size - (tmp->size + sizeof(t_block));
	tmp->next = prev->next;
	if (tmp->next && tmp->next->next)
		tmp->next->next->prev = tmp->next;
	prev->next = tmp;
	tmp->prev = prev;
	tmp->used = 0;
	return (prev);
}

static t_stdmem		*ft_stdmem(t_stdmem *prev, size_t size)
{
	t_stdmem		*ptr;
	t_block			*tmp;

	ptr = mmap(NULL, size, MALLOCPROT, MALLOCMAP, -1, 0);
	ptr->size = size - sizeof(t_stdmem);
	ptr->mem = (void *)ptr + sizeof(t_stdmem);
	ptr->next = NULL;
	tmp = ptr->mem;
	tmp->ptr = (void *)tmp + sizeof(t_block);
	tmp->used = 0;
	tmp->next = NULL;
	tmp->prev = NULL;
	tmp->size = ptr->size - sizeof(t_block);
	if (prev)
		prev->next = ptr;
	return (ptr);
}

static t_block		*ft_find_(size_t size)
{
	t_block		*mem;
	t_stdmem	*stdmem;

	if (size <= TINYZONE)
		stdmem = g_mem.min;
	else if (size <= MEDZONE)
		stdmem = g_mem.med;
	else
		return (ft_extmem(size));
	while (stdmem)
	{
		mem = stdmem->mem;
		while (mem && (mem->size < size + sizeof(t_block) || mem->used))
			mem = mem->next;
		if (mem && mem->size > size)
			return (ft_block(mem, size));
		else if (stdmem->next == NULL)
			ft_stdmem(stdmem, stdmem->size);
		stdmem = stdmem->next;
	}
	return (NULL);
}

void				*ft_malloc(size_t size)
{
	t_block		*ptr;
	int			s;

	if (!g_mem.init)
	{
		s = getpagesize() * 13;
		g_mem.min = ft_stdmem(NULL, s);
		s = 128 * s;
		g_mem.med = ft_stdmem(NULL, s);
		g_mem.init = 1;
	}
	ptr = ft_find_(size);
	ptr->used = 1;
	return (ptr->ptr);
}
