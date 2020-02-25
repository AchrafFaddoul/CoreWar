/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_fextension.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaddoul <afaddoul@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 09:41:11 by afaddoul          #+#    #+#             */
/*   Updated: 2020/02/25 01:00:22 by ada              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		check_fextension(char *str)
{
	int		i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			if (str[i] == '.')
			{
				if (str[i + 1] && str[i + 1] == 's')
				{
					if (!str[i + 2])
						return ;
				}
				else
				{
					ft_putstr("not a valid file");
					exit(1);
				}
			}
			i++;
		}
	}
	ft_putstr("not a valid file");
	exit(1);
}
