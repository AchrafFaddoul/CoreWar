/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaddoul <afaddoul@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 09:41:11 by afaddoul          #+#    #+#             */
/*   Updated: 2020/02/29 04:32:07 by ada              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void 		ft_error(void)
{
	write(1, "Error\n", 6);
	exit(1);
}

int			main(int argc, char *argv[])
{
	t_env	*env;
	char	*file;
	int		fd;

	if (argc != 2)
		ft_error();
	check_fextension(argv[1]);
	if ((fd = open(argv[1], O_RDONLY)) == -1)
		ft_error();
	file = read_file(fd);
	if (!(env = (t_env*)ft_memalloc(sizeof(t_env))))
		ft_error();
	env->vect = file;
	ft_assembler(env);
	printf("Done\n");
	return (0);
}
