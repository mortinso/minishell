/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 15:54:07 by mira              #+#    #+#             */
/*   Updated: 2023/10/19 15:51:49 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	unset_env(t_list **env, char *str)
{
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = *env;
	while (i < ft_lstsize(*env))
	{
		if (strcmp_nochr(str, (char *)tmp->data, '=') == 0
			|| ft_strcmp((char *)tmp->data, str) == 0)
		{
			list_remove(env, i);
			return ;
		}
		tmp = tmp->next;
		i++;
	}
}

void	unset_exp(t_list **exp, char *str)
{
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = *exp;
	while (i < ft_lstsize(*exp))
	{
		if (strcmp_nochr(str, (char *)tmp->data, '=') == 0
			|| ft_strcmp((char *)tmp->data, str) == 0)
		{
			list_remove(exp, i);
			return ;
		}
		tmp = tmp->next;
		i++;
	}
}

void	unset(t_list **env, t_list **exp, char **arr) //g_exit > 0 if a variable couldnt be unset (idk how?????)
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
		unset_env(env, buf);
		exp_buf = export_str(buf);
		unset_exp(exp, exp_buf);
		free(exp_buf);
		free(buf);
		i++;
	}
	g_exit = 0;
}
