/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akpenou <akpenou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 17:19:02 by akpenou           #+#    #+#             */
/*   Updated: 2017/02/05 17:19:04 by akpenou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <sys/mman.h>
# include <sys/resource.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>

# define TINYZONE			16
# define MEDZONE			128

# define MALLOCPROT	PROT_READ | PROT_WRITE
# define MALLOCMAP	MAP_ANONYMOUS | MAP_PRIVATE

/*
** # define ft_safe_free free
** # define ft_safe_malloc malloc
** # define ft_safe_realloc realloc
** # define ft_safe_calloc calloc
*/

typedef struct				s_stdmem
{
	void					*mem;
	size_t					size;
	struct s_stdmem			*next;
}							t_stdmem;

typedef struct				s_block
{
	size_t					size;
	struct s_block			*next;
	struct s_block			*prev;
	char					used;
	void					*ptr;
}							t_block;

typedef struct				s_mem
{
	char					init;
	t_stdmem				*min;
	t_stdmem				*med;
	t_block					*ext;
}							t_mem;

extern t_mem				g_mem;
extern pthread_mutex_t		g_fastmutex;

/*
** Unsafe functions
*/
void						*ft_malloc(size_t size);
void						ft_free(void *ptr);
void						*ft_realloc(void *ptr, size_t size);

/*
** Show allocations
*/
void						show_alloc_mem();
void						show_alloc_mem_hex(void);
void						show_alloc(bool show_mem);

/*
** Memory tools
*/
t_block						*ft_block(t_block *prev, size_t size);
t_stdmem					*ft_merge(t_block *ptr, t_stdmem **prev);
t_stdmem					*ft_find(t_block *ptr, t_stdmem *mtmp,\
															t_stdmem **prev);
/*
** Standard functions
*/
void						*ft_memcpy(void *dest, const void *src, size_t n);
void						ft_print_memory(void *mem, size_t size);
int							ft_putnbr(size_t number, int base);
int							ft_putstr(char *s);

/*
**	Final functions
*/
void						*ft_safe_malloc(size_t size);
void						ft_safe_free(void *ptr);
void						*ft_safe_realloc(void *ptr, size_t size);
void						*ft_safe_calloc(size_t nmemb, size_t size);

#endif
