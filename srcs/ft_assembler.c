/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_assembler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 02:20:22 by ada               #+#    #+#             */
/*   Updated: 2020/03/11 18:29:05 by ada              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void 				ft_lines_del(void *content)
{
	t_instru 		*instru;
	t_symbol_tab	*sym_tab;

	instru = (t_instru*)content;
	if (instru->buff)
		ft_strdel((char**)&(instru->buff));
	if (instru->sym_tab)
	{
		sym_tab = ((t_symbol_tab*)instru->sym_tab);
		if (sym_tab->label)
			ft_strdel((char**)&(sym_tab->label));
		if (sym_tab->op)
			ft_strdel((char**)&(sym_tab->op));
		if (sym_tab->arg_1)
			ft_strdel((char**)&(sym_tab->arg_1));
		if (sym_tab->arg_2)
			ft_strdel((char**)&(sym_tab->arg_2));
		if (sym_tab->arg_3)
			ft_strdel((char**)&(sym_tab->arg_3));
		ft_memdel((void**)&(instru->sym_tab));
	}
	ft_memdel((void**)&instru);
}

void 				ft_label_del(void *content)
{
	t_label			*lbl;

	lbl = (t_label*)content;
	printf("from LABEL_DEL\n");
	if (lbl)
	{
		if (lbl->label)
			ft_strdel((char**)&(lbl->label));
		ft_memdel((void**)lbl);
	}
}

void 				ft_env_destroy(t_env *env)
{
	printf("DBL FREE ISSUE\n");
	if (env->vect)
		ft_strdel((char**)&(env->vect));
	printf("HERE_1\n");
	if (env->file_name)
		ft_strdel((char**)&(env->file_name));
	printf("HERE_2\n");
	if (env->exec)
	ft_strdel((char**)&(env->exec));
	printf("HERE_3\n");
	if (env->name)
	ft_strdel((char**)&(env->name));
	printf("HERE_4\n");
	if (env->comment)
	ft_strdel((char**)&(env->comment));
	printf("HERE_5\n");
	if (env->lines)
		ft_dlstdel(&env->lines, ft_lines_del);
	printf("HERE_6\n");
	if (env->labels)
		ft_dlstdel(&env->lines, ft_label_del);
	printf("HERE_7\n");
	if (env)
		ft_memdel((void**)&(env));
	printf("HERE_8\n");
}

void 				ft_assembler(t_env *env)
{
	if (!ft_frontend_analys(env))
	{
		ft_env_destroy(env);
		ft_error();
	}
	if(!(ft_backend_analys(env)))
	{
		ft_env_destroy(env);
		ft_error();
		//free_leaks
	}
	printf("DESTROY\n");
	ft_env_destroy(env);
}
