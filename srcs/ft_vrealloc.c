/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vrealloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 00:50:25 by afaddoul          #+#    #+#             */
/*   Updated: 2020/02/25 00:50:38 by ada              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char		*ft_vrealloc(char **buff, size_t buff_size)
{
	char	*new_buff;

	if (!(new_buff = (char*)ft_memalloc(sizeof(char) * buff_size)))
	{
		ft_memdel((void**)buff);
		return (NULL);
	}
	ft_strcpy(new_buff, *buff);
	ft_memdel((void**)buff);
	return (new_buff);
}
