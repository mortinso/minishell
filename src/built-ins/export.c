/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 16:31:09 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/11/22 14:43:24 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_list	**export_init(t_minishell *ms)
{
	int		i;
	char	*tmp;
	t_list	**exp;
	t_list	*node;
	t_list	*env_buf;

	i = 0;
	exp = (t_list **)malloc(sizeof(exp));
	*exp = NULL;
	env_buf = (*ms->env);
	while (i < ft_lstsize((*ms->env)))
	{
		tmp = export_str(env_buf->data);
		node = ft_lstnew(tmp);
		ft_lstadd_back(exp, node);
		env_buf = env_buf->next;
		i++;
	}
	list_sort(ms, exp);
	return (exp);
}

//Checks if export arguments are valid
int	export_error(t_minishell *ms, char *str)
{
	int	i;

	i = 0;
	if (ft_isdigit(str[0]) || str[0] == '=')
		return (export_error_msg(ms, str));
	while (i < (int)ft_strlen(str) && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (export_error_msg(ms, str));
		i++;
	}
	return (0);
}

// takes str and creates new string in specific format
// E.g.: str = ARG=123; -> new_str = declare -x ARG="123";
char	*export_str(char *str)
{
	int		i;
	int		j;
	int		size;
	char	*buf1;
	char	*buf2;

	i = 0;
	j = 0;
	size = ft_strlen(str);
	buf1 = ft_calloc(size + 3, sizeof(char));
	while (str[i] && str[i] != '=')
		buf1[j++] = str[i++];
	buf1[j++] = str[i++];
	buf1[j++] = '\"';
	while (i < size)
		buf1[j++] = str[i++];
	buf1[j] = '\"';
	buf2 = ft_strjoin("declare -x ", buf1);
	free(buf1);
	return (buf2);
}

//Checks if there is alredy str in export list;
int	export_override(char *str, t_list **export)
{
	char	*buf;
	t_list	*tmp;

	tmp = *export;
	buf = export_str(str);
	while (tmp)
	{
		if (!ft_strchr(buf, '=') && strcmp_nochr(buf, tmp->data, '=') == 0)
			break ;
		if (strcmp_chr(tmp->data, buf, '=') == 0 || (!ft_strchr(tmp->data, '=') \
			&& strcmp_nochr(tmp->data, buf, '=') == 0))
		{
			free(tmp->data);
			tmp->data = ft_strdup(buf);
			break ;
		}
		tmp = tmp->next;
	}
	free(buf);
	if (!tmp)
		return (0);
	return (1);
}

void	export(t_minishell *ms, char **arr)
{
	int		i;
	t_list	*node;

	i = 1;
	while (i < arr_size(arr))
	{
		if (export_error(ms, arr[i]))
		{
			i++;
			continue ;
		}
		env_override(arr[i], ms->env);
		if (export_override(arr[i], ms->exp) == 1)
		{
			i++;
			continue ;
		}
		node = ft_lstnew(export_str(arr[i]));
		ft_lstadd_back(ms->exp, node);
		i++;
	}
}
