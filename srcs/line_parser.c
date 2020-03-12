/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaddoul <afaddoul@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 21:07:52 by afaddoul          #+#    #+#             */
/*   Updated: 2020/03/12 21:07:52 by afaddoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_instru		*ft_instru_new(char *line)
{
	t_instru	*elm;

	if (!(elm = (t_instru*)ft_memalloc(sizeof(t_instru))))
		return (NULL);
	elm->buff = line;
	return (elm);
}

char			*ft_get_line(t_env *env, int start, int end)
{
	t_instru	*instru;
	t_element	*elm;
	char		*buff;
	int			len;

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

t_env			*ft_line_parser(t_env *env)
{
	int			i;
	int			j;

	i = 0;
	j = 0;
	while (env->vect[i])
	{
		if (env->vect[i] == '\n')
		{
			if (!ft_get_line(env, j, i))
				return (NULL);
			j = i + 1;
		}
		i++;
	}
	if (env->vect[i - 1] != '\n')
		return (NULL);
	return (env);
}
