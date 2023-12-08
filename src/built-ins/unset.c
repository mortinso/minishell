/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 15:54:07 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/12/08 14:46:58 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	unset_list(t_list **lst, char *str)
{
	int		i;
	int		size;
	t_list	*tmp;

	i = 0;
	tmp = *lst;
	size = ft_lstsize(*lst);
	while (i < size)
	{
		if (strcmp_nochr(str, (char *)tmp->data, '=') == 0
			|| ft_strcmp((char *)tmp->data, str) == 0)
		{
			list_remove(lst, i);
			return ;
		}
		tmp = tmp->next;
		i++;
	}
}

//ms->exit > 0 if a variable couldnt be unset (idk how?????)
void	unset(t_minishell *ms, char **arr)
{
	int		i;
	int		size;
	char	*buf;
	char	*exp_buf;

	i = 1;
	size = arr_size(arr);
	while (i < size)
	{
		buf = ft_strdup(arr[i]);
		unset_list(ms->env, buf);
		exp_buf = export_str(buf);
		unset_list(ms->exp, exp_buf);
		free(exp_buf);
		free(buf);
		i++;
	}
	ms->exit = 0;
}
