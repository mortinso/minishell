/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built_ins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 16:55:30 by mortins-          #+#    #+#             */
/*   Updated: 2023/12/05 18:38:21 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_built_in(char *str)
{
	if (!str)
		return (0);
	if (ft_strcmp(str, "echo") == 0 || ft_strcmp(str, "cd") == 0
		|| ft_strcmp(str, "pwd") == 0 || ft_strcmp(str, "export") == 0
		|| ft_strcmp(str, "unset") == 0 || ft_strcmp(str, "env") == 0
		|| ft_strcmp(str, "exit") == 0)
		return (1);
	return (0);
}

void	exp_built_in(t_minishell *ms, char **cmd_args)
{
	if (ft_strcmp(cmd_args[0], "export") == 0)
	{
		list_sort(ms, ms->exp);
		if (arr_size(cmd_args) > 1)
			export(ms, cmd_args);
		else
			list_print(ms->exp);
	}
}

void	built_ins(t_minishell *ms, char **cmd_args, int parent)
{
	if (ft_strcmp(cmd_args[0], "echo") == 0)
		ft_echo(ms, cmd_args);
	else if (ft_strcmp(cmd_args[0], "cd") == 0)
		cd(ms, cmd_args);
	else if (ft_strcmp(cmd_args[0], "pwd") == 0)
		pwd(ms);
	else if (ft_strcmp(cmd_args[0], "exit") == 0)
		ft_exit(ms, cmd_args, parent);
	else if (ft_strcmp(cmd_args[0], "env") == 0)
		list_print(ms->env);
	else if (ft_strcmp(cmd_args[0], "unset") == 0)
		unset(ms, cmd_args);
	else if (ft_strcmp(cmd_args[0], "export") == 0)
		exp_built_in(ms, cmd_args);
}
