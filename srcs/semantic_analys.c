/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semantic_analys.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaddoul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 12:29:21 by ada               #+#    #+#             */
/*   Updated: 2020/03/06 18:52:13 by afaddoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int 				ft_check_label(t_env *env, char *arg)
{
	t_element 		*tmp;
	int 			len;

	tmp = env->labels->head;
	len = ft_strlen(arg);
	while (tmp)
	{
		if (!(ft_strcmp(arg, ((t_label*)(tmp->content))->label)))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int 				ft_check_labels(t_env *env)
{
	t_element		*elm;

	elm = env->lines->head;
	printf("DAKHLA\n");
	while (elm)
	{
		printf("hahouwa\n");
		printf("ladrissa%p\n", SYM_TAB);
		if (SYM_TAB->arg_1)
		{
			printf("DAKHLA_1\n");
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
		}
		if (SYM_TAB->arg_2)
			printf("DAKHLA_2\n");
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

		}
		if (SYM_TAB->arg_3)
		{
			printf("DAKHLA_3\n");
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

		}
		elm = elm->next;
	}
	return (1);
}

int					ft_semantic_analysis(t_env *env)
{
	printf("dsjhg\n");
	if (!ft_check_labels(env))
		return (0);
	return (1);
}
