/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstpop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaddoul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 18:46:49 by ada               #+#    #+#             */
/*   Updated: 2020/02/27 19:09:17 by ada              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_element 		*ft_dlstpop(t_dlist **lst, void (*del)(void*), t_element *rear)
{
	t_element	*current;
	t_element	*to_del;

	current = (*lst)->head;
	while (current)
	{
		if (current == rear)
			return (rear);
		to_del = current;
		current = current->next;
		del(to_del->content);
		ft_memdel((void**)&to_del);
	}
	ft_memdel((void**)lst);
	return ((*lst)->head);
}
