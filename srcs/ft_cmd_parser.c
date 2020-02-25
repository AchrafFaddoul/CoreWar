/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 16:04:23 by ada               #+#    #+#             */
/*   Updated: 2020/02/25 19:18:06 by ada              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "asm.h"

#include "../includes/libft.h"
#include <stdio.h>

static char 	*ignore_whitespace(char *ptr)
{
	char 		*str;
	int 		count;
	int 		len;
	int 		i;
	int 		j;

	i = 0;
	j = 0;
	count = 0;
	len = ft_strlen(ptr);
	printf("%d\n", len);
	while (ptr[i])
	{
		if ((ptr[i] > 8 && ptr[i] < 14) || ptr[i] == 32)
			count++;
		i++;
	}
	i = 0;
	if (!(str = (char*)ft_memalloc(sizeof(char) * ((len - count) + 1))))
		return (NULL);
	while (ptr[i])
	{
		if (ptr[i] == '"')
		{
			while (ptr[i])
			{
				printf("->%d\n", i);
				str[j++] = ptr[i];
				if (ptr[i] == '"')
					if (ptr[i] == '\\')
						i++ ;
				i++;
			}
		}
		if (((ptr[i] <= 8 || ptr[i] >= 14) && ptr[i] != 32))
			str[j++] = ptr[i];
		i++;
	}
	return (str);
}

int main()
{
	char *str = ft_strdup(".comment       \"Just a basic Winner Program\"");
	printf("%s\n", ignore_whitespaece(str));
}
/*
static int 		destroy_cmd(t_env *env)
{
	if (env->name)
		ft_strdel((char**)(env->name));
	if (env->comment)
		ft_strdel((char**)(env->comment));
}

int 			ft_get_cmd(t_env *env, const char *ptr)
{
	int 		i;
	int 		j;

	i = 0;
	if (*(ptr + 1) = 'n');
	i = 5;
	else
		i = 8;
	while (ptr[i] && ((str[i] > 8 && str[i] < 14) || str[i] == 32))
		i++;
	if (!ptr[i])
		return (0);
	if (ptr[i++] == '"')
	{
		while (ptr[i])
		{
			if (ptr[i] == '\\' && ptr[i + 1] == '"')
				i += 2;
			if (ptr[i] == '"')
				break ;
			i++;
		}
	}
	else
		return (0);
	return (1)
}

t_env 			*ft_cmd_parser(t_env *env)
{
	t_element	*elm;
	char 		*ptr;
	int 		i;
	int 		j;

	i = 0;
	j = 0;
	elm = env->lines->head;
	while (elm)
	{
		if (env->name && env->comment)
			return (env);
		ptr = ((t_instru*)(elm->content))->buff;
		if (*ptr == COMMENT_CHAR || *ptr == ALT_COMMENT_CHAR || *ptr == '\n')
			continue ;
		if (!ft_strcmp(ptr, NAME_CMD_STRING) ||
				!ft_strcmp(ptr, COMMENT_CMD_STRING))
		{
			if (!(ft_get_cmd(env, ptr)))
			{
				destroy_cmd(env);
				return (NULL);
			}
		}	
		else
		{
			destroy_cmd(env);
			return (NULL);
		}
		elm = elm->next;
	}
	return (env);
}
*/
