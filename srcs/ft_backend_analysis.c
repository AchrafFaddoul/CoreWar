/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backend_analysis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaddoul <afaddoul@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 13:58:58 by afaddoul          #+#    #+#             */
/*   Updated: 2020/03/07 23:17:22 by afaddoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void				swap_bytes(void *src, void *dst, int size)
{
	int i = 0;
	int j = size - 1;
	while (i < size)
	{
		((unsigned char *)dst)[i] = ((unsigned char *)src)[j];
		j--;
		i++;
	}
}

void 				ft_set_label_pc(t_env *env, char *label)
{
	t_element 		*tmp;

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

int 				ft_pc_counter(t_symbol_tab* sym_tab)
{
	int 			pc;
	int 			index;

	pc = 1;
	index = ft_get_op_index(sym_tab->op);
	if (g_op_tab[index].arg_tcode)
		pc++;
	if (sym_tab->arg_1)
	{
		if (sym_tab->val_1.nat == T_REG)
			pc++;
		else if (sym_tab->val_1.nat == T_IND)
			pc += 2;
		else if (sym_tab->val_1.nat == T_DIR)
		{
			if (!g_op_tab[index].dir_size)
				pc += 4;
			else
				pc += 2;
		}
	}
	if (sym_tab->arg_2)
	{
		if (sym_tab->val_2.nat == T_REG)
			pc++;
		else if (sym_tab->val_2.nat == T_IND)
			pc += 2;
		else if (sym_tab->val_2.nat == T_DIR)
		{
			if (!g_op_tab[index].dir_size)
				pc += 4;
			else
				pc += 2;
		}
	}
	if (sym_tab->arg_3)
	{
		if (sym_tab->val_3.nat == T_REG)
			pc++;
		else if (sym_tab->val_3.nat == T_IND)
			pc += 2;
		else if (sym_tab->val_3.nat == T_DIR)
		{
			if (!g_op_tab[index].dir_size)
				pc += 4;
			else
				pc += 2;
		}
	}
	return (sym_tab->pc = pc);
}

void 				ft_exec_size_counter(t_env *env)
{
	t_element 		*elm;
	int 			instru_pc;

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

int 				ft_magic_header(char *exec)
{
	int 			tmp;
	int 			magic_header;
	int 			i;

	tmp = 0;
	i = 0;
	magic_header = COREWAR_EXEC_MAGIC;
	swap_bytes(&magic_header, &tmp, 3);
	while (i < 3)
	{
		exec[i] = ((char*)(&tmp))[i];
		i++;
	}
	return (i);
}

int 				ft_name_generator(char *exec, char *name, int i)
{
	char			*tmp;
	int 			j;

	j = 0;
	if(!(tmp = ft_memalloc(sizeof(char) * PROG_NAME_LENGTH)))
		return (-1);
	ft_strcpy(tmp, name);
	while(j < PROG_NAME_LENGTH)
	{
		exec[i] = tmp[j];
		i++;
		j++;
	}
	return (i);
}

int 				ft_comment_generator(char *exec, char *cmt, int i)
{
	char			*tmp;
	int 			j;

	j = 0;
	if(!(tmp = ft_memalloc(sizeof(char) * COMMENT_LENGTH)))
		return (-1);
	ft_strcpy(tmp, cmt);
	while(j < COMMENT_LENGTH)
	{
		exec[i] = tmp[j];
		i++;
		j++;
	}
	return (i);
}
void 				ft_exec_size_gen(int size, int fd)
{
	int 			tmp;

	swap_bytes(&size, &tmp, 4);
	write(fd, &tmp, 4);
}

int 				ft_code_generator(t_env *env, int total_size)
{
	char 			exec[total_size];
	int 			fd;
	int 			i;

	i = 0;
	ft_bzero(exec, total_size);
	i += ft_magic_header(exec);
	if ((i = ft_name_generator(exec, env->name, i)) == -1)
		return (0);
	i += 4;
	if ((ft_comment_generator(exec, env->comment, i)) == -1)
		return (0);
	i += 4;
	;
	if ((fd = open(env->file_name, O_CREAT | O_WRONLY, S_IRWXU)) == -1)
		return (0);
	write(fd, exec, total_size);
	//	write(fd, (char[4]){0}, 4);
	//	ft_exec_size_gen(env->pc, fd);
	//	if (!(ft_comment_generator(env->comment, fd)))
	//		return (0);
	//	write(fd, (char[4]){0}, 4);
	return (1);
}

t_env				*ft_backend_analys(t_env *env)
{
	ft_exec_size_counter(env);
	if (!(ft_code_generator(env, (env->pc + CODE_HEAD_SIZE))))
		return (0);
	return (env);
}
