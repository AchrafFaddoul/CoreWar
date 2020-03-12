/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 16:04:23 by ada               #+#    #+#             */
/*   Updated: 2020/03/12 17:04:08 by ada              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_env				*destroy_cmd(t_env *env)
{
	if (env->name)
		ft_strdel((char**)&(env->name));
	if (env->comment)
		ft_strdel((char**)&(env->comment));
	return (NULL);
}

t_env				*ft_cmd_dup(t_env *env, char *buff, int flag)
{
	char			*cmd;

	if (!(cmd = ft_strdup(buff)))
		return (NULL);
	if (flag == PROG_NAME_LENGTH)
	{
		if (env->name)
			return (NULL);
		env->name = cmd;
	}
	else
	{
		if (env->comment)
			return (NULL);
		env->comment = cmd;
	}
	return (env);
}

t_element			*ft_get_next_node(t_element *elm, char *buff, int j,
		int size)
{
	char			*ptr;
	int				i;

	while (elm)
	{
		i = 0;
		ptr = ((t_instru*)(elm->content))->buff;
		while (ptr[i])
		{
			if (j > size)
				return (NULL);
			if (ptr[i] == '"' && ptr[i - 1] != '\\')
				return (elm);
			buff[j] = ptr[i];
			j++;
			i++;
		}
		elm = elm->next;
	}
	return (NULL);
}

t_element			*ft_get_cmd_dispatcher(t_env *env, const char *ptr,
		t_element *elm)
{
	if (*(ptr + 1) == 'n')
		return (get_name(env, (ptr + 5), PROG_NAME_LENGTH, elm));
	else
		return (get_cmt(env, (ptr + 8), COMMENT_LENGTH, elm));
}
