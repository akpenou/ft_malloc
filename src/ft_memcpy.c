/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akpenou <akpenou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 08:33:38 by akpenou           #+#    #+#             */
/*   Updated: 2017/02/05 16:22:31 by akpenou          ###   ########.fr       */
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
