/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semantic_analys.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaddoul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 12:29:21 by ada               #+#    #+#             */
/*   Updated: 2020/03/12 02:14:31 by ada              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int					ft_check_label(t_env *env, char *arg)
{
	t_element		*tmp;

	tmp = env->labels->head;
	while (tmp)
	{
		if (!(ft_strcmp(arg, ((t_label*)(tmp->content))->label)))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int 				check_arg1(t_env *env, t_element *elm)
{	
	if (SYM_TAB->val_1.nat == T_DIR)
	{
		if (*(SYM_TAB->arg_1 + 1) == LABEL_CHAR)
			if (!(ft_check_label(env, (SYM_TAB->arg_1 + 2))))
				return (0);
	}
	else if (SYM_TAB->val_1.nat == T_IND)
	{
		if (*(SYM_TAB->arg_1) == LABEL_CHAR)
			if (!(ft_check_label(env, (SYM_TAB->arg_1 + 1))))
				return (0);
	}
	return (1);
}

int 				check_arg2(t_env *env, t_element *elm)
{	
	if (SYM_TAB->val_2.nat == T_DIR)
	{
		if (*(SYM_TAB->arg_2 + 1) == LABEL_CHAR)
			if (!(ft_check_label(env, (SYM_TAB->arg_2 + 2))))
				return (0);
	}
	else if (SYM_TAB->val_2.nat == T_IND)
	{
		if (*(SYM_TAB->arg_2) == LABEL_CHAR)
			if (!(ft_check_label(env, (SYM_TAB->arg_2 + 1))))
				return (0);
	}
	return (1);
}

int 				check_arg3(t_env *env, t_element *elm)
{	
	if (SYM_TAB->val_3.nat == T_DIR)
	{
		if (*(SYM_TAB->arg_3 + 1) == LABEL_CHAR)
			if (!(ft_check_label(env, (SYM_TAB->arg_3 + 2))))
				return (0);
	}
	else if (SYM_TAB->val_3.nat == T_IND)
	{
		if (*(SYM_TAB->arg_3) == LABEL_CHAR)
			if (!(ft_check_label(env, (SYM_TAB->arg_3 + 1))))
				return (0);
	}
	return (1);

}

int					ft_check_labels(t_env *env)
{
	t_element		*elm;

	elm = env->lines->head;
	while (elm)
	{
		if (((t_instru*)(elm->content))->op_flg)
		{
			if (SYM_TAB->arg_1)
				if (!check_arg1(env, elm))
					return (0);
			if (SYM_TAB->arg_2)
				if (!check_arg1(env, elm))
					return (0);
			if (SYM_TAB->arg_3)
				if (!check_arg1(env, elm))
					return (0);
		}
		elm = elm->next;
	}
	return (1);
}

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
