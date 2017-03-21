/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akpenou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/18 16:52:32 by akpenou           #+#    #+#             */
/*   Updated: 2017/03/21 14:59:41 by akpenou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static int			ft_find_ext(t_block *ptr)
{
	t_block	*tmp;

	tmp = g_mem.ext;
	while (tmp)
	{
		if (tmp == ptr)
			return (1);
		tmp = tmp->next;
	}
	return (0);
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
	if (!(ft_find(tmp, g_mem.min, NULL) || ft_find(tmp, g_mem.med, NULL) ||
				ft_find_ext(tmp)))
		return (NULL);
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
		ft_memcpy(new, tmp->ptr, size < tmp->size ? size : tmp->size);
		ft_free(ptr);
	}
	return (new);
}
