/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhdili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/17 14:17:59 by hhdili            #+#    #+#             */
/*   Updated: 2026/10/19 19:48:02 by hhdili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	const char	*big;
	const char	*little;
	size_t		i;
	size_t		j;

	if (!*needle)
		return ((char *)haystack);
	j = 0;
	while (j < len && *haystack)
	{
		i = 0;
		big = haystack;
		little = needle;
		while (j + i < len && *big && *little && (*big == *little))
		{
			big++;
			little++;
			i++;
		}
		if (*little == '\0')
			return ((char *)haystack);
		j++;
		haystack++;
	}
	return (NULL);
}
