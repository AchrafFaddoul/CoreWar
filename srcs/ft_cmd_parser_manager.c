/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_parser_manager.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 14:50:01 by ada               #+#    #+#             */
/*   Updated: 2020/03/12 16:51:19 by ada              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"


int				ft_get_cmd(t_env *env, t_element *elm, char *ptr,
		int i)
{
	if (!ft_strncmp((ptr + i), NAME_CMD_STRING, 5) ||
			!ft_strncmp((ptr + i), COMMENT_CMD_STRING, 8))
	{
		if (!(elm = ft_get_cmd_dispatcher(env, (ptr + i), elm)))
			return (1);
	}
	else
		return (1);
	return (0);
}


//	if (!(ft_get_cmd(env, elm, ptr, i)))
//		return (NULL);

t_env				*ft_parsing_done(t_env *env, t_element *elm)
{
	if (env->name && env->comment)
	{
		env->lines->head = ft_dlstpop(&(env->lines), dummy_del, elm);
		return (env);
	}
	return (NULL);
}

t_env				*ft_cmd_parser(t_env *env)
{
	t_element		*elm;
	char			*ptr;
	int				i;

	elm = env->lines->head;
	while (elm)
	{
		i = 0;
		if (ft_parsing_done(env, elm))
			return (env);
		ptr = ((t_instru*)(elm->content))->buff;
		while (ptr[i] && (ptr[i] == 9 || ptr[i] == 32))
			i++;
		if (*(ptr + i) == COMMENT_CHAR ||
				*(ptr + i) == ALT_COMMENT_CHAR || *(ptr + i) == '\n')
		{
			elm = elm->next;
			continue ;
		}
	/*	if (!ft_strncmp((ptr + i), NAME_CMD_STRING, 5) ||
				!ft_strncmp((ptr + i), COMMENT_CMD_STRING, 8))
		{
			if (!(elm = ft_get_cmd_dispatcher(env, (ptr + i), elm)))
				return (destroy_cmd(env));
		}
		else
			return (destroy_cmd(env));*/
		
		if (ft_get_cmd(env, elm, ptr, i) == 1)
			return (destroy_cmd(env));
		elm = elm->next;
	}
	return (NULL);
}

