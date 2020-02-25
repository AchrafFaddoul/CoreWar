/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frontend_analysis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 02:23:34 by ada               #+#    #+#             */
/*   Updated: 2020/02/26 00:45:58 by ada              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void dummy_del(void *content)
{
	ft_strdel((char**)(((t_instru*)content)->buff));
	ft_memdel((void**)(content));
}

t_env		*ft_fend_analys(t_env *env)
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
		printf("here\n");
		ft_dlstdel(&(env->lines), dummy_del);
		printf("here2\n");
		return (NULL);
	}
	return (env);
}
