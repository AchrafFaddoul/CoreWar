/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champ_exe_code.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaddoul <afaddoul@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 00:32:16 by afaddoul          #+#    #+#             */
/*   Updated: 2020/03/08 06:58:35 by afaddoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char 			ft_get_op_code(t_symbol_tab *sym_tab)
{
	int 		i;

	i = 0;
	while (i < 16)
	{
		if (!ft_strcmp(sym_tab->op, g_op_tab[i].op))
			break ;
		i++;
	}
	return (g_op_tab[i].op_index);
}

void		 			ft_get_tcode(t_symbol_tab *sym_tab, char *exec, int i)
{
	unsigned char 		args[3];
	unsigned char 		ret;

	ft_bzero(args, 3);
	if (sym_tab->val_1.nat == T_REG)
		args[0] = REG_CODE;
	if (sym_tab->val_1.nat == T_IND)
		args[0] = IND_CODE;
	if (sym_tab->val_1.nat == T_DIR)
		args[0] = DIR_CODE;
	if (sym_tab->val_2.nat == T_REG)
		args[1] = REG_CODE;
	if (sym_tab->val_2.nat == T_IND)
		args[1] = IND_CODE;
	if (sym_tab->val_2.nat == T_DIR)
		args[1] = DIR_CODE;
	if (sym_tab->val_3.nat == T_REG)
		args[2] = REG_CODE;
	if (sym_tab->val_3.nat == T_IND)
		args[2] = IND_CODE;
	if (sym_tab->val_3.nat == T_DIR)
		args[2] = DIR_CODE;
	args[0] = args[0] << 6;
	args[1] = args[1] << 4;
	args[2] = args[2] << 2;
	ret = args[0] | args[1] | args[2];
	exec[i] = ret;
}

void 			ft_generate_reg(t_symbol_tab *sym_tab, char *exec,
		int i, int index)
{
	if (index == 1)
		exec[i] = ((char*)(&sym_tab->val_1.val))[0];
	if (index == 2)
		if (((char*)(&sym_tab->val_2.val))[0] == 2)
			printf("********|%d|----\n",sym_tab->val_2.val);
	if (index == 3)
		exec[i] = ((char*)(&sym_tab->val_3.val))[0];
}

int 				ft_get_label_pc(t_env *env, char *arg)
{
	t_element 		*tmp;

	tmp = env->labels->head;
	while (tmp)
	{
		if (!(ft_strcmp(arg + 2, ((t_label*)(tmp->content))->label)))
			break ;
		tmp = tmp->next;
	}
	return ((((t_label*)(tmp->content))->pc));
}

void			ft_generate_indir(t_symbol_tab *sym_tab, t_env *env, int i,
		int index)
{
	int 		pc;

	if (index == 1)
	{
		if (sym_tab->arg_1[0] == LABEL_CHAR)
		{
			pc = ft_get_label_pc(env, sym_tab->arg_1);
			sym_tab->val_1.val = pc - sym_tab->pc;
		}
		env->exec[i] = ((char*)(&sym_tab->val_1.val))[1];
		env->exec[i + 1] = ((char*)(&sym_tab->val_1.val))[0];
	}
	if (index == 2)
	{
		if (sym_tab->arg_2[0] == LABEL_CHAR)
		{
			pc = ft_get_label_pc(env, sym_tab->arg_2);
			sym_tab->val_2.val = pc - sym_tab->pc;
		}
		env->exec[i] = ((char*)(&sym_tab->val_2.val))[1];
		env->exec[i + 1] = ((char*)(&sym_tab->val_2.val))[0];
	}
	if (index == 3)
	{
		if (sym_tab->arg_3[0] == LABEL_CHAR)
		{
			pc = ft_get_label_pc(env, sym_tab->arg_3);
			sym_tab->val_3.val = pc - sym_tab->pc;
		}
		env->exec[i] = ((char*)(&sym_tab->val_3.val))[1];
		env->exec[i + 1] = ((char*)(&sym_tab->val_3.val))[0];
	}
}

void 			ft_generate_dir_short(t_symbol_tab *sym_tab, t_env *env, int i,
		int index)
{
	int 		pc;

			printf("->>>%d<<<-\n", sym_tab->val_2.val);
			printf("-1>>>%d<<<-\n", pc);
			printf("-2>%s>>%d<<<-\n", sym_tab->op, sym_tab->pc);
	if (index == 1)
	{
		if (sym_tab->arg_1[1] == LABEL_CHAR)
		{
			pc = ft_get_label_pc(env, sym_tab->arg_1);
			sym_tab->val_1.val = pc - sym_tab->pc;
		}
		env->exec[i] = ((char*)(&sym_tab->val_1.val))[1];
		env->exec[i + 1] = ((char*)(&sym_tab->val_1.val))[0];
	}
	if (index == 2)
	{
		if (sym_tab->arg_2[1] == LABEL_CHAR)
		{
			pc = ft_get_label_pc(env, sym_tab->arg_2);
			sym_tab->val_2.val = pc - sym_tab->pc;
		}
		env->exec[i] = ((char*)(&sym_tab->val_2.val))[1];
		env->exec[i + 1] = ((char*)(&sym_tab->val_2.val))[0];
	}
	if (index == 3)
	{
		if (sym_tab->arg_3[1] == LABEL_CHAR)
		{
			pc = ft_get_label_pc(env, sym_tab->arg_3);
			sym_tab->val_3.val = pc - sym_tab->pc;
		}
		env->exec[i] = ((char*)(&sym_tab->val_3.val))[1];
		env->exec[i + 1] = ((char*)(&sym_tab->val_3.val))[0];
	}
}
void 			ft_generate_dir_long(t_symbol_tab *sym_tab, t_env *env, int i,
		int index)
{
	int 		pc;

	if (index == 1)
	{
		if (sym_tab->arg_1[1] == LABEL_CHAR)
		{
			pc = ft_get_label_pc(env, sym_tab->arg_1);
			sym_tab->val_1.val = pc - sym_tab->pc;
		}
		env->exec[i] = ((char*)(&sym_tab->val_1.val))[3];
		env->exec[i + 1] = ((char*)(&sym_tab->val_1.val))[2];
		env->exec[i + 2] = ((char*)(&sym_tab->val_1.val))[1];
		env->exec[i + 3] = ((char*)(&sym_tab->val_1.val))[0];
	}
	if (index == 2)
	{
		if (sym_tab->arg_2[1] == LABEL_CHAR)
		{
			pc = ft_get_label_pc(env, sym_tab->arg_2);
			sym_tab->val_2.val = pc - sym_tab->pc;
		}
		env->exec[i] = ((char*)(&sym_tab->val_2.val))[3];
		env->exec[i + 1] = ((char*)(&sym_tab->val_2.val))[2];
		env->exec[i + 2] = ((char*)(&sym_tab->val_2.val))[1];
		env->exec[i + 3] = ((char*)(&sym_tab->val_2.val))[0];
	}
	if (index == 3)
	{
		if (sym_tab->arg_3[1] == LABEL_CHAR)
		{
			pc = ft_get_label_pc(env, sym_tab->arg_3);
			sym_tab->val_3.val = pc - sym_tab->pc;
		}
		env->exec[i] = ((char*)(&sym_tab->val_3.val))[3];
		env->exec[i + 1] = ((char*)(&sym_tab->val_3.val))[2];
		env->exec[i + 2] = ((char*)(&sym_tab->val_3.val))[1];
		env->exec[i + 3] = ((char*)(&sym_tab->val_3.val))[0];
	}
}
int 			ft_generate_instruction(t_symbol_tab *sym_tab, t_env *env,
		int i)
{
	int 		index;

	env->exec[i] = ft_get_op_code(sym_tab);
	i++;
	index = ft_get_op_index(sym_tab->op);

	if (g_op_tab[index].arg_tcode)
	{
	printf("CHECK_1\n");
		ft_get_tcode(sym_tab, env->exec, i);
		i++;
	}
	if (sym_tab->val_1.nat == T_REG)
	{
	printf("CHECK-2\n");
		ft_generate_reg(sym_tab, env->exec, i, 1);
		i++;
	}
	if (sym_tab->val_1.nat == T_IND)
	{
	printf("CHECK-5\n");
		ft_generate_indir(sym_tab, env, i, 1);
		i += 2;
	}
	if (sym_tab->val_1.nat == T_DIR)
	{
	printf("CHECK-8\n");
		if (g_op_tab[index].dir_size)
		{
			ft_generate_dir_short(sym_tab, env, i, 1);
			i += 2;
		}	
		if (!g_op_tab[index].dir_size)
		{
			ft_generate_dir_long(sym_tab, env, i, 1);
			i += 4;
		}
	}
	if (sym_tab->val_2.nat == T_REG)
	{
	printf("CHECK-3\n");
		ft_generate_reg(sym_tab, env->exec, i, 2);
		i++;
	}
	if (sym_tab->val_2.nat == T_IND)
	{
	printf("CHECK-6\n");
		ft_generate_indir(sym_tab, env, i, 2);
		i += 2;
	}
	if (sym_tab->val_2.nat == T_DIR)
	{
	printf("CHECK-10\n");
		if (g_op_tab[index].dir_size)
		{
			ft_generate_dir_short(sym_tab, env, i, 2);
			i += 2;
		}	
		if (!g_op_tab[index].dir_size)
		{
			ft_generate_dir_long(sym_tab, env, i, 2);
			i += 4;
		}
	}
	if (sym_tab->val_3.nat == T_REG)
	{
	printf("CHECK-4\n");
		ft_generate_reg(sym_tab, env->exec, i, 3);
		i++;
	}
	if (sym_tab->val_3.nat == T_IND)
	{
	printf("CHECK-7\n");
		ft_generate_indir(sym_tab, env, i, 3);
		i += 2;
	}
	if (sym_tab->val_3.nat == T_DIR)
	{
	printf("CHECK-11\n");
		if (g_op_tab[index].dir_size)
		{
			ft_generate_dir_short(sym_tab, env, i, 3);
			i += 2;
		}	
		if (!g_op_tab[index].dir_size)
		{
			ft_generate_dir_long(sym_tab, env, i, 3);
			i += 4;
		}
	}
	return (i);
}

int 			ft_champ_exe_code(t_env *env, char *exec, int i)
{
	t_element 	*elm;

	printf("AFT_i:%d\n", i);
	elm = env->lines->head;
	while (elm)
	{
		if (((t_instru*)(elm->content))->op_flg)
		{
			printf("|%d|\n|%s|\n", i, SYM_TAB->op);
			printf("||||%d-%d|||||\n", SYM_TAB->val_1.nat, SYM_TAB->val_2.nat);
			i = ft_generate_instruction(SYM_TAB, env, i);
			printf("DONE\n");
		}
		elm = elm->next;
	}
	return (i);
}
