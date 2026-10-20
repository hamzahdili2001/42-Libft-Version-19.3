/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhdili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/17 11:12:58 by hhdili            #+#    #+#             */
/*   Updated: 2026/10/20 16:11:29 by hhdili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	dlen;
	size_t	slen;
	size_t	i;

	slen = ft_strlen(src);
	dlen = 0;
	while (dlen < size && dest[dlen])
		dlen++;
	if (dlen >= size)
		return (size + slen);
	i = 0;
	while (i < slen && dlen + i < size - 1)
	{
		dest[dlen + i] = src[i];
		i++;
	}
	dest[dlen + i] = '\0';
	return (dlen + slen);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char	mem[128] = "hello ";
	char	mem1[128] = "hello ";

	ft_strlcat(mem, mem, 128);
	printf("FT: %s\n", mem);
	strlcat(mem1, mem1, 128);
	printf("OG: %s\n", mem1);
}
*/
