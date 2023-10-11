/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 13:48:41 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/10/05 14:53:44 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**list_to_array(t_list **env)
{
	int		i;
	int		size;
	t_list	*tmp;
	char	**buf;

	i = 0;
	tmp = *env;
	size = ft_lstsize(tmp);
	buf = malloc(sizeof(char *) * (size + 1));
	while (tmp && i < size)
	{
		buf[i] = ft_strdup((char *)tmp->data);
		tmp = tmp->next;
		i++;
	}
	buf[i] = 0;
	return (buf);
}

void	exec(t_minishell *ms, t_cmdlist *cmdlist)
{
	char		**env_arr;
	char		*cmd_path;

	cmd_path = NULL;
	env_arr = list_to_array(ms->env);
	if (!is_built_in(cmdlist->content->cmd_flags[0]))
		cmd_path = is_exec(cmdlist->content->cmd_flags[0], ms->paths);
	else
	{
		built_ins(ms, cmdlist->content->cmd_flags);
		free_array(env_arr);
		exit (0);
	}
	if (cmd_path
		&& execve(cmd_path, cmdlist->content->cmd_flags, env_arr) == -1)
		perror("EXECVE ERROR\n");
	free_array(env_arr);
	free(cmd_path);
	exit(0);
}

void	child_process(t_minishell *ms, t_cmdlist *cmdlist, int *pipe_fd, int i)
{
	if (redir_check_out(cmdlist->content, ms->main_arr, i))
	{
		redir_in(cmdlist->content, ms->main_arr, i);
		redir_out(cmdlist->content, ms->main_arr, i);
	}
	else
	{
		redir_in(cmdlist->content, ms->main_arr, i);
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
	}
	exec(ms, cmdlist);
}

void	parent_process(int *pipe_fd)
{
	close(pipe_fd[1]);
	wait(NULL);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
}
