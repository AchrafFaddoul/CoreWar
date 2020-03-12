/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_fextension.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaddoul <afaddoul@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 09:41:11 by afaddoul          #+#    #+#             */
/*   Updated: 2020/03/12 22:11:59 by afaddoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		check_fextension(char *str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	if (str[i - 1] == 's' && str[i - 2] == '.')
		return ;
	else
	{
		ft_putstr_fd("not a valid file", 2);
		exit(1);
	}
}
