/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 17:08:39 by mortins-          #+#    #+#             */
/*   Updated: 2023/10/06 12:30:12 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*find_home(t_list **env)
{
	t_list	*tmp;
	char	*buf;

	buf = NULL;
	tmp = *env;
	while (tmp)
	{
		if (ft_strncmp((char *)tmp->data, "HOME=", 5) == 0)
		{
			buf = ft_strtrim((char *)tmp->data, "HOME=");
			return (buf);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

void	cd_home(t_minishell *ms)
{
	char	*buf;

	buf = find_home(ms->env);
	if (!buf)
	{
		free(buf);
		write(2, "Minishell: cd: HOME is undefined\n", 29);
		g_exit = 1;
	}
	else if (chdir(buf) != 0)
	{
		free(buf);
		perror("Minishell: cd: HOME");
		g_exit = 1;
	}
	g_exit = 0;
}

void	cd(t_minishell *ms, char **path)
{
	if (path && arr_size(path) > 2)
	{
		write(2, "Minishell: cd: too many arguments\n", 34);
		g_exit = 1;
	}
	else if (!path || !path[1] || !path[1][0])
		return (cd_home(ms));
	else if (chdir(path[1]) != 0)
	{
		perror("Minishell: cd");
		g_exit = 1;
	}
	else
		g_exit = 0;
}
