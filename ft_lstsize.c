/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhdili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 09:15:35 by hhdili            #+#    #+#             */
/*   Updated: 2026/10/19 19:38:29 by hhdili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

unsigned int	ft_lstsize(t_list *lst)
{
	t_list			*current;
	unsigned int	size;

	size = 0;
	current = lst;
	while (current)
	{
		current = current->next;
		size++;
	}
	return (size);
}
