/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pc_counter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 00:07:20 by ada               #+#    #+#             */
/*   Updated: 2020/03/12 00:20:28 by ada              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void				ft_arg1_pc_counter(t_symbol_tab *sym_tab, int *pc, int i)
{
	if (sym_tab->val_1.nat == T_REG)
		(*pc)++;
	else if (sym_tab->val_1.nat == T_IND)
		*pc += 2;
	else if (sym_tab->val_1.nat == T_DIR)
	{
		if (!g_op_tab[i].dir_size)
			*pc += 4;
		else
			*pc += 2;
	}
}

void				ft_arg2_pc_counter(t_symbol_tab *sym_tab, int *pc, int i)
{
	if (sym_tab->val_1.nat == T_REG)
		(*pc)++;
	else if (sym_tab->val_1.nat == T_IND)
		*pc += 2;
	else if (sym_tab->val_1.nat == T_DIR)
	{
		if (!g_op_tab[i].dir_size)
			*pc += 4;
		else
			*pc += 2;
	}
}

void				ft_arg3_pc_counter(t_symbol_tab *sym_tab, int *pc, int i)
{
	if (sym_tab->val_1.nat == T_REG)
		(*pc)++;
	else if (sym_tab->val_1.nat == T_IND)
		*pc += 2;
	else if (sym_tab->val_1.nat == T_DIR)
	{
		if (!g_op_tab[i].dir_size)
			*pc += 4;
		else
			*pc += 2;
	}
}

int					ft_pc_counter(t_symbol_tab *sym_tab)
{
	int				pc;
	int				index;

	pc = 1;
	index = ft_get_op_index(sym_tab->op);
	if (g_op_tab[index].arg_tcode)
		pc++;
	if (sym_tab->arg_1)
		ft_arg1_pc_counter(sym_tab, &pc, index);
	if (sym_tab->arg_2)
		ft_arg2_pc_counter(sym_tab, &pc, index);
	if (sym_tab->arg_3)
		ft_arg3_pc_counter(sym_tab, &pc, index);
	return (pc);
}
