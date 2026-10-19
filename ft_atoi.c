/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhdili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/17 14:35:23 by hhdili            #+#    #+#             */
/*   Updated: 2026/10/18 16:36:15 by hhdili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

static int	issign(unsigned char c)
{
	if (c == '-' || c == '+')
		return (1);
	return (0);
}

static int	ft_isspace(unsigned char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	return (0);
}

static int	ft_overflow(int sign)
{
	if (sign == -1)
		return (0);
	return (-1);
}

int	ft_atoi(const char *str)
{
	long long	result;
	int			sign;

	result = 0;
	sign = 1;
	while (*str && ft_isspace(*str))
		str++;
	if (issign(*str))
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str && ft_isdigit(*str))
	{
		if (result > (9223372036854775807 - (*str - '0')) / 10)
			return (ft_overflow(sign));
		result = result * 10 + (*str - '0');
		str++;
	}
	return ((int)(result * sign));
}
