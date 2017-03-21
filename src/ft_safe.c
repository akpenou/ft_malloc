/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_safe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akpenou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/18 16:52:27 by akpenou           #+#    #+#             */
/*   Updated: 2017/03/21 16:11:10 by akpenou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_malloc.h>

pthread_mutex_t g_fastmutex = PTHREAD_MUTEX_INITIALIZER;

static void	init(void)
{
	int			s;

	if (!g_mem.init)
	{
		s = getpagesize() * 13;
		g_mem.min = ft_stdmem(NULL, s);
		s = 128 * s;
		g_mem.med = ft_stdmem(NULL, s);
		g_mem.init = 1;
	}
}

void		*malloc(size_t size)
{
	void	*ptr;

	init();
	pthread_mutex_lock(&g_fastmutex);
	ptr = ft_malloc(size);
	pthread_mutex_unlock(&g_fastmutex);
	return (ptr);
}

void		free(void *ptr)
{
	init();
	pthread_mutex_lock(&g_fastmutex);
	ft_free(ptr);
	pthread_mutex_unlock(&g_fastmutex);
}

void		*realloc(void *ptr, size_t size)
{
	init();
	if (!(ptr && size))
	{
		if (!ptr)
			return (malloc(size));
		free(ptr);
		return (NULL);
	}
	pthread_mutex_lock(&g_fastmutex);
	ptr = ft_realloc(ptr, size);
	pthread_mutex_unlock(&g_fastmutex);
	return (ptr);
}

void		*calloc(size_t nmemb, size_t size)
{
	char	*ptr;
	int		total_size;
	int		i;

	init();
	total_size = nmemb * size;
	if (!(ptr = malloc(total_size)))
		return (NULL);
	i = -1;
	while (++i < total_size)
		ptr[i] = 0;
	return ((void *)ptr);
}
