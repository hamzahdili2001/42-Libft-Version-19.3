/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhdili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/18 09:18:23 by hhdili            #+#    #+#             */
/*   Updated: 2026/10/18 09:18:23 by hhdili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	guard(size_t len, size_t slen, unsigned int start)
{
	size_t	count;

	if (start >= slen)
		count = 0;
	else if (len > slen - start)
		count = slen - start;
	else
		count = len;
	return (count);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;
	size_t	count;
	size_t	slen;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	count = guard(len, slen, start);
	sub = malloc(count + 1);
	if (!sub)
		return (NULL);
	i = 0;
	while (i < count)
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}
