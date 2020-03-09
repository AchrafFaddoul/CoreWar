/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_assembler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 02:20:22 by ada               #+#    #+#             */
/*   Updated: 2020/03/09 17:10:28 by ada              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void 		ft_assembler(t_env *env)
{
	printf("IN FRONT END\n");
	if (!ft_frontend_analys(env))
		{
			ft_strdel((char**)&(env->vect));
			ft_memdel((void**)&env);
			ft_error();
		}
	printf("OUT FRONT END\n");
	printf("IN BACK END\n");
		if(!(ft_backend_analys(env)))
		{
			ft_error();
		}
		printf("OUT BACKEND END\n");
}
