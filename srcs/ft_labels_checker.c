/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_labels_checker.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaddoul <afaddoul@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 21:07:37 by afaddoul          #+#    #+#             */
/*   Updated: 2020/03/12 21:07:37 by afaddoul         ###   ########.fr       */
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

int					check_arg1(t_env *env, t_element *elm)
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

int					check_arg2(t_env *env, t_element *elm)
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

int					check_arg3(t_env *env, t_element *elm)
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
