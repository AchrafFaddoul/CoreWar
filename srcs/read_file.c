/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaddoul <afaddoul@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 09:41:11 by afaddoul          #+#    #+#             */
/*   Updated: 2020/01/12 19:00:51 by afaddoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char	*read_file(int fd)
{
	char 		*buff;
	size_t 		buff_size;
	int		ret;
	size_t		i;

	i = 0;
	buff_size = BUFF_SIZE;
	buff = (char*)ft_memalloc(sizeof(char) * buff_size);
	while (i < MAX_SIZE && (ret = read(fd, buff, 1) > 0))
	{
		printf("here |%s|\n", buff);
		if (i == (buff_size - 1))
		{
			buff_size *= 2;
			buff = ft_vrealloc(buff, buff_size);
		}
		i++;
	}
	printf("%p", buff);
	if (ret == -1)
	{
		ft_memdel((void**)buff);
		return (NULL);
	}
	printf("%s", buff);
	return (buff);
}
