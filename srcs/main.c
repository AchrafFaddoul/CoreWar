/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaddoul <afaddoul@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 09:41:11 by afaddoul          #+#    #+#             */
/*   Updated: 2020/01/12 19:00:51 by afaddoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int main(int argc, char *argv[])
{
	char 	*file;
	int	fd;

	if (argc > 2)
		return (0);
	check_fextension(argv[1]);
	if ((fd = open(argv[1], O_RDONLY)) == -1)
		exit(1);
	file = read_file(fd);
	return (0);
}
