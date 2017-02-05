/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akpenou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/18 16:52:30 by akpenou           #+#    #+#             */
/*   Updated: 2017/02/05 16:23:41 by akpenou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static t_stdmem		*ft_find(t_block *ptr, t_stdmem *mtmp, t_stdmem **prev)
{
	t_block		*btmp;

	if (prev)
		*prev = NULL;
	while (mtmp)
	{
		if ((void *)mtmp->mem <= (void *)ptr &&
				(void *)ptr <= (void *)mtmp->mem + mtmp->size)
		{
			btmp = mtmp->mem;
			while (btmp)
			{
				if (btmp == ptr)
					return (mtmp);
				btmp = btmp->next;
			}
			return (NULL);
		}
		if (prev)
			*prev = mtmp;
		mtmp = mtmp->next;
	}
	return (NULL);
}

static int			ft_free_ext(t_block *ptr)
{
	t_block		*tmp;
	int			done;

	tmp = g_mem.ext;
	done = 0;
	while (tmp)
	{
		if (tmp == ptr)
		{
			if (tmp->next)
				tmp->next->prev = tmp->prev;
			if (tmp->prev)
				tmp->prev->next = tmp->next;
			if (tmp == g_mem.ext)
				g_mem.ext = tmp->next;
			munmap(tmp, tmp->size + sizeof(t_block));
			done = 1;
			break ;
		}
		tmp = tmp->next;
	}
	return (done);
}

static t_stdmem		*ft_merge(t_block *ptr, t_stdmem **prev)
{
	t_stdmem	*mtmp;

	if (!((mtmp = ft_find(ptr, g_mem.min, prev)) ||
				(mtmp = ft_find(ptr, g_mem.med, prev))))
		return (NULL);
	ptr->used = 0;
	if (ptr->prev && !ptr->prev->used)
	{
		ptr->prev->next = ptr->next;
		ptr->prev->size += sizeof(t_block) + ptr->size;
		if (ptr->next)
			ptr->next->prev = ptr->prev;
		ptr = ptr->prev;
	}
	if (ptr->next && !ptr->next->used)
	{
		ptr->size += sizeof(t_block) + ptr->next->size;
		ptr->next = ptr->next->next;
		if (ptr->next)
			ptr->next->prev = ptr;
	}
	return (mtmp);
}

void				ft_free(void *ptr)
{
	t_stdmem	*mtmp;
	t_stdmem	*prev;
	t_block		*tmp;

	tmp = ptr - sizeof(t_block);
	if (ft_free_ext(tmp))
		return ;
	mtmp = ft_merge(tmp, &prev);
	if (prev && !((t_block *)mtmp->mem)->next)
	{
		prev->next = mtmp->next;
		munmap(mtmp, mtmp->size + sizeof(mtmp));
	}
}

void				ft_extendblock(t_block *tmp, size_t size)
{
	t_block		*new;

	new = (void *)tmp->ptr + size;
	new->size = tmp->size + tmp->next->size - size;
	tmp->used = 1;
	tmp->size = size;
	tmp->next->prev = new;
	if (tmp->next->next)
		tmp->next->next->prev = new;
	new->next = tmp->next->next;
	tmp->next = new;
	new->prev = tmp;
	new->used = 0;
	new->ptr = (void *)new + sizeof(t_block);
}

void				*ft_realloc(void *ptr, size_t size)
{
	t_block		*tmp;
	t_block		*new;

	tmp = ptr - sizeof(t_block);
	if (!(ft_find(tmp, g_mem.min, NULL) || ft_find(tmp, g_mem.med, NULL)))
		return (ft_malloc(size));
	if (tmp->size > size + sizeof(t_block))
	{
		new = ft_block(tmp, size);
		ft_merge(tmp->next, NULL);
	}
	else if (tmp->size < size && tmp->next && !tmp->next->used &&
			tmp->next->size + tmp->size > size)
	{
		ft_extendblock(tmp, size);
		return (tmp->ptr);
	}
	else
	{
		new = ft_malloc(size);
		ft_memcpy(new, tmp->ptr, size);
		ft_free(ptr);
	}
	return (new);
}
