/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frontend_analysis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 02:23:34 by ada               #+#    #+#             */
/*   Updated: 2020/03/02 11:24:52 by ada              ###   ########.fr       */
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
	printf("HELLO FROM front end anal\n");
	if (!(env->lines = (t_dlist*)ft_memalloc(sizeof(t_dlist))))
		return (NULL);
	if (!(ft_line_parser(env)))
	{
		ft_dlstdel(&(env->lines), dummy_del);
		return (NULL);
	}
	printf("HELLO FROM front end anal LINES PARSED\n");
	if (!(ft_cmd_parser(env)))
	{
		ft_dlstdel(&(env->lines), dummy_del);
		return (NULL);
	}
	printf("HELLO FROM front end anal CMD PARSED\n");
	if (!(env->labels = (t_dlist*)ft_memalloc(sizeof(t_dlist))))
	{
		ft_dlstdel(&(env->lines), dummy_del);
		return (NULL);
	}
	printf("HELLO FROM front end anal LABEL CREATED\n");
	if (!(ft_instruparser(env)))
	{
		return (NULL);
	}
	printf("HELLO FROM front end anal INSTRU PARSED\n");
	return (env);
}
