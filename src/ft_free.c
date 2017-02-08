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

t_stdmem		*ft_find(t_block *ptr, t_stdmem *mtmp, t_stdmem **prev)
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

t_stdmem		*ft_merge(t_block *ptr, t_stdmem **prev)
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

	if (!ptr)
		return ;
	tmp = ptr - sizeof(t_block);
	if (ft_free_ext(tmp))
		return ;
	if (!(mtmp = ft_merge(tmp, &prev)))
		return ;
	if (prev && !((t_block *)mtmp->mem)->next)
	{
		prev->next = mtmp->next;
		munmap(mtmp, mtmp->size + sizeof(mtmp));
	}
}
