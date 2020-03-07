/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backend_analysis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaddoul <afaddoul@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 13:58:58 by afaddoul          #+#    #+#             */
/*   Updated: 2020/03/07 18:19:16 by afaddoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void 				ft_set_label_pc(t_env *env, char *label)
{
	t_element 		*tmp;

	tmp = env->labels->head;
	while (tmp)
	{
		if (!(ft_strcmp(label, ((t_label*)(tmp->content))->label)))
		{
			((t_label*)(tmp->content))->pc = env->pc;
			return ;
		}
		tmp = tmp->next;
	}
}

int 				ft_pc_counter(t_symbol_tab* sym_tab)
{
	int 			pc;
	int 			index;

	pc = 1;
	index = ft_get_op_index(sym_tab->op);
	if (g_op_tab[index].arg_tcode)
		pc++;
	if (sym_tab->arg_1)
	{
		if (sym_tab->val_1.nat == T_REG)
			pc++;
		else if (sym_tab->val_1.nat == T_IND)
			pc += 2;
		else if (sym_tab->val_1.nat == T_DIR)
		{
			if (!g_op_tab[index].dir_size)
				pc += 4;
			else
				pc += 2;
		}
	}
	if (sym_tab->arg_2)
	{
		if (sym_tab->val_2.nat == T_REG)
			pc++;
		else if (sym_tab->val_2.nat == T_IND)
			pc += 2;
		else if (sym_tab->val_2.nat == T_DIR)
		{
			if (!g_op_tab[index].dir_size)
				pc += 4;
			else
				pc += 2;
		}
	}
	if (sym_tab->arg_3)
	{
		if (sym_tab->val_3.nat == T_REG)
			pc++;
		else if (sym_tab->val_3.nat == T_IND)
			pc += 2;
		else if (sym_tab->val_3.nat == T_DIR)
		{
			if (!g_op_tab[index].dir_size)
				pc += 4;
			else
				pc += 2;
		}
	}
	return (sym_tab->pc = pc);
}

void 				ft_exec_size_counter(t_env *env)
{
	t_element 		*elm;
	int 			instru_pc;

	elm = env->lines->head;
	while (elm)
	{
		if (((t_instru*)(elm->content))->op_flg ||
				((t_instru*)(elm->content))->lbl_flg)
		{
			if (((t_instru*)(elm->content))->lbl_flg)
				ft_set_label_pc(env, SYM_TAB->label);
			if (((t_instru*)(elm->content))->op_flg)
			{
				SYM_TAB->pc = env->pc;
				instru_pc = ft_pc_counter(SYM_TAB);
				env->pc += instru_pc;
			}
		}
		elm = elm->next;
	}
}

t_env				*ft_backend_analys(t_env *env)
{
	int  			fd;

	ft_exec_size_counter(env);
	if ((fd = open(env->file_name, O_CREAT | O_WRONLY)) == -1)
		return (NULL);

	return (env);
}
