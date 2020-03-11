/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_tcode.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 23:21:51 by ada               #+#    #+#             */
/*   Updated: 2020/03/11 23:25:57 by ada              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static unsigned char		ft_shift_bits(unsigned char *args)
{
	unsigned char			ret;

	args[0] = args[0] << 6;
	args[1] = args[1] << 4;
	args[2] = args[2] << 2;
	ret = args[0] | args[1] | args[2];
	return (ret);
}

void						ft_get_tcode(t_symbol_tab *sym_tab, char *exec,
		int i)
{
	unsigned char		args[3];
	unsigned char		ret;

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
	ret = ft_shift_bits(args);
	exec[i] = ret;
}
