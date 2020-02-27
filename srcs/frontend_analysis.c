/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frontend_analysis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 02:23:34 by ada               #+#    #+#             */
/*   Updated: 2020/02/27 15:09:07 by ada              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void dummy_del(void *content)
{
	printf("yooooo_1|%p|\n", (((t_instru*)content)->buff));
	if ((((t_instru*)content)->buff))
		ft_strdel((char**)(((t_instru*)content)->buff));
	printf("yooooo_2\n");
	ft_memdel((void**)(content));
	printf("yooooo_3\n");
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
	if (!(ft_cmd_parser(env)))
	{
		printf("lblaaan\n");
		ft_dlstdel(&(env->lines), dummy_del);
		printf("waw waw\n");
		return (NULL);
	}
	return (env);
}
