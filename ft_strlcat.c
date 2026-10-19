/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhdili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/17 11:12:58 by hhdili            #+#    #+#             */
/*   Updated: 2026/10/17 11:12:58 by hhdili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	dlen;
	size_t	slen;
	size_t	i;
	char	*dp;

	dlen = 0;
	slen = ft_strlen(src);
	while (dlen < size && dest[dlen])
		dlen++;
	if (size == 0)
		return (slen);
	if (dlen == size)
		return (size + slen);
	i = 0;
	dp = dest + dlen;
	while (src[i] && i < size - dlen - 1)
		*dp++ = src[i++];
	*dp = '\0';
	return (dlen + slen);
}
