/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vrealloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaddoul <afaddoul@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 09:41:11 by afaddoul          #+#    #+#             */
/*   Updated: 2020/01/12 19:00:51 by afaddoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

size_t		ft_vrealloc(char *buff, size_t buff_size)
{
	char 	*new_buff;
	size_t	coeff;

	coeff = 2;
	new_buff = (char*)ft_memalloc(sizeof(char) * buff_size * coeff);
	ft_strcpy(new_buff, buff);
	ft_memdel((void**)buff);
	buff = new_buff;
	return (buff_size * coeff);
}
