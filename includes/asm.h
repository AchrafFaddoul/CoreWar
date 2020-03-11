/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaddoul <afaddoul@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 09:41:11 by afaddoul          #+#    #+#             */
/*   Updated: 2020/03/11 23:33:09 by ada              ###   ########.fr       */
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
# define SYM_TAB ((t_symbol_tab*)(((t_instru*)(elm->content))->sym_tab))


typedef struct		 s_op
{
	char			*op;
	int				arg_nb;
	int 			arg[3];
	unsigned char	 op_index;
	int 			cycle;
	char 			*op_desc;
	int				arg_tcode;
	int 			dir_size;
}					t_op;

t_op				g_op_tab[17];

typedef struct 		s_label
{
	char			*label;
	int 			pc;
}					t_label;

typedef struct 		s_args
{
	unsigned int	val;
	int 			nat;
	int 			byte_size;
}					t_args;

typedef struct 		s_ptrs
{
	int 			start;
	int 			end;
}					t_ptrs;

typedef struct 		s_symbol_tab
{
	char			*label;
	char 			*op;
	char 			*arg_1;
	char 			*arg_2;
	char 			*arg_3;
	t_args			val_1;
	t_args			val_2;
	t_args			val_3;
	int 			pc;
}					t_symbol_tab;

typedef struct 		s_instru
{
	char			*buff;
	int				op_flg;
	int				lbl_flg;
	int 			index;
	t_symbol_tab	*sym_tab;
}					t_instru;

typedef struct 		s_env
{
	t_dlist 		*lines;
	t_dlist 		*labels;
	char 			*exec;
	char 			*vect;
	char 			*name;
	char 			*comment;
	char 			*file_name;
	int 			pc;
}					t_env;

void				check_fextension(char *str);
char				*read_file(int fd);
char 				*ft_vrealloc(char *buff, size_t buff_size);
void				ft_assembler(t_env *env);
t_env				*ft_frontend_analys(t_env *env);
t_env				*ft_line_parser(t_env *env);
char				*ft_get_line(t_env *env, int start, int end);
t_instru			*ft_instru_new(char *line);
t_element			*get_name(t_env *env, const char *ptr, int max_size,
		t_element *elm);
t_element			*get_cmt(t_env *env, const char *ptr, int max_size,
		t_element *elm);
t_element			*ft_get_cmd_dispatcher(t_env *env, const char *ptr,
		t_element *elm);
t_env				*ft_cmd_parser(t_env *env);
void 				ft_error(void);
void				dummy_del(void *content);
t_env				*ft_instruparser(t_env *env);
t_env				*ft_scanner(t_env *env, t_element *elm, char *ptr);
int					ft_syntax_analys(t_env *env, t_element *elm, char *ptr);
int					ft_instru_tokenizer(t_env *env, t_element *elm, char *ptr);
t_env				*ft_getop(t_env *env, t_element *elm, char *ptr);
t_env				*ft_get_instru(t_env *env, t_element *elm, char *str);
int					ft_argscanner(t_env *env, t_element *elm, char *str,
		int index);
int                 ft_argtokenizer(t_env *env, t_element *elm, char *str,
		t_ptrs ptrs);
int					ft_lbltokenizer(t_env *env, t_element *elm,char *ptr,
		int len);
t_label				*ft_labelnew(char *token);
char				*ft_wsdel(char *str);
char				*ft_intrucpy(char *ptr, char *dest);
int					ft_islabel(char c);
int					ft_isop(char c);
int					ft_check_args(t_element *elm, char *arg, int arg_nb);
int					ft_isreg(t_element *elm, char *arg, int arg_nb);
int					ft_semantic_analysis(t_env *env);
int					ft_get_op_index(char *op);
int					ft_args_checker(t_env *env);
int					ft_check_args_type(t_element *elm, int arg_nb, int index);
int					ft_check_arg_nb(t_element *elm, int arg_nb);
t_env				*ft_backend_analys(t_env *env);
void				ft_exec_size_counter(t_env *env);
int 				ft_pc_counter(t_symbol_tab* sym_tab);
void				ft_set_label_pc(t_env *env, char *label);
char				*ft_fname_extracter(char *f_name);
void				swap_bytes(void *src, void *dst, int size);
int					ft_code_generator(t_env *env, int total_size);
int					ft_magic_header(char *exec);
int					ft_name_generator(char *exec, char *name, int i);
int					ft_comment_generator(char *exec, char *cmt, int i);
int         	    ft_generate_instruction(t_symbol_tab *sym_tab, t_env *env,
		int i);
int          	   ft_champ_exe_code(t_env *env, int i);
void				ft_champ_exec_size(char *exec, int pc, int i);
int					ft_check_separators(char *str, int index);
t_element			*ft_get_next_node(t_element *elm, char *buff, int j,
		int size);
void				ft_env_destroy(t_env *env);
void				ft_lines_del(void *content);
void				ft_label_del(void *content);
void				ft_gen_ind_arg1(t_symbol_tab *sym_tab, t_env *env,
		int i, int *pc);
void				ft_gen_ind_arg2(t_symbol_tab *sym_tab, t_env *env,
		int i, int *pc);
void				ft_gen_ind_arg3(t_symbol_tab *sym_tab, t_env *env,
		int i, int *pc);
void				ft_gen_sdir_arg1(t_symbol_tab *sym_tab, t_env *env,
		int i, int *pc);
void				ft_gen_sdir_arg2(t_symbol_tab *sym_tab, t_env *env,
		int i, int *pc);
void				ft_gen_sdir_arg3(t_symbol_tab *sym_tab, t_env *env,
		int i, int *pc);
void				ft_gen_ldir_arg1(t_symbol_tab *sym_tab, t_env *env,
		int i, int *pc);
void				ft_gen_ldir_arg2(t_symbol_tab *sym_tab, t_env *env,
		int i, int *pc);
void				ft_gen_ldir_arg3(t_symbol_tab *sym_tab, t_env *env,
		int i, int *pc);
void				ft_gen_arg1_bytecode(t_symbol_tab *sym_tab,
		t_env *env, int *i, int index);
void				ft_gen_arg2_bytecode(t_symbol_tab *sym_tab,
		t_env *env, int *i, int index);
void				ft_gen_arg3_bytecode(t_symbol_tab *sym_tab,
		t_env *env, int *i, int index);
void                        ft_get_tcode(t_symbol_tab *sym_tab, char *exec,
		int i);
int					ft_get_label_pc_dir(t_env *env, char *arg);
int					ft_get_label_pc_indir(t_env *env, char *arg);
char				ft_get_op_code(t_symbol_tab *sym_tab);
void				ft_generate_reg(t_symbol_tab *sym_tab, char *exec,
		int i, int index);
int					ft_get_label_pc_dir(t_env *env, char *arg);
int					ft_get_label_pc_indir(t_env *env, char *arg);

#endif
