/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vrealloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaddoul <afaddoul@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 21:07:38 by afaddoul          #+#    #+#             */
/*   Updated: 2020/03/12 21:07:38 by afaddoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char		*ft_vrealloc(char *buff, size_t buff_size)
{
	char	*new_buff;

	if (!(new_buff = (char*)ft_memalloc(sizeof(char) * (buff_size + 1))))
	{
		ft_strdel((char**)&buff);
		return (NULL);
	}
	ft_strcpy(new_buff, buff);
	ft_strdel((char**)&(buff));
	return (new_buff);
}
