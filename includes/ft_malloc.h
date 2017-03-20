/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akpenou <akpenou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 17:19:02 by akpenou           #+#    #+#             */
/*   Updated: 2017/03/20 18:41:25 by akpenou          ###   ########.fr       */
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


# define ft_free free
# define ft_malloc malloc
# define ft_realloc realloc


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

void						*ft_malloc(size_t size);
void						ft_free(void *ptr);
t_block						*ft_block(t_block *prev, size_t size);
void						*ft_memcpy(void *dest, const void *src, size_t n);
void						*ft_realloc(void *ptr, size_t size);
void						show_alloc_mem();
int							ft_print_block(void *addr_begin, void *addr_end,\
														unsigned int size);
int							ft_print_zone(char *name, void *address);
void						ft_extendblock(t_block *tmp, size_t size);
int							ft_print_total(int size);

#endif
