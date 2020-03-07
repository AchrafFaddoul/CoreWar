/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backend_analysis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaddoul <afaddoul@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 13:58:58 by afaddoul          #+#    #+#             */
/*   Updated: 2020/03/07 21:50:09 by afaddoul         ###   ########.fr       */
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

void 				ft_magic_header(int fd)
{
	int 			tmp;
	int 			magic_header;

	tmp = 0;
	magic_header = COREWAR_EXEC_MAGIC;
	swap_bytes(&magic_header, &tmp, 3);
	write(fd, &tmp, 3);
}

int 				ft_name_generator(char *name, int fd)
{
	char			*tmp;

	if(!(tmp = ft_memalloc(sizeof(char) * PROG_NAME_LENGTH)))
		return (0);
	ft_strcpy(tmp, name);
	write(fd, tmp, PROG_NAME_LENGTH);
	return (1);
}

int 				ft_comment_generator(char *comment, int fd)
{
	char			*tmp;

	if(!(tmp = ft_memalloc(sizeof(char) * COMMENT_LENGTH)))
		return (0);
	ft_strcpy(tmp, comment);
	write(fd, tmp, COMMENT_LENGTH);
	return (1);
}
void 				ft_exec_size_gen(int size, int fd)
{
	int 			tmp;

	printf("pc:%d\n", size);
	swap_bytes(&size, &tmp, 4);
	write(fd, &tmp, 4);
}

t_env				*ft_backend_analys(t_env *env)
{
	int  			fd;

	ft_exec_size_counter(env);
	if ((fd = open(env->file_name, O_CREAT | O_WRONLY, S_IRWXU)) == -1)
		return (NULL);
	ft_magic_header(fd);
	if (!(ft_name_generator(env->name, fd)))
		return (0);
	write(fd, (char[4]){0}, 4);
	ft_exec_size_gen(env->pc, fd);
	if (!(ft_comment_generator(env->comment, fd)))
		return (0);
	write(fd, (char[4]){0}, 4);
	return (env);
}
