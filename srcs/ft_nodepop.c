/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nodepop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaddoul <afaddoul@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 20:15:42 by afaddoul          #+#    #+#             */
/*   Updated: 2020/03/06 20:41:23 by afaddoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void			ft_nodepop(t_element *elm)
{
	t_element 	*next;
	t_element 	*prev;

	next = elm->next;
	prev = elm->prev;
	next->prev = prev;
	prev->next = next;
	ft_strdel((char**)&((t_instru*)(elm->content))->buff);
	ft_memdel((void**)&elm->content);
	ft_memdel((void**)&elm);
}
