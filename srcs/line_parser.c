/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 02:14:19 by ada               #+#    #+#             */
/*   Updated: 2020/02/25 03:37:28 by ada              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_env		*ft_line_parser(t_env *env)
{
	int 	i;
	int		j;

	i = 0;
	j = 0;
	while (env->vect[i])
	{
		if (env->vect[i] == '\n')
		{
			if (!ft_get_line(env, j, i))
				return (NULL);
			printf("%s", ((t_instru*)(env->lines->tail->content))->buff);
			j = i + 1;
		}
		i++;
	}
	return (env);
}
