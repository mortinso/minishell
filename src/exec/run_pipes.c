/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_pipes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 13:28:56 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/10/06 14:37:24 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_pipe(t_minishell *ms, t_cmdlist *cmdlist, int i)
{
	pid_t	child;
	int		pipe_fd[2];

	if (pipe(pipe_fd) < 0)
	{
		printf("Pipe error\n");
		return (1);
	}
	child = fork();
	if (child == -1)
		return (printf("Fork Error\n"));
	if (child == 0)
		child_process(ms, cmdlist, pipe_fd, i);
	else
		parent_process(pipe_fd);
	return (1);
}

int	run_pipes(t_minishell *ms, t_cmdlist *cmdlist, int i)
{
	ft_pipe(ms, cmdlist, i);
	while (ms->main_arr[i] && ft_strcmp(ms->main_arr[i], "|") != 0)
		i++;
	i++;
	return (i);
}

int	no_pipe(t_minishell *ms, t_cmdlist *cmdlist)
{
	pid_t	child;

	redir_in(cmdlist->content, ms->main_arr, 0);
	redir_out(cmdlist->content, ms->main_arr, 0);
	child = fork();
	if (child == 0)
	{
		if (!is_built_in(cmdlist->content->cmd_flags[0]))
			exec(ms, cmdlist);
		exit (0);
	}
	else
	{
		wait(NULL);
		if (is_built_in(cmdlist->content->cmd_flags[0]))
			built_ins(ms, cmdlist->content->cmd_flags);
		set_fd(ms);
	}
	return (0);
}

int	run(t_minishell *ms)
{
	int			i;
	int			cmds;
	t_cmdlist	*tmp;

	i = 0;
	tmp = ms->cmdlist;
	cmds = ms->cmd_count;
	ms->paths = path_init(ms);
	if (cmds == 1) //if there isn't a pipe
	{
		no_pipe(ms, tmp);
		free_array(ms->paths);
		return (0);
	}
	while (cmds > 1 && cmds-- > 0 && tmp->next) //if there's a pipe
	{
		i += run_pipes(ms, tmp, i);
		tmp = tmp->next;
	}
	last_cmd(ms, tmp, i);
	set_fd(ms);
	return (free_array(ms->paths));
}
