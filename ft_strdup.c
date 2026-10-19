/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhdili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/18 09:08:32 by hhdili            #+#    #+#             */
/*   Updated: 2026/10/18 09:08:32 by hhdili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	slen;
	char	*dup;

	slen = ft_strlen(s);
	dup = malloc(slen + 1);
	if (!dup)
		return (NULL);
	ft_strlcpy(dup, s, slen + 1);
	return (dup);
}
