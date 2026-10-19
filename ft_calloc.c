/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhdili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/17 15:49:58 by hhdili            #+#    #+#             */
/*   Updated: 2026/10/19 18:55:50 by hhdili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t			len;
	unsigned char	*ptr;

	if (size != 0 && count > SIZE_MAX / size)
		return (NULL);
	len = count * size;
	if (!len)
		len = 1;
	ptr = malloc(len);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, len);
	return ((void *)ptr);
}
