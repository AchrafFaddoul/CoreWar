/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semantic_analys.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaddoul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 12:29:21 by ada               #+#    #+#             */
/*   Updated: 2020/03/06 17:44:58 by afaddoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int					ft_semantic_analysis(t_env *env)
{
	t_element 		*elm;

	elm = env->labels->head;
	while (elm)
	{
		printf("%s\n", ((t_label*)(elm->content))->label);
		elm = elm->next;
	}
	return (1);
}
