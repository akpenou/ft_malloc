/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akpenou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/18 16:52:32 by akpenou           #+#    #+#             */
/*   Updated: 2016/05/18 16:52:35 by akpenou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

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
