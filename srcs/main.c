/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaddoul <afaddoul@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 09:41:11 by afaddoul          #+#    #+#             */
/*   Updated: 2020/02/27 14:24:51 by ada              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			main(int argc, char *argv[])
{
	t_env	*env;
	char	*file;
	int		fd;

	if (argc != 2)
		exit(1);
	check_fextension(argv[1]);
	if ((fd = open(argv[1], O_RDONLY)) == -1)
		exit(1);
	file = read_file(fd);
	if (!(env = (t_env*)ft_memalloc(sizeof(t_env))))
		exit(1);
	env->vect = file;
	ft_assembler(env);
	return (0);
}
