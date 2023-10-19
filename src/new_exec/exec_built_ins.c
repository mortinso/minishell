/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built_ins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:43:48 by mortins-          #+#    #+#             */
/*   Updated: 2023/10/19 16:00:07 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_builtin(char *str)
{
	if (ft_strcmp(str, "echo") == 0 || ft_strcmp(str, "cd") == 0 \
		|| ft_strcmp(str, "pwd") == 0 || ft_strcmp(str, "export") == 0 \
		|| ft_strcmp(str, "unset") == 0 || ft_strcmp(str, "env") == 0 \
		|| ft_strcmp(str, "exit") == 0)
		return (1);
	return (0);
}

void	exp_built_in(t_minishell *ms, char *cmd_arr)
{
	if (ft_strcmp(cmd_flags[0], "export") == 0) //Check if this makes sense
	{
		list_sort(ms->exp);
		if (export_error(cmd_flags))
		{
			g_exit = 1;
			return ;
		}
		if (arr_size(cmd_flags) > 1)
			export(cmd_flags, ms->exp, ms->env);
		else
			list_print(ms->exp);
	}
}

void	built_ins(t_minishell *ms, char **cmd_arr, int exit)
{
	if (ft_strcmp(cmd_arr[0], "echo") == 0)
		echo(cmd_arr);
	else if (ft_strcmp(cmd_arr[0], "cd") == 0)
		cd(ms, cmd_arr);
	else if (ft_strcmp(cmd_arr[0], "pwd") == 0)
		pwd();
	else if (ft_strcmp(cmd_arr[0], "exit") == 0) //WRONG
	{
		if (exit) //WRONG
			write(STDERR_FILENO, "exit\n", 5);//WRONG
		ft_exit(ms, cmd_arr, exit);//WRONG
		if (exit) //WRONG
		{
			free_array(ms->paths);//WRONG
			free_ms(ms);//WRONG
		}
	}
	else if (ft_strcmp(cmd_arr[0], "env") == 0)
		list_print(ms->env);
	else if (ft_strcmp(cmd_flags[0], "unset") == 0)
		unset(ms->env, ms->exp, cmd_flags);
	else
		exp_built_in(ms, cmd_arr);
}
