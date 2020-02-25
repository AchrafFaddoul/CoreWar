/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 02:32:02 by ada               #+#    #+#             */
/*   Updated: 2020/02/25 03:37:30 by ada              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_instru		*ft_instru_new(char *line)
{
	t_instru 	*elm;

	if (!(elm = (t_instru*)ft_memalloc(sizeof(t_instru))))
		return (NULL);
	elm->buff = line;
	return (elm);
}

char 			*ft_get_line(t_env *env, int start, int end)
{
	static int	index;
	t_instru 	*elm;
	char		*buff;
	int 		len;

	len = end - start + 1;
	if (!(buff = ft_strsub(env->vect, start, len)))
			return (NULL);
	if (!(elm = ft_instru_new(buff)))
	{
		ft_strdel((char**)buff);
		return (NULL);
	}
	elm->index = index++;
	ft_dlstpush(env->lines, ft_elemnew(elm));
	return (buff);
}
