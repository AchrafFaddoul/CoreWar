/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   code_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 21:53:42 by ada               #+#    #+#             */
/*   Updated: 2020/03/02 11:51:19 by ada              ###   ########.fr       */
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
	if (!(arg = ft_strsub(str, start, i)))
		return (-1);
	if (arg_nb == 1)
		SYM_TAB->arg_1 = arg;
	else if (arg_nb == 2)
		SYM_TAB->arg_2 = arg;
	else if (arg_nb == 3)
		SYM_TAB->arg_3 = arg;
	return (i);
}

int 				ft_argscanner(t_element *elm, char *str, int index)
{
	int				i;
	int 			calls_nb;

	i = 0;
	calls_nb = 0;
	while (str[i])
	{
		if (str[i] == 'r' || str[i] == DIRECT_CHAR ||
				ft_isdigit(str[i]) || str[i] == '-')
		{
			calls_nb++;
			if ((index >= g_op_tab[index].arg_nb) ||
					((i = ft_argtokenizer(elm, str, i, calls_nb)) == -1))
			{
				ft_strdel((char**)&(SYM_TAB->op));
				ft_strdel((char**)&(SYM_TAB->arg_1));
				ft_strdel((char**)&(SYM_TAB->arg_2));
				ft_strdel((char**)&(SYM_TAB->arg_3));
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
		if ((ft_strstr(str, g_op_tab[i].op)))
			break ;
			if (i == 15)
				return (NULL);
		i++;
	}
	if (!(SYM_TAB->op = ft_strdup(g_op_tab[i].op)))
		return (NULL);
	//get args
	index = i;
	i += ft_strlen(g_op_tab[i].op);
	// one arg 
	if (!(ft_argscanner(elm, str + i, index)))
		return (NULL);
	return (env);

	// multiple arg
}

t_env				*ft_getop(t_env *env, t_element *elm, char *ptr)
{
	int 			i;

	i = 0;
	while (ptr[i])
	{
		if (!ft_isop(ptr[i]))
		{
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
	printf("syntax anal in\n");
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
	printf("LABEL PARSED\n");
	int id = 1;
	printf("labelparsed %d \n", id++);
	//check if comment or \n or op
	if (((t_instru*)(elm->content))->lbl_flg == 1)
	{
		if (ptr[i] == COMMENT_CHAR ||
				ptr[i] == ALT_COMMENT_CHAR || ptr[i] == '\n')
			return (1);
		else
		{
			if (!(ft_instru_tokenizer(env, elm, (ptr + i))))
			{
				//free last cash
				return (0);
			}
		}
	}
	if (!(ft_instru_tokenizer(env, elm, ptr)))
	{
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

	elm = env->lines->head;
	while (elm)
	{
		if (!(ptr = ft_wsdel(((t_instru*)(elm->content))->buff)))
			return (NULL);
		printf("OPEN THE GATE\n%s\n", ptr);
		if (*ptr == COMMENT_CHAR ||
				*ptr == ALT_COMMENT_CHAR || *ptr == '\n')
		{
			elm = elm->next;
			continue ;
		}
		if (!(ft_scanner(env, elm, ptr)))
		{
			ft_strdel((char**)&ptr);
			return (NULL);
		}
		elm = elm->next;
	}
	return (env);
}
