/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhdili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/18 11:38:53 by hhdili            #+#    #+#             */
/*   Updated: 2026/10/18 16:04:41 by hhdili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static size_t	w_count(const char *s, char c)
{
	int		found;
	size_t	count;

	count = 0;
	found = 0;
	while (*s)
	{
		if (*s == c)
			found = 0;
		else if (found == 0)
		{
			found = 1;
			count++;
		}
		s++;
	}
	return (count);
}

static void	free_arr(char **arr, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static size_t	w_len(char const *s, char c)
{
	size_t	len;

	len = 0;
	while (*s && *s != c)
	{
		len++;
		s++;
	}
	return (len);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	size_t	i;

	if (!s)
		return (NULL);
	arr = malloc(sizeof(char *) * (w_count(s, c) + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			arr[i] = ft_substr(s, 0, w_len(s, c));
			if (!arr[i])
				return (free_arr(arr, i), NULL);
			i++;
			s += w_len(s, c);
		}
		else
			s++;
	}
	arr[i] = NULL;
	return (arr);
}
