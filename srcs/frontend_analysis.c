/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frontend_analysis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 02:23:34 by ada               #+#    #+#             */
/*   Updated: 2020/03/07 17:13:13 by afaddoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		dummy_del(void *content)
{
	if ((((t_instru*)content)->buff))
		ft_strdel((char**)&(((t_instru*)content)->buff));
	if (content)
		ft_memdel((void**)&(content));
}

t_env		*ft_frontend_analys(t_env *env)
{
	if (!(env->lines = (t_dlist*)ft_memalloc(sizeof(t_dlist))))
		return (NULL);
	if (!(ft_line_parser(env)))
	{
		ft_dlstdel(&(env->lines), dummy_del);
		return (NULL);
	}
	printf("here_1\n");
	if (!(ft_cmd_parser(env)))
	{
		ft_dlstdel(&(env->lines), dummy_del);
		return (NULL);
	}
	printf("here_2\n");
	if (!(env->labels = (t_dlist*)ft_memalloc(sizeof(t_dlist))))
	{
		ft_dlstdel(&(env->lines), dummy_del);
		return (NULL);
	}
	printf("here_3\n");
	if (!(ft_instruparser(env)))
	{
		return (NULL);
	}
	printf("here_4\n");
	if (!(ft_semantic_analysis(env)))
	{
		return (NULL);
	}
	printf("here_5\n");
	return (env);
}
