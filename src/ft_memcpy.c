/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akpenou <akpenou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 08:33:38 by akpenou           #+#    #+#             */
/*   Updated: 2017/03/20 18:15:39 by akpenou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

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

void	ft_extendblock(t_block *tmp, size_t size)
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
