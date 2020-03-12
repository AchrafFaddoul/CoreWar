/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_backend_analysis.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaddoul <afaddoul@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 21:08:46 by afaddoul          #+#    #+#             */
/*   Updated: 2020/03/12 22:15:19 by afaddoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void					swap_bytes(void *src, void *dst, int size)
{
	int					i;
	int					j;

	i = 0;
	j = size - 1;
	while (i < size)
	{
		((unsigned char *)dst)[i] = ((unsigned char *)src)[j];
		j--;
		i++;
	}
}

void					ft_set_label_pc(t_env *env, char *label)
{
	t_element			*tmp;

	tmp = env->labels->head;
	while (tmp)
	{
		if (!(ft_strcmp(label, ((t_label*)(tmp->content))->label)))
		{
			((t_label*)(tmp->content))->pc = env->pc;
			return ;
		}
		tmp = tmp->next;
	}
}

void					ft_exec_size_counter(t_env *env)
{
	t_element			*elm;
	int					instru_pc;

	instru_pc = 0;
	env->pc = 0;
	elm = env->lines->head;
	while (elm)
	{
		if (((t_instru*)(elm->content))->op_flg ||
				((t_instru*)(elm->content))->lbl_flg)
		{
			if (((t_instru*)(elm->content))->lbl_flg)
				ft_set_label_pc(env, SYM_TAB->label);
			if (((t_instru*)(elm->content))->op_flg)
			{
				SYM_TAB->pc = env->pc;
				instru_pc = ft_pc_counter(SYM_TAB);
				env->pc += instru_pc;
			}
		}
		elm = elm->next;
	}
}

int						ft_code_generator(t_env *env, int total_size)
{
	int					i;

	i = 0;
	if (!(env->exec = ft_memalloc(sizeof(char) * total_size)))
		return (-1);
	ft_magic_header(env->exec);
	i = 4;
	if ((ft_name_generator(env->exec, env->name, i)) == -1)
		return (0);
	i += 132;
	ft_champ_exec_size(env->exec, env->pc, i);
	i += 4;
	if ((ft_comment_generator(env->exec, env->comment, i)) == -1)
		return (0);
	i += 2052;
	if ((ft_champ_exe_code(env, i)) == -1)
		return (0);
	return (1);
}

t_env					*ft_backend_analys(t_env *env)
{
	int					fd;

	ft_exec_size_counter(env);
	if (!(ft_code_generator(env, (env->pc + CODE_HEAD_SIZE))))
		return (0);
	if ((fd = open(env->file_name, O_CREAT | O_WRONLY, S_IRWXU)) == -1)
		return (0);
	write(fd, env->exec, env->pc + CODE_HEAD_SIZE);
	close(fd);
	return (env);
}
