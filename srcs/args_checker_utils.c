/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_checker_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaddoul <afaddoul@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 21:05:58 by afaddoul          #+#    #+#             */
/*   Updated: 2020/03/12 21:05:58 by afaddoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int					ft_reg_checker(char *arg)
{
	if (!(ft_isvalid(arg)))
		return (-1);
	return (ft_atoi(arg));
}

int					ft_dirchecker(t_element *elm, char *arg, int arg_nb)
{
	if (arg_nb == 1)
		SYM_TAB->val_1.nat = T_DIR;
	else if (arg_nb == 2)
		SYM_TAB->val_2.nat = T_DIR;
	else if (arg_nb == 3)
		SYM_TAB->val_3.nat = T_DIR;
	if (*arg == LABEL_CHAR)
		return (0);
	return (1);
}

int					ft_indirchecker(t_element *elm, char *arg, int arg_nb)
{
	if (arg_nb == 1)
		SYM_TAB->val_1.nat = T_IND;
	else if (arg_nb == 2)
		SYM_TAB->val_2.nat = T_IND;
	else if (arg_nb == 3)
		SYM_TAB->val_3.nat = T_IND;
	if (*arg == LABEL_CHAR)
		return (0);
	return (1);
}
