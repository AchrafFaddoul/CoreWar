/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   code_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 21:53:42 by ada               #+#    #+#             */
/*   Updated: 2020/03/05 15:20:03 by ada              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"


t_env				*ft_scanner(t_env *env, t_element *elm, char *ptr)
{
	if (!(ft_syntax_analys(env, elm, ptr)))
	{
		return (NULL);
	}
	return (env);
}

t_env				*ft_instruparser(t_env *env)
{
	t_element		*elm;
	char 			*ptr;
	t_symbol_tab	*s_tab;

	elm = env->lines->head;
	while (elm)
	{
		if (!(ptr = ft_wsdel(((t_instru*)(elm->content))->buff)))
			return (NULL);
		if (*ptr == COMMENT_CHAR ||
				*ptr == ALT_COMMENT_CHAR || *ptr == '\n')
		{
			elm = elm->next;
			continue ;
		}
		if (!(s_tab = (t_symbol_tab*)ft_memalloc(sizeof(t_symbol_tab))))
			return (NULL);
		((t_instru*)(elm->content))->sym_tab = s_tab;
		if (!(ft_scanner(env, elm, ptr)))
		{
			ft_strdel((char**)&ptr);
			return (NULL);
		}
		printf("************************************\n");
			printf("lbl:%s\nop:%s\narg1:%s\narg2:%s\narg3:%s\n",
			((t_symbol_tab*)((t_instru*)(elm->content))->sym_tab)->label,
			((t_symbol_tab*)((t_instru*)(elm->content))->sym_tab)->op,
			((t_symbol_tab*)((t_instru*)(elm->content))->sym_tab)->arg_1,
			((t_symbol_tab*)((t_instru*)(elm->content))->sym_tab)->arg_2,
			((t_symbol_tab*)((t_instru*)(elm->content))->sym_tab)->arg_3);
	printf("op_flg:%d\n", ((t_instru*)(elm->content))->op_flg);
	printf("lbl_flg:%d\n", ((t_instru*)(elm->content))->lbl_flg);
		elm = elm->next;
	}	
	elm = env->labels->head;
	while (elm)
   {
   		printf("%s\n", ((t_label*)(elm->content))->label);
		printf("%d\n", ((t_label*)(elm->content))->pc);
   		elm = elm->next;
   }
	return (env);
}

/*
	printf("************************************\n");
	printf("lbl:%s\nop:%s\narg1:%s\narg2:%s\narg3:%s\n",
			((t_symbol_tab*)((t_instru*)(elm->content))->sym_tab)->label,
			((t_symbol_tab*)((t_instru*)(elm->content))->sym_tab)->op,
			((t_symbol_tab*)((t_instru*)(elm->content))->sym_tab)->arg_1,
			((t_symbol_tab*)((t_instru*)(elm->content))->sym_tab)->arg_2,
			((t_symbol_tab*)((t_instru*)(elm->content))->sym_tab)->arg_3);
	printf("op_flg:%d\n", ((t_instru*)(elm->content))->op_flg);
	printf("lbl_flg:%d\n", ((t_instru*)(elm->content))->lbl_flg);
	elm = env->labels->head;
	while (elm)
   {
   		printf("%s\n", ((t_label*)(elm->content))->label);
		printf("%d\n", ((t_label*)(elm->content))->pc);
   		elm = elm->next;
   }
   */
