/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 14:37:46 by mortins-          #+#    #+#             */
/*   Updated: 2023/10/19 18:14:37 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	find_cmd_pos(char **main_arr, int pos)
{
	while (main_arr[pos] && main_arr[pos][0] && ft_strcmp(main_arr[pos][0], "|"\
		) != 0)
		pos++;
	if (main_arr[pos] && main_arr[pos][0] && ft_strcmp(main_arr[pos][0], "|") \
		== 0)
		pos++;
	return (pos);
}

int	run(t_minishell *ms)
{
	t_cmdlist	*tmp;
	int			pos;
	pid_t		pid;
	int			status;

	tmp = ms->cmdlist;
	pos = 0;
	pid = fork();
	if (pid < 0)
		{}//fork error
	if (pid == 0 && ms->cmd_count == 1)
	{
		redirect(ms, tmp->content, ms->main_arr, pos);
		exec(ms, tmp->content->cmd_flags)
	}
	else if (pid == 0)
	{
		while (cmd_run < cmd_count)
		{
			child(ms, tmp->content, pos);
			pos = find_cmd_pos(ms->main_arr, pos);
			tmp = tmp->next;
		}
		redirect(ms, tmp->content, ms->main_arr, pos);
		exec(ms, tmp->content->cmd_flags)
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_exit = WEXITSTATUS(status);
	return ;
}
