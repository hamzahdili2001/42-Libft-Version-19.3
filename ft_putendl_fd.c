/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhdili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/14 15:23:30 by hhdili            #+#    #+#             */
/*   Updated: 2026/10/18 15:08:26 by hhdili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <fcntl.h>

void	ft_putendl_fd(char *s, int fd)
{
	if (!s)
		return ;
	ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
}
/*
int	main(void)
{
	// int	fd;
	// fd = open("text.test", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	// if (fd == -1)
	//	return (-1);
	ft_putendl_fd("Hamza is testing all the time", 1);
	return (0);
}
*/
