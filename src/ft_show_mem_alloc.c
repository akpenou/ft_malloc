/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_show_mem_alloc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akpenou <akpenou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 18:01:57 by akpenou           #+#    #+#             */
/*   Updated: 2017/03/21 14:58:01 by akpenou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	show_alloc_mem(void)
{
	pthread_mutex_lock(&g_fastmutex);
	show_alloc(0);
	pthread_mutex_unlock(&g_fastmutex);
}

void	show_alloc_mem_hex(void)
{
	pthread_mutex_lock(&g_fastmutex);
	show_alloc(1);
	pthread_mutex_unlock(&g_fastmutex);
}
