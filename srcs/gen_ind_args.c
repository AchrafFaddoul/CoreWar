/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_ind_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaddoul <afaddoul@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 21:07:50 by afaddoul          #+#    #+#             */
/*   Updated: 2020/03/12 21:07:50 by afaddoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void						ft_gen_ind_arg1(t_symbol_tab *sym_tab, t_env *env,
		int i, int *pc)
{
	if (sym_tab->arg_1[0] == LABEL_CHAR)
	{
		*pc = ft_get_label_pc_indir(env, sym_tab->arg_1);
		sym_tab->val_1.val = *pc - sym_tab->pc;
	}
	env->exec[i] = ((char*)(&sym_tab->val_1.val))[1];
	env->exec[i + 1] = ((char*)(&sym_tab->val_1.val))[0];
}

void						ft_gen_ind_arg2(t_symbol_tab *sym_tab, t_env *env,
		int i, int *pc)
{
	if (sym_tab->arg_2[0] == LABEL_CHAR)
	{
		*pc = ft_get_label_pc_indir(env, (sym_tab->arg_2));
		sym_tab->val_2.val = *pc - sym_tab->pc;
	}
	env->exec[i] = ((char*)(&sym_tab->val_2.val))[1];
	env->exec[i + 1] = ((char*)(&sym_tab->val_2.val))[0];
}

void						ft_gen_ind_arg3(t_symbol_tab *sym_tab, t_env *env,
		int i, int *pc)
{
	if (sym_tab->arg_3[0] == LABEL_CHAR)
	{
		*pc = ft_get_label_pc_indir(env, sym_tab->arg_3);
		sym_tab->val_3.val = *pc - sym_tab->pc;
	}
	env->exec[i] = ((char*)(&sym_tab->val_3.val))[1];
	env->exec[i + 1] = ((char*)(&sym_tab->val_3.val))[0];
}
