/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champ_exe_code.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaddoul <afaddoul@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 21:06:01 by afaddoul          #+#    #+#             */
/*   Updated: 2020/03/12 21:06:01 by afaddoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

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
