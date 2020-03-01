/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   code_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 21:53:42 by ada               #+#    #+#             */
/*   Updated: 2020/03/01 19:11:10 by ada              ###   ########.fr       */
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

char				*ft_intrucpy(char *ptr, char *dest)
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
	while (ptr[i])
	{
		if (ptr[i] == 9 || ptr[i] == 32)
			counter++;
		i++;
	}
	len = ft_strlen(ptr) - counter;
	if (!(dest = (char*)ft_memalloc(sizeof(char) * (len + 1))))
		return (NULL);
	dest = ft_instrucpy(ptr, dest);
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

char 				*ft_getop(char *ptr)
{
	int 			i;

	i = 0;
	while (ptr[i])
	{
		if (!ft_isop(ptr[i]))
		{
			if (ft_get_instru())
		}
			i++;
	}
	return (NULL);
}

int 				ft_intru_tokenizer(t_env *env, t_element *elm, char *ptr,
		int len)
{
	if (!(ft_getop(ptr)))
		return (0);
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
	//check if comment or \n or op
	if (((t_instru*)(elm->content))->lbl_flg == 1)
	{
		if (ptr[i] == COMMENT_CHAR ||
				ptr[i] == ALT_COMMENT_CHAR || ptr[i] == '\n')
			return (1);
		else
		{
			if (!(ft_instru_tokenizer(env, elm, ptr, i)))
			{
				//free last cash
				return (0);
			}
		}
	}
	if (!(ft_instru_tokenizer(env, elm, ptr, 0)))
	{
		//free last cash
		return (0);
	}
	return (1);
}

t_env				*ft_scanner(t_env *env, t_element *elm, char *ptr)
{
	if (!(ft_syntax_analysis()))
	{
		return (NULL);
	}
	if (!(ft_line_symmantic_analysis()))
	{
		return (NULL);
	}
	return (env);
}

t_env				*parser(t_env *env)
{
	t_element		*elm;
	char 			*ptr;

	elm = env->lines->head;
	while (elm)
	{
		if (!(ptr = ft_wsdel(((t_instru*)(elm->content))->buff)))
			return (NULL);
		if (*ptr == COMMENT_CHAR ||
				*ptr == ALT_COMMENT_CHAR || *ptr == '\n')
		{
			elm = elm->next;
			continue ;
		}
		if (!(ft_scanner(env, , ptr)))
		{
			ft_strdel((char**)&ptr);
			return (NULL);
		}
		elm = elm->next;
	}
	return (env);
}
