/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champ_exe_code.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaddoul <afaddoul@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 00:32:16 by afaddoul          #+#    #+#             */
/*   Updated: 2020/03/11 23:35:05 by ada              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
/*
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
*/
void						ft_generate_indir(t_symbol_tab *sym_tab,
		t_env *env, int i, int index)
{
	int						pc;

	if (index == 1)
		ft_gen_ind_arg1(sym_tab, env, i, &pc);
	if (index == 2)
		ft_gen_ind_arg2(sym_tab, env, i, &pc);
	if (index == 3)
		ft_gen_ind_arg3(sym_tab, env, i, &pc);
}

void						ft_gen_sdir_arg1(t_symbol_tab *sym_tab, t_env *env,
		int i, int *pc)
{
	if (sym_tab->arg_1[1] == LABEL_CHAR)
	{
		*pc = ft_get_label_pc_dir(env, sym_tab->arg_1);
		sym_tab->val_1.val = *pc - sym_tab->pc;
	}
	env->exec[i] = ((char*)(&sym_tab->val_1.val))[1];
	env->exec[i + 1] = ((char*)(&sym_tab->val_1.val))[0];
}

void						ft_gen_sdir_arg2(t_symbol_tab *sym_tab, t_env *env,
		int i, int *pc)
{
	if (sym_tab->arg_2[1] == LABEL_CHAR)
	{
		*pc = ft_get_label_pc_dir(env, sym_tab->arg_2);
		sym_tab->val_2.val = *pc - sym_tab->pc;
	}
	env->exec[i] = ((char*)(&sym_tab->val_2.val))[1];
	env->exec[i + 1] = ((char*)(&sym_tab->val_2.val))[0];
}

void						ft_gen_sdir_arg3(t_symbol_tab *sym_tab, t_env *env,
		int i, int *pc)
{
	if (sym_tab->arg_3[1] == LABEL_CHAR)
	{
		*pc = ft_get_label_pc_dir(env, sym_tab->arg_3);
		sym_tab->val_3.val = *pc - sym_tab->pc;
	}
	env->exec[i] = ((char*)(&sym_tab->val_3.val))[1];
	env->exec[i + 1] = ((char*)(&sym_tab->val_3.val))[0];
}

void						ft_generate_dir_short(t_symbol_tab *sym_tab,
		t_env *env, int i, int index)
{
	int						pc;

	if (index == 1)
		ft_gen_sdir_arg1(sym_tab, env, i, &pc);
	if (index == 2)
		ft_gen_sdir_arg2(sym_tab, env, i, &pc);
	if (index == 3)
		ft_gen_sdir_arg3(sym_tab, env, i, &pc);
}

void						ft_gen_ldir_arg1(t_symbol_tab *sym_tab, t_env *env,
		int i, int *pc)
{
	if (sym_tab->arg_1[1] == LABEL_CHAR)
	{
		*pc = ft_get_label_pc_dir(env, sym_tab->arg_1);
		sym_tab->val_1.val = *pc - sym_tab->pc;
	}
	env->exec[i] = ((char*)(&sym_tab->val_1.val))[3];
	env->exec[i + 1] = ((char*)(&sym_tab->val_1.val))[2];
	env->exec[i + 2] = ((char*)(&sym_tab->val_1.val))[1];
	env->exec[i + 3] = ((char*)(&sym_tab->val_1.val))[0];
}

void						ft_gen_ldir_arg2(t_symbol_tab *sym_tab, t_env *env,
		int i, int *pc)
{
	if (sym_tab->arg_2[1] == LABEL_CHAR)
	{
		*pc = ft_get_label_pc_dir(env, sym_tab->arg_2);
		sym_tab->val_2.val = *pc - sym_tab->pc;
	}
	env->exec[i] = ((char*)(&sym_tab->val_2.val))[3];
	env->exec[i + 1] = ((char*)(&sym_tab->val_2.val))[2];
	env->exec[i + 2] = ((char*)(&sym_tab->val_2.val))[1];
	env->exec[i + 3] = ((char*)(&sym_tab->val_2.val))[0];
}

void						ft_gen_ldir_arg3(t_symbol_tab *sym_tab, t_env *env,
		int i, int *pc)
{
	if (sym_tab->arg_3[1] == LABEL_CHAR)
	{
		*pc = ft_get_label_pc_dir(env, sym_tab->arg_3);
		sym_tab->val_3.val = *pc - sym_tab->pc;
	}
	env->exec[i] = ((char*)(&sym_tab->val_3.val))[3];
	env->exec[i + 1] = ((char*)(&sym_tab->val_3.val))[2];
	env->exec[i + 2] = ((char*)(&sym_tab->val_3.val))[1];
	env->exec[i + 3] = ((char*)(&sym_tab->val_3.val))[0];
}

void						ft_generate_dir_long(t_symbol_tab *sym_tab,
		t_env *env, int i, int index)
{
	int						pc;

	if (index == 1)
		ft_gen_ldir_arg1(sym_tab, env, i, &pc);
	if (index == 2)
		ft_gen_ldir_arg2(sym_tab, env, i, &pc);
	if (index == 3)
		ft_gen_ldir_arg3(sym_tab, env, i, &pc);
}

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

int							ft_generate_instruction(t_symbol_tab *sym_tab,
		t_env *env, int i)
{
	int						index;

	env->exec[i] = ft_get_op_code(sym_tab);
	i++;
	index = ft_get_op_index(sym_tab->op);
	if (g_op_tab[index].arg_tcode)
	{
		ft_get_tcode(sym_tab, env->exec, i);
		i++;
	}
	ft_gen_arg1_bytecode(sym_tab, env, &i, index);
	ft_gen_arg2_bytecode(sym_tab, env, &i, index);
	ft_gen_arg3_bytecode(sym_tab, env, &i, index);
	return (i);
}

int							ft_champ_exe_code(t_env *env, int i)
{
	t_element				*elm;

	elm = env->lines->head;
	while (elm)
	{
		if (((t_instru*)(elm->content))->op_flg)
			i = ft_generate_instruction(SYM_TAB, env, i);
		elm = elm->next;
	}
	return (i);
}
