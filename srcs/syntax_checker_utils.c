/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 14:42:24 by ada               #+#    #+#             */
/*   Updated: 2020/03/12 14:46:22 by ada              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int					ft_tokenize_arg(t_ptrs *ptrs, t_element *elm, char *str,
		int *i)
{
	while (str[*i])
	{
		if (str[*i] == SEPARATOR_CHAR || str[*i] == '\n' ||
				str[*i] == COMMENT_CHAR || str[*i] == ALT_COMMENT_CHAR)
		{
			ptrs->end = *i;
			if (!ft_argtokenizer(elm, str, *ptrs))
				return (0);
			break ;
		}
		(*i)++;
	}
	return (1);
}

int					ft_arg_filler(t_element *elm, char *arg)
{
	if (!SYM_TAB->arg_1)
	{
		SYM_TAB->arg_1 = arg;
		if (!(ft_check_args(elm, arg, 1)))
			return (0);
	}
	else if (!SYM_TAB->arg_2)
	{
		SYM_TAB->arg_2 = arg;
		if (!(ft_check_args(elm, arg, 2)))
			return (0);
	}
	else if (!SYM_TAB->arg_3)
	{
		SYM_TAB->arg_3 = arg;
		if (!(ft_check_args(elm, arg, 3)))
			return (0);
	}
	else
		return (0);
	return (1);
}

int					ft_check_args(t_element *elm, char *arg, int arg_nb)
{
	int				val;

	val = -1;
	if (*arg == 'r')
	{
		if (!(ft_isreg(elm, arg + 1, arg_nb)))
			return (0);
	}
	else if (*arg == DIRECT_CHAR)
	{
		if (!(ft_isdir(elm, arg + 1, arg_nb)))
			return (0);
	}
	else if (*arg == LABEL_CHAR || *arg == '-' || ft_isdigit(*arg))
	{
		if (!(ft_isindir(elm, arg, arg_nb)))
			return (0);
	}
	return (1);
}

char				*ft_instrucpy(char *ptr, char *dest)
{
	int				i;
	int				j;

	i = 0;
	j = 0;
	while (ptr[i])
	{
		if (ptr[i] != 9 && ptr[i] != 32)
		{
			dest[j] = ptr[i];
			j++;
		}
		i++;
	}
	return (dest);
}

char				*ft_wsdel(char *str)
{
	int				i;
	size_t			len;
	int				counter;
	char			*dest;

	i = 0;
	counter = 0;
	while (str[i])
	{
		if (str[i] == 9 || str[i] == 32)
			counter++;
		i++;
	}
	len = ft_strlen(str) - counter;
	if (!(dest = (char*)ft_memalloc(sizeof(char) * (len + 1))))
		return (NULL);
	dest = ft_instrucpy(str, dest);
	return (dest);
}
