/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analysis_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 11:00:14 by ada               #+#    #+#             */
/*   Updated: 2020/03/12 11:25:32 by ada              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int					ft_isreg(t_element *elm, char *arg, int arg_nb)
{
	int				reg;

	if ((reg = ft_reg_checker(arg)) == -1)
		return (0);
	if (reg < 1 || reg > 16)
		return (0);
	if (arg_nb == 1)
	{
		SYM_TAB->val_1.val = reg;
		SYM_TAB->val_1.nat = T_REG;
	}
	if (arg_nb == 2)
	{
		SYM_TAB->val_2.val = reg;
		SYM_TAB->val_2.nat = T_REG;
	}
	if (arg_nb == 3)
	{
		SYM_TAB->val_3.val = reg;
		SYM_TAB->val_3.nat = T_REG;
	}
	return (1);
}

int					ft_isvalid(char *arg)
{
	int				i;

	i = 0;
	while (arg[i])
	{
		if (!(ft_isdigit(arg[i])))
			return (0);
		i++;
	}
	return (1);
}

int					ft_isnumber(char *arg)
{
	int				i;

	i = 0;
	if (*arg == '-')
	{
		if (!(ft_isvalid(arg + 1)))
			return (0);
	}
	else
	{
		if (!(ft_isvalid(arg)))
			return (0);
	}
	return (1);
}

int					ft_isdir(t_element *elm, char *arg, int arg_nb)
{
	int				val;

	val = 0;
	if (!(ft_dirchecker(elm, arg, arg_nb)))
		return (1);
	else if (*arg == '-' || ft_isdigit(*arg))
	{
		if (!(ft_isnumber(arg)))
			return (0);
		val = ft_atoi(arg);
		if (arg_nb == 1)
			SYM_TAB->val_1.val = val;
		if (arg_nb == 2)
			SYM_TAB->val_2.val = val;
		if (arg_nb == 3)
			SYM_TAB->val_3.val = val;
	}
	else
		return (0);
	return (1);
}

int					ft_isindir(t_element *elm, char *arg, int arg_nb)
{
	int				val;

	val = 0;
	if (!(ft_indirchecker(elm, arg, arg_nb)))
		return (1);
	else if (*arg == '-' || ft_isdigit(*arg))
	{
		if (!(ft_isnumber(arg)))
			return (0);
		val = ft_atoi(arg);
		if (arg_nb == 1)
			SYM_TAB->val_1.val = val;
		if (arg_nb == 2)
			SYM_TAB->val_2.val = val;
		if (arg_nb == 3)
			SYM_TAB->val_3.val = val;
	}
	else
		return (0);
	return (1);
}
