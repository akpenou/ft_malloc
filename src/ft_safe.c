/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_safe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akpenou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/18 16:52:27 by akpenou           #+#    #+#             */
/*   Updated: 2017/02/05 16:23:43 by akpenou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

pthread_mutex_t g_fastmutex = PTHREAD_MUTEX_INITIALIZER;

void	*ft_safe_malloc(size_t size)
{
	void	*ptr;

	pthread_mutex_lock(&g_fastmutex);
	ptr = ft_malloc(size);
	pthread_mutex_unlock(&g_fastmutex);
	return (ptr);
}

void	ft_safe_free(void *ptr)
{
	pthread_mutex_lock(&g_fastmutex);
	ft_free(ptr);
	pthread_mutex_unlock(&g_fastmutex);
}

void	*ft_safe_realloc(void *ptr, size_t size)
{
	void	*ptr;

	pthread_mutex_lock(&g_fastmutex);
	if (!(ptr && size))
	{
		if (!ptr)
			return (ft_malloc(size));
		ft_free(ptr);
		return (NULL);
	}
	ptr = ft_realloc(ptr, size);
	pthread_mutex_unlock(&g_fastmutex);
	return (ptr);
}

void	*ft_safe_calloc(size_t nmemb, size_t size)
{
	char	*ptr;
	int		total_size;
	int		i;

	total_size = nmemb * size;
	pthread_mutex_lock(&g_fastmutex);
	if (!(ptr = ft_malloc(size)))
		return (NULL);
	pthread_mutex_unlock(&g_fastmutex);
	i = -1;
	while (++i < total_size)
		ptr[i] = 0;
	return ((void *)ptr)
}
