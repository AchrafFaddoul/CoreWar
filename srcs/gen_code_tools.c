/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_code_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaddoul <afaddoul@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 21:07:39 by afaddoul          #+#    #+#             */
/*   Updated: 2020/03/12 21:07:39 by afaddoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char						ft_get_op_code(t_symbol_tab *sym_tab)
{
	int						i;

	i = 0;
	while (i < 16)
	{
		if (!ft_strcmp(sym_tab->op, g_op_tab[i].op))
			break ;
		i++;
	}
	return (g_op_tab[i].op_index);
}

void						ft_generate_reg(t_symbol_tab *sym_tab, char *exec,
		int i, int index)
{
	if (index == 1)
		exec[i] = ((char*)(&sym_tab->val_1.val))[0];
	if (index == 2)
		exec[i] = ((char*)(&sym_tab->val_2.val))[0];
	if (index == 3)
		exec[i] = ((char*)(&sym_tab->val_3.val))[0];
}

int							ft_get_label_pc_dir(t_env *env, char *arg)
{
	t_element				*tmp;

	tmp = env->labels->head;
	while (tmp)
	{
		if (!(ft_strcmp(arg + 2, ((t_label*)(tmp->content))->label)))
			break ;
		tmp = tmp->next;
	}
	return ((((t_label*)(tmp->content))->pc));
}

int							ft_get_label_pc_indir(t_env *env, char *arg)
{
	t_element				*tmp;

	tmp = env->labels->head;
	while (tmp)
	{
		if (!(ft_strcmp(arg + 1, ((t_label*)(tmp->content))->label)))
			break ;
		tmp = tmp->next;
	}
	return ((((t_label*)(tmp->content))->pc));
}
