/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   code_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 21:53:42 by ada               #+#    #+#             */
/*   Updated: 2020/03/03 03:24:35 by ada              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int			ft_islabel(char c)
{
	if ((c >= 97 && c <= 122) || (c >= 48 && c <= 57)
			|| c == '_')
		return (1);
	return (0);
}

static int 			ft_isop(char c)
{
	if ((c >= 97 && c <= 122))
		return (1);
	return (0);
}

char				*ft_instrucpy(char *ptr, char *dest)
{
	int 			i;
	int 			j;

	i = 0;
	j = 0;
	while (ptr[i])
	{
		if (ptr[i] != 9 && ptr[i] != 32)
		{
			dest[j] = ptr[i];
			j++;
		}
		i++;
	}
	return (dest);
}

char 				*ft_wsdel(char *str)
{
	int 			i;
	size_t			len;
	int 			counter;
	char 			*dest;

	i = 0;
	counter = 0;
	while (str[i])
	{
		if (str[i] == 9 || str[i] == 32)
			counter++;
		i++;
	}
	len = ft_strlen(str) - counter;
	if (!(dest = (char*)ft_memalloc(sizeof(char) * (len + 1))))
		return (NULL);
	dest = ft_instrucpy(str, dest);
	return (dest);
}

static t_label		*ft_labelnew(char *token)
{
	t_label 		*elm;

	if (!(elm = (t_label*)ft_memalloc(sizeof(t_label))))
		return (NULL);
	elm->label = token;
	return (elm);
}

int 				ft_lbltokenizer(t_env *env, t_element *elm,
		char *ptr, int len)
{
	char 			*str;
	t_label			*element;
	t_element 		*label;

	if (!(str = (char*)ft_memalloc(sizeof(char) * (len + 1))))
		return (0);
	ft_strncpy(str, ptr, len);
	if (!(element = ft_labelnew(str)))
	{
		ft_strdel((char**)&str);
		return (0);
	}
	if (!(label = ft_elemnew(element)))
	{
		ft_strdel((char**)&str);
		ft_memdel((void**)&element);
		return (0);
	}
	ft_dlstpush(env->labels, label);
	SYM_TAB->label = ft_strdup(str);
	((t_instru*)(elm->content))->lbl_flg = 1;
	return (1);
}

int					ft_argtokenizer(t_element *elm, char *str, int start, 
		int arg_nb)
{
	int 			i;
	char 			*arg;

	i = 0;
	while (str[i] != '\n' && str[i] != COMMENT_CHAR &&
			str[i] != ALT_COMMENT_CHAR && str[i] != SEPARATOR_CHAR)
		i++;
	printf("separator|%c|\n", str[i]);
	if (!(arg = ft_strsub(str, start, i)))
		return (-1);
	printf("SUB|%s|\n", arg);
	if (arg_nb == 1)
		SYM_TAB->arg_1 = arg;
	else if (arg_nb == 2)
		SYM_TAB->arg_2 = arg;
	else if (arg_nb == 3)
		SYM_TAB->arg_3 = arg;
	if (str[i] == SEPARATOR_CHAR)
		i++;
	return (i);
}

			//	ft_strdel((char**)&(SYM_TAB->op));
			//	ft_strdel((char**)&(SYM_TAB->arg_1));
			//	ft_strdel((char**)&(SYM_TAB->arg_2));
			//	ft_strdel((char**)&(SYM_TAB->arg_3));

int 				ft_argscanner(t_element *elm, char *str, int index)
{
	int				i;
	int 			calls_nb;

	i = 0;
	calls_nb = 0;
	printf("|%s|", str);
	while (str[i])
	{
	//	printf("LOOP\n");	
		if (str[i] == 'r' || str[i] == DIRECT_CHAR ||
				ft_isdigit(str[i]) || str[i] == '-')
		{
			calls_nb++;
			if ((index >= g_op_tab[index].arg_nb) ||
					((i = ft_argtokenizer(elm, str, i, calls_nb)) == -1))
			{
				return (0);
			}
			if (str[i] == '\n' || str[i] == COMMENT_CHAR ||
					str[i] == ALT_COMMENT_CHAR)
				break ;
			else if (str[i] == SEPARATOR_CHAR)
			{
				if (str[i + 1] == 'r' || str[i + 1] == DIRECT_CHAR ||
					ft_isdigit(str[i + 1]) || str[i + 1] == '-')
					continue ;
				else
					return (0);
			}
			else
				return (0);
		}
		i++;
	}
	return (1);
}	

t_env				*ft_get_instru(t_env *env, t_element *elm, char *str)
{
	int 			i;
	int 			index;

	i = 0;
	//get op
	while (i < 16)
	{
		printf("%s\n", str);
		if ((ft_strstr(str, g_op_tab[i].op)))
			break ;
			if (i == 15)
				return (NULL);
		i++;
	}
	printf("OUT\n");
	if (!(SYM_TAB->op = ft_strdup(g_op_tab[i].op)))
		return (NULL);
	//get args
	index = i;
	i = ft_strlen(g_op_tab[i].op);
	printf("INPUT |%s|\n", str);
	printf("thats what am looking for |%s|\n", str + i);
	printf("index:%d\n", i);
	// one arg 
	if (!(ft_argscanner(elm, str + i, index)))
		return (NULL);
	printf("INTO ARG\n");
	printf("OUT A SAT A SAT\n");
	printf("*** PARSE ARGS  ***\n");
	printf("%s\n%s\n%s\n%s\n%s\n", 
	((t_symbol_tab*)((t_instru*)(elm->content))->sym_tab)->label, 
	((t_symbol_tab*)((t_instru*)(elm->content))->sym_tab)->op, 
	((t_symbol_tab*)((t_instru*)(elm->content))->sym_tab)->arg_1, 
	((t_symbol_tab*)((t_instru*)(elm->content))->sym_tab)->arg_2,
	((t_symbol_tab*)((t_instru*)(elm->content))->sym_tab)->arg_3);
	printf("*** DONE  ***\n");
	printf("************************\n");
	return (env);

	// multiple arg
}

t_env				*ft_getop(t_env *env, t_element *elm, char *ptr)
{
	int 			i;

	i = 0;
	printf("dakhala houna aydan\n");
	while (ptr[i])
	{
		if (!ft_isop(ptr[i]))
		{
			printf("3AFRIIIIT\n")	;
			if (!ft_get_instru(env, elm, ptr))
				return (NULL);
			else
				return (env);
		}
		i++;
	}
	return (NULL);
}

int 				ft_instru_tokenizer(t_env *env, t_element *elm, char *ptr)
{
	if (!(ft_getop(env, elm, ptr)))
		return (0);
	return (1);
}

int 				ft_syntax_analysis(t_env *env, t_element *elm, char *ptr)
{
	int 			i;
	//line nature
	i = 0;
	while (ptr[i])
	{
		if (!ft_islabel(ptr[i]))
		{
			if (ptr[i] == LABEL_CHAR)
			{
				if (!(ft_lbltokenizer(env, elm, ptr, i)))
					return (0);
				i++;
				break ;
			}
			else
				break ;
		}
		i++;
	}
	printf("LABEL%s\n",
			((t_symbol_tab*)((t_instru*)(elm->content))->sym_tab)->label);
	printf("LABEL PARSED\n");
	static int id;
	printf("labelparsed %d \n", id++);
	//check if comment or \n or op
	if (((t_instru*)(elm->content))->lbl_flg == 1)
	{
		printf("LABEL FOUND\n");
		if (ptr[i] == COMMENT_CHAR ||
				ptr[i] == ALT_COMMENT_CHAR || ptr[i] == '\n')
			return (1);
		else
		{
			printf("OP FOUND\n");
			if (!(ft_instru_tokenizer(env, elm, (ptr + i))))
			{
				//free last cash
				return (0);
			}
		}
	}
	else if (!(ft_instru_tokenizer(env, elm, ptr)))
	{
		printf("dakhala min houna \n");
		//free last cash
		return (0);
	}
	return (1);
}

t_env				*ft_scanner(t_env *env, t_element *elm, char *ptr)
{
	printf("SCAN\n");
	if (!(ft_syntax_analysis(env, elm, ptr)))
	{
		return (NULL);
	}
//	if (!(ft_line_symmantic_analysis()))
//	{
//		return (NULL);
//	}
	return (env);
}

t_env				*ft_instruparser(t_env *env)
{
	t_element		*elm;
	char 			*ptr;
	t_symbol_tab	*s_tab;

	elm = env->lines->head;
	while (elm)
	{
		if (!(ptr = ft_wsdel(((t_instru*)(elm->content))->buff)))
			return (NULL);
		printf("OPEN THE GATE\n|%s|\n", ptr);
		if (*ptr == COMMENT_CHAR ||
				*ptr == ALT_COMMENT_CHAR || *ptr == '\n')
		{
			elm = elm->next;
			continue ;
		}
		if (!(s_tab = (t_symbol_tab*)ft_memalloc(sizeof(t_symbol_tab))))
			return (NULL);
		((t_instru*)(elm->content))->sym_tab = s_tab;
		if (!(ft_scanner(env, elm, ptr)))
		{
			ft_strdel((char**)&ptr);
			return (NULL);
		}
	//	printf("%s\n%s\n%s\n%s\n", 
	//	((t_symbol_tab*)((t_instru*)(elm->content))->sym_tab)->op, 
	//	((t_symbol_tab*)((t_instru*)(elm->content))->sym_tab)->arg_1, 
	//	((t_symbol_tab*)((t_instru*)(elm->content))->sym_tab)->arg_2,
	//	((t_symbol_tab*)((t_instru*)(elm->content))->sym_tab)->arg_3);
		elm = elm->next;
	}
	return (env);
}
