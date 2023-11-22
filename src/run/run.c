/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:01:57 by mortins-          #+#    #+#             */
/*   Updated: 2023/11/22 14:57:17 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	find_cmd_pos(char **main_arr, int pos)
{
	while (main_arr[pos] && main_arr[pos][0] && ft_strcmp(main_arr[pos], "|") \
		!= 0)
		pos++;
	if (main_arr[pos] && main_arr[pos][0] && ft_strcmp(main_arr[pos], "|") == 0)
		pos++;
	return (pos);
}

void	get_exit_status(t_minishell *ms, pid_t pid, int cmds_run)
{
	int	status;

	if (ms->cmd_count == 1 && is_built_in(ms->cmdlist->cmd_args[0]) \
		== 1)
	{
		wait(&status);
		reset_fds(ms);
		return ;
	}
	while (cmds_run > 0)
	{
		wait(&status);
		if (pid != -1 && WIFEXITED(status))
			ms->exit = WEXITSTATUS(status);
		if (pid != -1 && WIFSIGNALED(status))
			g_sig = WTERMSIG(status);
		else
			g_sig = 0;
		cmds_run--;
	}
	reset_fds(ms);
}

void	run(t_minishell *ms)
{
	int		pipe_fd[2];
	int		cmds_run;
	int		pos;
	pid_t	pid;

	cmds_run = 0;
	pos = 0;
	if (!ms->cmdlist)
		return ;
	signal(SIGQUIT, signal_process_interrupt);
	while (cmds_run < ms->cmd_count)
	{
		if (pipe(pipe_fd) < 0)
			pipe_error(ms);
		pid = fork();
		if (pid < 0)
			fork_error(ms);
		if (pid == 0)
			child(ms, pipe_fd, cmds_run, pos);
		else
			parent(ms, pipe_fd, cmds_run, pos);
		pos = find_cmd_pos(ms->main_arr, pos);
		cmds_run++;
	}
	get_exit_status(ms, pid, cmds_run);
}

void	child(t_minishell *ms, int *pipe_fd, int cmds_run, int pos)
{
	t_cmdlist	*cmd;
	int			i;

	cmd = ms->cmdlist;
	i = cmds_run;
	while (i > 0)
	{
		cmd = cmd->next;
		i--;
	}
	if (cmds_run != 0)
	{
		dup2(ms->cmd_in_fd, STDIN_FILENO);
		close(ms->cmd_in_fd);
	}
	if (cmds_run < ms->cmd_count - 1)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
	if (ms->cmd_count == 1 && is_built_in(cmd->cmd_args[0]))
		exit(ms->exit);
	redirect(ms, ms->main_arr, pos, 1);
	exec(ms, cmd->cmd_args);
}

void	parent(t_minishell *ms, int *pipe_fd, int cmds_run, int pos)
{
	t_cmdlist	*cmd;
	int			i;

	cmd = ms->cmdlist;
	i = cmds_run;
	while (i-- > 0)
		cmd = cmd->next;
	if (ms->cmd_count == 1)
	{
		if (is_built_in(cmd->cmd_args[0]))
		{
			if (redirect(ms, ms->main_arr, pos, 0) == 0)
				built_ins(ms, cmd->cmd_args);
		}
	}
	if (cmds_run > 0)
		close(ms->cmd_in_fd);
	if (cmds_run < ms->cmd_count - 1)
	{
		close(pipe_fd[1]);
		ms->cmd_in_fd = pipe_fd[0];
	}
	signal(SIGINT, signal_process_interrupt);
}
