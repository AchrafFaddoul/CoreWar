/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semantic_analys.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaddoul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 12:29:21 by ada               #+#    #+#             */
/*   Updated: 2020/03/12 02:20:29 by ada              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int					ft_get_op_index(char *op)
{
	int				i;

	i = 0;
	while (i < 16)
	{
		if (!ft_strcmp(op, g_op_tab[i].op))
			break ;
		i++;
	}
	return (i);
}

int					ft_check_arg_nb(t_element *elm, int arg_nb)
{
	if (arg_nb == 1)
	{
		if (!(SYM_TAB->arg_1 && !SYM_TAB->arg_2 && !SYM_TAB->arg_3))
			return (0);
	}
	else if (arg_nb == 2)
	{
		if (!(SYM_TAB->arg_1 && SYM_TAB->arg_2 && !SYM_TAB->arg_3))
			return (0);
	}
	else if (arg_nb == 3)
	{
		if (!(SYM_TAB->arg_1 && SYM_TAB->arg_2 && SYM_TAB->arg_3))
			return (0);
	}
	return (1);
}

int					ft_check_args_type(t_element *elm, int arg_nb, int index)
{
	int				i;

	i = arg_nb;
	if (!(SYM_TAB->val_1.nat & g_op_tab[index].arg[0]))
		return (0);
	i--;
	if (!i)
		return (1);
	if (!(SYM_TAB->val_2.nat & g_op_tab[index].arg[1]))
		return (0);
	i--;
	if (!i)
		return (1);
	if (!(SYM_TAB->val_3.nat & g_op_tab[index].arg[2]))
		return (0);
	i--;
	if (!i)
		return (1);
	return (1);
}

int					ft_args_checker(t_env *env)
{
	t_element		*elm;
	int				index;
	int				arg_nb;

	elm = env->lines->head;
	while (elm)
	{
		if (((t_instru*)(elm->content))->op_flg)
		{
			index = ft_get_op_index(SYM_TAB->op);
			arg_nb = g_op_tab[index].arg_nb;
			if (!(ft_check_arg_nb(elm, arg_nb)))
				return (0);
			if (!(ft_check_args_type(elm, arg_nb, index)))
				return (0);
		}
		elm = elm->next;
	}
	return (1);
}

int					ft_semantic_analysis(t_env *env)
{
	if (!ft_check_labels(env))
		return (0);
	if (!(ft_args_checker(env)))
		return (0);
	return (1);
}
