/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhdili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/18 09:08:32 by hhdili            #+#    #+#             */
/*   Updated: 2026/10/20 15:36:36 by hhdili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	slen;
	char	*dup;

	// if (!s)
	//	return (NULL);
	slen = ft_strlen(s);
	dup = malloc(slen + 1);
	if (!dup)
		return (NULL);
	ft_strlcpy(dup, s, slen + 1);
	return (dup);
}
/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	main(void)
{
	printf("%s", ft_strdup(NULL));
		printf("%s", strdup(NULL));
}
*/
