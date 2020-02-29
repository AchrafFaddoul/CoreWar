/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 02:14:19 by ada               #+#    #+#             */
/*   Updated: 2020/02/29 04:09:49 by ada              ###   ########.fr       */
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
	t_instru 	*instru;
	t_element 	*elm;
	char		*buff;
	int 		len;

	len = end - start + 1;
	if (!(buff = ft_strsub(env->vect, start, len)))
		return (NULL);
	if (!(instru = ft_instru_new(buff)))
	{
		ft_strdel((char**)&buff);
		return (NULL);
	}
	if (!(elm = ft_elemnew(instru)))
	{
		ft_strdel((char**)&buff);
		ft_memdel((void**)&instru);
		return (NULL);
	}
	ft_dlstpush(env->lines, elm);
	return (buff);
}

t_env		*ft_line_parser(t_env *env)
{
	int 	i;
	int		j;

	i = 0;
	j = 0;
	while (env->vect[i])
	{
		if (env->vect[i] == '\n')
		{
			if (!ft_get_line(env, j, i))
				return (NULL);
		//	printf("|%s|", ((t_instru*)(env->lines->tail->content))->buff);
			j = i + 1;
		}
		i++;
	}
	if (env->vect[i - 1] != '\n')
		return (NULL);
	return (env);
}
