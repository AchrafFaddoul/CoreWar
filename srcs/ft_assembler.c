/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_assembler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 02:20:22 by ada               #+#    #+#             */
/*   Updated: 2020/02/27 19:12:43 by ada              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void 		ft_assembler(t_env *env)
{
	if (!ft_frontend_analys(env))
		{
			ft_strdel((char**)&(env->vect));
			ft_memdel((void**)&env);
			ft_error();
		}
	printf("\n\n\n\n\n\n\nn\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nn\n");
	while (env->lines->head)
	{
		printf("|%s|", ((t_instru*)(env->lines->head->content))->buff);
		env->lines->head = env->lines->head->next;
	}
	//	ft_bend_analys(env);
}
