/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhdili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/17 10:00:19 by hhdili            #+#    #+#             */
/*   Updated: 2026/10/19 19:40:19 by hhdili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// make sure to do !dest && !src does not need SEGV test it against the OG
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;
	size_t				i;

	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}

#include <stdio.h>

int	main(void)
{
	printf("%s", ft_memcpy("Hello", "hell", 5));
	return (0);
}
