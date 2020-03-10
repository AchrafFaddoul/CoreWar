/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_assembler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 02:20:22 by ada               #+#    #+#             */
/*   Updated: 2020/03/10 18:03:51 by ada              ###   ########.fr       */
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
	if(!(ft_backend_analys(env)))
	{
		ft_error();
	}
}
