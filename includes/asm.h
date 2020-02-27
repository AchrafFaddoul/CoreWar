/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaddoul <afaddoul@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 09:41:11 by afaddoul          #+#    #+#             */
/*   Updated: 2020/02/27 16:15:23 by ada              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
#define ASM_H

#include "libft.h"
#include "op.h"
#include <stdio.h>
#include <fcntl.h>
# define BUFF_SIZE 1000
# define MAX_SIZE 1000000


typedef struct 		s_instru
{
	char			*buff;
	int 			index;
}					t_instru;

typedef struct 		s_env
{
	char 			*vect;
	char 			*name;
	char 			*comment;
	t_dlist 		*lines;
}					t_env;

void			check_fextension(char *str);
char			*read_file(int fd);
char 			*ft_vrealloc(char **buff, size_t buff_size);
void			ft_assembler(t_env *env);
t_env			*ft_frontend_analys(t_env *env);
t_env			*ft_line_parser(t_env *env);
char			*ft_get_line(t_env *env, int start, int end);
t_instru		*ft_instru_new(char *line);
t_env			*get_name(t_env *env, const char *ptr, int max_size);
t_env			*get_cmt(t_env *env, const char *ptr, int max_size);
t_env			*ft_get_cmd_dispatcher(t_env *env, const char *ptr);
t_env			*ft_cmd_parser(t_env *env);
void 			ft_error(void);


#endif