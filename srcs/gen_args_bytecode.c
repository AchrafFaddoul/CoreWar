/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_args_bytecode.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaddoul <afaddoul@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 21:07:38 by afaddoul          #+#    #+#             */
/*   Updated: 2020/03/12 21:07:38 by afaddoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void						ft_gen_arg1_bytecode(t_symbol_tab *sym_tab,
		t_env *env, int *i, int index)
{
	if (sym_tab->val_1.nat == T_REG)
	{
		ft_generate_reg(sym_tab, env->exec, *i, 1);
		(*i)++;
	}
	if (sym_tab->val_1.nat == T_IND)
	{
		ft_generate_indir(sym_tab, env, *i, 1);
		*i += 2;
	}
	if (sym_tab->val_1.nat == T_DIR)
	{
		if (g_op_tab[index].dir_size)
		{
			ft_generate_dir_short(sym_tab, env, *i, 1);
			*i += 2;
		}
		if (!g_op_tab[index].dir_size)
		{
			ft_generate_dir_long(sym_tab, env, *i, 1);
			*i += 4;
		}
	}
}

void						ft_gen_arg2_bytecode(t_symbol_tab *sym_tab,
		t_env *env, int *i, int index)
{
	if (sym_tab->val_2.nat == T_REG)
	{
		ft_generate_reg(sym_tab, env->exec, *i, 2);
		(*i)++;
	}
	if (sym_tab->val_2.nat == T_IND)
	{
		ft_generate_indir(sym_tab, env, *i, 2);
		*i += 2;
	}
	if (sym_tab->val_2.nat == T_DIR)
	{
		if (g_op_tab[index].dir_size)
		{
			ft_generate_dir_short(sym_tab, env, *i, 2);
			*i += 2;
		}
		if (!g_op_tab[index].dir_size)
		{
			ft_generate_dir_long(sym_tab, env, *i, 2);
			*i += 4;
		}
	}
}

void						ft_gen_arg3_bytecode(t_symbol_tab *sym_tab,
		t_env *env, int *i, int index)
{
	if (sym_tab->val_3.nat == T_REG)
	{
		ft_generate_reg(sym_tab, env->exec, *i, 3);
		(*i)++;
	}
	if (sym_tab->val_3.nat == T_IND)
	{
		ft_generate_indir(sym_tab, env, *i, 3);
		*i += 2;
	}
	if (sym_tab->val_3.nat == T_DIR)
	{
		if (g_op_tab[index].dir_size)
		{
			ft_generate_dir_short(sym_tab, env, *i, 3);
			*i += 2;
		}
		if (!g_op_tab[index].dir_size)
		{
			ft_generate_dir_long(sym_tab, env, *i, 3);
			*i += 4;
		}
	}
}
