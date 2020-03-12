/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   code_gen_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 01:31:57 by ada               #+#    #+#             */
/*   Updated: 2020/03/12 01:33:30 by ada              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int						ft_magic_header(char *exec)
{
	int					tmp;
	int					magic_header;
	int					i;

	tmp = 0;
	i = 0;
	magic_header = COREWAR_EXEC_MAGIC;
	swap_bytes(&magic_header, &tmp, 4);
	while (i < 4)
	{
		exec[i] = ((char*)(&tmp))[i];
		i++;
	}
	return (i);
}

void					ft_champ_exec_size(char *exec, int pc, int i)
{
	int					tmp;
	int					j;

	tmp = 0;
	j = 0;
	swap_bytes(&pc, &tmp, 4);
	while (j < 4)
	{
		exec[i] = ((char*)(&tmp))[j];
		i++;
		j++;
	}
}

int						ft_name_generator(char *exec, char *name, int i)
{
	char				*tmp;
	int					j;

	j = 0;
	if (!(tmp = ft_memalloc(sizeof(char) * (PROG_NAME_LENGTH + 1))))
		return (-1);
	ft_strcpy(tmp, name);
	while (j < PROG_NAME_LENGTH)
	{
		exec[i] = tmp[j];
		i++;
		j++;
	}
	ft_strdel((char**)&tmp);
	return (i);
}

int						ft_comment_generator(char *exec, char *cmt, int i)
{
	char				*tmp;
	int					j;

	j = 0;
	if (!(tmp = ft_memalloc(sizeof(char) * (COMMENT_LENGTH + 1))))
		return (-1);
	ft_strcpy(tmp, cmt);
	while (j < COMMENT_LENGTH)
	{
		exec[i] = tmp[j];
		i++;
		j++;
	}
	ft_strdel((char**)&tmp);
	return (i);
}
