/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vrealloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 00:50:25 by afaddoul          #+#    #+#             */
/*   Updated: 2020/02/27 16:12:47 by ada              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char		*ft_vrealloc(char **buff, size_t buff_size)
{
	char	*new_buff;

	if (!(new_buff = (char*)ft_memalloc(sizeof(char) * buff_size)))
	{
		ft_strdel((char**)&buff);
		return (NULL);
	}
	ft_strcpy(new_buff, *buff);
	ft_strdel((char**)(buff));
	return (new_buff);
}
