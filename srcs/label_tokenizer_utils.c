/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label_tokenizer_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaddoul <afaddoul@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 21:07:51 by afaddoul          #+#    #+#             */
/*   Updated: 2020/03/12 21:07:51 by afaddoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int					check_label_instru(t_env *env, t_element *elm, char *ptr,
		int *i)
{
	while (ptr[*i])
	{
		if (!ft_islabel(ptr[*i]))
		{
			if (ptr[*i] == LABEL_CHAR)
			{
				if (!(ft_lbltokenizer(env, elm, ptr, *i)))
					return (0);
				(*i)++;
				break ;
			}
			else
				break ;
		}
		(*i)++;
	}
	return (1);
}

t_env				*ft_get_label(t_env *env, char *ptr, int *i)
{
	int				len;

	while (*i < 16)
	{
		if ((ft_strstr(ptr, g_op_tab[*i].op)))
		{
			if (!ft_strncmp(ptr, g_op_tab[*i].op, ft_strlen(g_op_tab[*i].op)))
			{
				len = ft_strlen(g_op_tab[*i].op);
				if (ptr[len] == 'r' || ptr[len] == DIRECT_CHAR ||
						ptr[len] == LABEL_CHAR ||
						ft_isdigit(ptr[len]) || ptr[len] == '-')
				{
					break ;
				}
			}
		}
		if (*i == 15)
		{
			ft_strdel((char**)&ptr);
			return (NULL);
		}
		(*i)++;
	}
	return (env);
}

int					ft_check_separators(char *str, int index)
{
	int				sep_nb;
	int				i;

	i = 0;
	sep_nb = 0;
	while (str[i])
	{
		if (str[i] == COMMENT_CHAR || str[i] == ALT_COMMENT_CHAR)
			break ;
		if (str[i] == SEPARATOR_CHAR)
			sep_nb++;
		i++;
	}
	if (sep_nb > (g_op_tab[index].arg_nb - 1))
		return (0);
	return (1);
}

int					ft_lbltokenizer(t_env *env, t_element *elm,
		char *ptr, int len)
{
	char			*str;
	t_label			*element;
	t_element		*label;

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
