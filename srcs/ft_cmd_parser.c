/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 16:04:23 by ada               #+#    #+#             */
/*   Updated: 2020/02/26 00:46:02 by ada              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static t_env	*destroy_cmd(t_env *env)
{
	printf("yohihihihi\n");
	printf("yo||%p||\n", env);
	printf("yo||%p||\n", env->name);
	printf("yo||%p||\n", env->comment);
	if (env->name)
		ft_strdel((char**)(env->name));
	if (env->comment)
		ft_strdel((char**)(env->comment));
	printf("yohihihihi\n");
	return (NULL);
}

static t_env	*ft_cmd_dup(t_env *env, char *buff, int flag)
{
	char 		*cmd;

	if (!(cmd = ft_strdup(buff)))
		return (NULL);
	if (flag == PROG_NAME_LENGTH)
		env->name = cmd;
	else
		env->comment = cmd;
	return (env);
}

t_env			*get_name(t_env *env, const char *ptr, int max_size)
{
	char 		buff[max_size];
	int 		i;
	int 		j;

	i = 0;
	j = 0;
	while (ptr[i] && ((ptr[i] > 8 && ptr[i] < 14) || ptr[i] == 32))
		i++;
	if (!ptr[i])
		return (NULL);
	if (ptr[i++] != '"')
		return (0);
	while (ptr[i])
	{
		if (j == max_size)
			return (0);
		if (ptr[i] == '"' && ptr[i - 1] != '\\')
			break ;
		buff[j] = buff[i];
		i++;
		j++;
	}
	while (ptr[i] && ((ptr[i] > 8 && ptr[i] < 14) || ptr[i] == 32))
		i++;
	if (!ptr[i])
		return (NULL);
	else if (ptr[i] == COMMENT_CHAR ||
			ptr[i] == ALT_COMMENT_CHAR || ptr[i] == '\n')
		return (ft_cmd_dup(env, buff, max_size));
	return (NULL);
}

t_env			*get_cmt(t_env *env, const char *ptr, int max_size)
{
	char 		buff[max_size];
	int 		i;
	int 		j;

	i = 0;
	j = 0;
	while (ptr[i] && ((ptr[i] > 8 && ptr[i] < 14) || ptr[i] == 32))
		i++;
	if (!ptr[i])
		return (NULL);
	if (ptr[i++] != '"')
		return (0);
	while (ptr[i])
	{
		if (j == max_size)
			return (0);
		if (ptr[i] == '"' && ptr[i - 1] != '\\')
			break ;
		buff[j] = buff[i];
		i++;
		j++;
	}
	while (ptr[i] && ((ptr[i] > 8 && ptr[i] < 14) || ptr[i] == 32))
		i++;
	if (!ptr[i])
		return (NULL);
	else if (ptr[i] == COMMENT_CHAR ||
			ptr[i] == ALT_COMMENT_CHAR || ptr[i] == '\n')
		return (ft_cmd_dup(env, buff, max_size));
	return (NULL);
}

t_env			*ft_get_cmd_dispatcher(t_env *env, const char *ptr)
{
	int 		i;
	int 		j;

	i = 0;
	j = 0;
	printf("yohoooooo4");
	if (*(ptr + 1) == 'n')
		return (get_name(env, (ptr + 5), PROG_NAME_LENGTH));
	else
		return (get_cmt(env, (ptr + 8), COMMENT_LENGTH));
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
		printf("yohoooooo1|%s|\n",((char*)(((t_instru*)(elm->content))->buff)));
		if (env->name && env->comment)
			return (env);
		ptr = ((t_instru*)(elm->content))->buff;
		printf("yohoooooo2\n");
		if (*ptr == COMMENT_CHAR || *ptr == ALT_COMMENT_CHAR || *ptr == '\n')
			continue ;
		printf("yohoooooo3\n");
		if (!ft_strcmp(ptr, NAME_CMD_STRING) ||
				!ft_strcmp(ptr, COMMENT_CMD_STRING))
		{
			if (!(ft_get_cmd_dispatcher(env, ptr)))
				return (destroy_cmd(env));
		}	
		else
			return (destroy_cmd(env));
		printf("yohoooooo4\n");
		elm = elm->next;
	}
	return (env);
}
