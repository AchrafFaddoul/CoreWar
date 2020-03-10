/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   code_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 21:53:42 by ada               #+#    #+#             */
/*   Updated: 2020/03/10 18:04:01 by ada              ###   ########.fr       */
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

char 				*ft_first_ws_del(char *ptr)
{
	char 			*dest;
	int 			i;

	i = 0;
	while (ptr[i] && (ptr[i] == 9 || ptr[i] == 32))
		i++;
	if (!(dest = (char*)ft_memalloc(sizeof(char) * (ft_strlen(ptr + i) + 1))))
		return (NULL);
	ft_strcpy(dest, ptr + i);
	return (dest);
}

t_env				*ft_instruparser(t_env *env)
{
	t_element		*elm;
	char 			*ptr;
	t_symbol_tab	*s_tab;

	elm = env->lines->head;
	while (elm)
	{
		if (!(ptr = ft_first_ws_del(((t_instru*)(elm->content))->buff)))
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
		elm = elm->next;
	}
	return (env);
}
