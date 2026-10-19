/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhdili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/18 14:10:02 by hhdili            #+#    #+#             */
/*   Updated: 2026/10/19 19:37:56 by hhdili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_intlen(long nbr)
{
	size_t	len;

	len = 0;
	if (nbr == 0)
		return (1);
	if (nbr < 0)
	{
		len++;
		nbr = -nbr;
	}
	while (nbr > 0)
	{
		len++;
		nbr /= 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*ptr;
	size_t	nlen;
	long	nbr;

	nbr = n;
	nlen = ft_intlen(nbr);
	ptr = malloc(nlen + 1);
	if (!ptr)
		return (NULL);
	ptr[nlen] = '\0';
	if (nbr < 0)
	{
		ptr[0] = '-';
		nbr = -nbr;
	}
	if (nbr == 0)
		ptr[0] = '0';
	while (nbr > 0)
	{
		ptr[--nlen] = nbr % 10 + '0';
		nbr /= 10;
	}
	return (ptr);
}
