/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frontend_analysis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 02:23:34 by ada               #+#    #+#             */
/*   Updated: 2020/02/29 15:17:02 by ada              ###   ########.fr       */
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
	if (!(ft_cmd_parser(env)))
	{
		ft_dlstdel(&(env->lines), dummy_del);
		return (NULL);
	}
	printf("bef label parsing\n");
	if (!(env->labels = (t_dlist*)ft_memalloc(sizeof(t_dlist))))
		return (NULL);
	if(!(ft_label_parser(env)))
	{
		ft_dlstdel(&(env->lines), dummy_del);
		ft_dlstdel(&(env->labels), dummy_del);
		return (NULL);
	}
	printf("yoo guys\n");
	while (env->labels->head)
	{
		printf("%s\n", ((t_label*)(env->labels->head))->label);
		env->labels->head = env->labels->head->next;
	}
	return (env);
}
