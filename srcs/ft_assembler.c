/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_assembler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 02:20:22 by ada               #+#    #+#             */
/*   Updated: 2020/03/12 01:13:04 by ada              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void				ft_lines_del(void *content)
{
	t_instru		*instru;
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

void				ft_label_del(void *content)
{
	t_label			*lbl;

	lbl = (t_label*)content;
	if (lbl->label)
		ft_strdel((char**)&(lbl->label));
	ft_memdel((void**)&lbl);
}

void				ft_env_destroy(t_env *env)
{
	if (env->vect)
		ft_strdel((char**)&(env->vect));
	if (env->file_name)
		ft_strdel((char**)&(env->file_name));
	if (env->exec)
		ft_strdel((char**)&(env->exec));
	if (env->name)
		ft_strdel((char**)&(env->name));
	if (env->comment)
		ft_strdel((char**)&(env->comment));
	if (env->lines)
		ft_dlstdel(&env->lines, ft_lines_del);
	if (env->labels)
		ft_dlstdel(&env->labels, ft_label_del);
	if (env)
		ft_memdel((void**)&(env));
}

void				ft_assembler(t_env *env)
{
	if (!ft_frontend_analys(env))
	{
		ft_env_destroy(env);
		ft_error();
	}
	if (!(ft_backend_analys(env)))
	{
		ft_env_destroy(env);
		ft_error();
	}
	ft_env_destroy(env);
}
