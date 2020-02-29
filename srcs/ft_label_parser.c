/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_label_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 15:43:20 by ada               #+#    #+#             */
/*   Updated: 2020/02/29 04:09:47 by ada              ###   ########.fr       */
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

static t_label		*ft_labelnew(char *token)
{
	t_label 		*elm;

	if (!(elm = (t_label*)ft_memalloc(sizeof(t_label))))
		return (NULL);
	elm->label = token;
	return (elm);
}

t_element 			*ft_labelpush(t_env *env, char **label)
{
	t_element		*elm;
	t_label			*lbl;

	if (!(lbl = ft_labelnew(*label)))
	{
		ft_strdel((char**)label);
		return (NULL);
	}
	if (!(elm = ft_elemnew(lbl)))
	{
		ft_strdel((char**)label);
		ft_memdel((void**)&lbl);
		return (NULL);
	}
	ft_dlstpush(env->labels, elm);
	return (elm);
}

char 				*ft_label_tokenizer(char *ptr, int start, int end)
{
	char 			*token;
	int 			len;
	int				i;

	i = 0;
	len = end - start + 1;
	if (!(token = ft_strsub(ptr, start, len)))
		return (NULL);
	while (token[i])
	{
		if (!ft_islabel(token[i]))
		{
			ft_strdel((char**)&token);
			return (NULL);
		}
		i++;
	}
	return (token);
}

t_env				*ft_label_scanner(t_env *env, const char *ptr)
{
	char 			*label;
	int 			i;
	int 			j;

	i = 0;
	j = 0;
	while (ptr[i])
	{
		if (ptr[i] == LABEL_CHAR)
		{
			if (!(label = ft_label_tokenizer(ptr, j, i)))
			{
				ft_strdel((char**)&label);
				return (NULL);
			}
			if (!(ft_labelpush(env, &label)))
				return (NULL);
			while (ptr[i] && (ptr[i] == 9 || ptr[i] == 32))
				i++;
			if (ptr[i] == COMMENT_CHAR || ptr[i] == ALT_COMMENT_CHAR ||
					ptr[i] == '\n')
				break ;
			j = i + 1;
		}
		i++;
	}
	return (env);
}

t_env 				*ft_label_parser(t_env *env)
{
	t_element		*elm;
	static size_t	index;
	char 			*ptr;
	int 			ws_counter;
	int 			i;

	elm = env->lines->head;
	while (elm)
	{
		i = 0;
		if (*(ptr + i) == COMMENT_CHAR ||
				*(ptr + i) == ALT_COMMENT_CHAR || *(ptr + i) == '\n')
		{
			elm = elm->next;
			continue ;
		}
		elm->index = ++index;
		while (ptr[i] && (ptr[i] == 9 || ptr[i] == 32))
			i++;
		ws_counter = i;
		while (ptr[i])
		{
			if (ptr[i] == LABEL_CHAR)
			{
				if (!(ft_label_scanner(env, (ptr + ws_counter)))
						return (destroy_labels(env));
				break ;
			}
			i++;
		}
		if (!ptr[i])
			elm->op_flg = 1;
		elm = elm->next;
	}
}
