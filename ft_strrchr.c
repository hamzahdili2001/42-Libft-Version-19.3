/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhdili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/17 12:05:09 by hhdili            #+#    #+#             */
/*   Updated: 2026/10/19 19:34:35 by hhdili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(char const *s, int c)
{
	const char	*ptr;
	size_t		i;

	ptr = NULL;
	i = 0;
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			ptr = &s[i];
		i++;
	}
	if ((unsigned char)c == '\0')
		ptr = &s[i];
	return ((char *)ptr);
}
