/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analys.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaddoul <afaddoul@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 21:07:52 by afaddoul          #+#    #+#             */
/*   Updated: 2020/03/12 21:07:52 by afaddoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int					ft_argtokenizer(t_element *elm, char *str, t_ptrs ptrs)
{
	int				i;
	int				len;
	char			*arg;

	i = 0;
	len = ptrs.end - ptrs.start;
	if (!(arg = ft_strsub(str, ptrs.start, len)))
		return (0);
	if (!ft_arg_filler(elm, arg))
		return (0);
	return (1);
}

int					ft_argscanner(t_element *elm, char *str, int index)
{
	int				i;
	int				j;
	t_ptrs			ptrs;

	i = -1;
	j = 0;
	if (!(ft_check_separators(str, index)))
		return (0);
	while (str[++i])
	{
		if (str[i] == 'r' || str[i] == DIRECT_CHAR || str[i] == LABEL_CHAR ||
				ft_isdigit(str[i]) || str[i] == '-')
		{
			j = i;
			ptrs.start = j;
			if (!(ft_tokenize_arg(&ptrs, elm, str, &i)))
				return (0);
		}
		if (str[i] == '\n' || str[i] == COMMENT_CHAR ||
				str[i] == ALT_COMMENT_CHAR)
			break ;
	}
	if (!SYM_TAB->arg_1)
		return (0);
	return (1);
}

t_env				*ft_get_instru(t_env *env, t_element *elm, char *str)
{
	int				i;
	int				index;
	char			*ptr;

	i = 0;
	if (!(ptr = ft_wsdel(str)))
		return (NULL);
	if (!(ft_get_label(env, ptr, &i)))
		return (0);
	if (!(SYM_TAB->op = ft_strdup(g_op_tab[i].op)))
	{
		ft_strdel((char**)&ptr);
		return (NULL);
	}
	index = i;
	i = ft_strlen(g_op_tab[i].op);
	((t_instru*)(elm->content))->op_flg = 1;
	if (!(ft_argscanner(elm, ptr + i, index)))
	{
		ft_strdel((char**)&ptr);
		return (NULL);
	}
	ft_strdel((char**)&ptr);
	return (env);
}

int					ft_instru_tokenizer(t_env *env, t_element *elm, char *ptr)
{
	if (!(ft_getop(env, elm, ptr)))
		return (0);
	return (1);
}

int					ft_syntax_analys(t_env *env, t_element *elm, char *ptr)
{
	int				i;

	i = 0;
	if (!(check_label_instru(env, elm, ptr, &i)))
		return (0);
	if (((t_instru*)(elm->content))->lbl_flg == 1)
	{
		while (ptr[i] == 9 || ptr[i] == 32)
			i++;
		if (ptr[i] == COMMENT_CHAR ||
				ptr[i] == ALT_COMMENT_CHAR || ptr[i] == '\n')
			return (1);
		else
		{
			if (!(ft_instru_tokenizer(env, elm, (ptr + i))))
				return (0);
		}
	}
	else if (!(ft_instru_tokenizer(env, elm, ptr)))
		return (0);
	return (1);
}
