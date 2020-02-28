/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_label_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 15:43:20 by ada               #+#    #+#             */
/*   Updated: 2020/02/28 16:57:51 by ada              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	ft_islabel(char c)
{
	if ((c >= 97 && c <= 122) || (c >= 48 && c <= 57)
			|| c == '_')
		return (1);
	return (0);
}

t_env 			*ft_label_parser(t_env *env)
{
	t_element	*elm;
	char 		*ptr;
	int 		i;

	elm = env->lines->head;
	while (elm)
	{
		;
		elm = elm->next;
	}
}
