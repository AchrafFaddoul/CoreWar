/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaddoul <afaddoul@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 09:41:11 by afaddoul          #+#    #+#             */
/*   Updated: 2020/02/27 16:18:00 by ada              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char			*read_file(int fd)
{
	char		*buff;
	size_t		buff_size;
	int			ret;
	size_t		i;

	i = 0;
	buff_size = BUFF_SIZE;
	if (!(buff = (char*)ft_memalloc(sizeof(char) * buff_size)))
		ft_error();
	while (i < MAX_SIZE && (ret = read(fd, buff + i, 1) > 0))
	{
		if (i == (buff_size - 1))
		{
			buff_size *= 2;
			if (!(buff = ft_vrealloc(&buff, buff_size)))
			{
				ft_strdel((char**)&buff);
				ft_error();
			}
		}
		i++;
	}
	if (ret == -1)
	{
		ft_strdel((char**)&buff);
		ft_error();
	}
	return (buff);
}
