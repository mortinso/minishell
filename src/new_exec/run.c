/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 14:37:46 by mortins-          #+#    #+#             */
/*   Updated: 2023/10/20 16:56:17 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	reset_fds(t_minishell *ms)
{
	dup2(ms->fdout_buf, STDOUT_FILENO);
	close(ms->fdout_buf);
	dup2(ms->fdin_buf, STDIN_FILENO);
	close(ms->fdin_buf);
}

int	find_cmd_pos(char **main_arr, int pos)
{
	while (main_arr[pos] && main_arr[pos][0] && ft_strcmp(main_arr[pos], "|") !=\
		0)
		pos++;
	if (main_arr[pos] && main_arr[pos][0] && ft_strcmp(main_arr[pos], "|") == 0)
		pos++;
	return (pos);
}

void	run(t_minishell *ms)
{
	t_cmdlist	*tmp;
	int			pos;
	pid_t		pid;
	int			status;
	int			cmd_run;
	int			cmd_num;

	tmp = ms->cmdlist;
	cmd_num = ms->cmd_count;
	if (!tmp)
		return ;
	cmd_run = 0;
	pos = 0;
	pid = fork();
	if (pid < 0)
		{}//fork error
	if (pid == 0 && ms->cmd_count == 1)
	{
		redirect(tmp->content, ms->main_arr, pos);
		exec(ms, tmp->content->cmd_flags);
	}
	else if (pid == 0 && ms->cmd_count > 1)
	{
		while (cmd_run < ms->cmd_count - 1)
		{
			child(ms, tmp, pos);
			pos = find_cmd_pos(ms->main_arr, pos);
			tmp = tmp->next;
			cmd_run++;
		}
		redirect(tmp->content, ms->main_arr, pos);
		exec(ms, tmp->content->cmd_flags);
	}
	while (cmd_num > 0)
	{
		wait(&status);
		if (pid != -1 && WIFEXITED(status))
			g_exit = WEXITSTATUS(status);
		cmd_num--;
	}
	reset_fds(ms);
}
