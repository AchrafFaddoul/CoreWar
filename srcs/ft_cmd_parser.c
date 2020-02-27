/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 16:04:23 by ada               #+#    #+#             */
/*   Updated: 2020/02/27 14:55:22 by ada              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static t_env	*destroy_cmd(t_env *env)
{
	printf("destroy_here_1\n");
	if (env->name)
		free((env->name));
		//ft_strdel((char**)(env->name));
	printf("destroy_here_2\n");
	printf("|%s|\n", env->comment);
	if (env->comment)
		free((env->comment));
		//ft_strdel((char**)(env->comment));
	printf("destroy_here_3\n");
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
	ft_bzero(buff, max_size);
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
		{
			i++;
			break ;
		}
		buff[j] = ptr[i];
		i++;
		j++;
	}
	while (ptr[i] && ((ptr[i] > 8 && ptr[i] < 14) || ptr[i] == 32))
		i++;
	if (ptr[i] == COMMENT_CHAR || ptr[i] == ALT_COMMENT_CHAR || !ptr[i])
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
	ft_bzero(buff, max_size);
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
		{
			i++;
			break ;
		}
		buff[j] = ptr[i];
		i++;
		j++;
	}
	printf("here_1\n");
	while (ptr[i] && ((ptr[i] > 8 && ptr[i] < 14) || ptr[i] == 32))
		i++;
	printf("here_2\n");
	if (ptr[i] == COMMENT_CHAR || ptr[i] == ALT_COMMENT_CHAR || !ptr[i])
		return (ft_cmd_dup(env, buff, max_size));
	printf("here_3\n");
	return (NULL);
}

t_env			*ft_get_cmd_dispatcher(t_env *env, const char *ptr)
{
	int 		i;
	int 		j;

	i = 0;
	j = 0;
	printf("inside_dispatcher_in\n");
	if (*(ptr + 1) == 'n')
	{
		printf("name exit\n");
		return (get_name(env, (ptr + 5), PROG_NAME_LENGTH));
	}
	else
	{
		printf("cmt exit\n");
		return (get_cmt(env, (ptr + 8), COMMENT_LENGTH));
	}
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
	printf("here_front\n");
	while (elm)
	{
		printf("first_loop_in\n");
		if (env->name && env->comment)
			return (env);
		printf("check1\n");
		ptr = ((t_instru*)(elm->content))->buff;
		if (*ptr == COMMENT_CHAR || *ptr == ALT_COMMENT_CHAR || *ptr == '\n')
			continue ;
		printf("check2\n");
		if (!ft_strncmp(ptr, NAME_CMD_STRING, 5) ||
				!ft_strncmp(ptr, COMMENT_CMD_STRING, 8))
		{
			printf("inside_1\n");
			if (!(ft_get_cmd_dispatcher(env, ptr)))
				return (destroy_cmd(env));
			printf("inside_2\n");
		}
		else
			return (destroy_cmd(env));
		printf("check3\n");
		elm = elm->next;
		printf("name->|%s|\n", env->name);
		printf("cmt->|%s|\n", env->comment);
		printf("first_loop_out\n");
	}
	printf("here_back");
	return (env);
}
