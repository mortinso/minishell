/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 17:08:39 by mortins-          #+#    #+#             */
/*   Updated: 2023/10/11 17:41:31 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	cd_home(t_minishell *ms)
{
	char	*buf;

	buf = env_var_str("HOME", ms->env);
	if (!buf)
	{
		write(2, "Minishell: cd: HOME is undefined\n", 29);
		g_exit = 1;
	}
	else if (chdir(buf) != 0)
	{
		perror("Minishell: cd: HOME");
		g_exit = 1;
	}
	else
		g_exit = 0;
	if (buf)
		free(buf);
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
