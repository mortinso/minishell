/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 16:34:23 by mortins-          #+#    #+#             */
/*   Updated: 2023/10/19 18:15:08 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	child(t_minishell *ms, t_cmdlist *cmd, int pos)
{
	pid_t	pid;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		{}//pipe error
	pid = fork();
	if (pid < 0)
		{}//fork error
	if (pid == 0)
	{
		redirect(ms, cmd->content, ms->main_arr, pos);
		if (!cmd->content->output && !cmd->content->append)
		{
			dup2(fd[1], STDOUT_FILENO);
			close(fd[0]);
			close(fd[1]);
		}
		exec();
	}
	else
	{
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[1]);
		close(pipe_fd[0]);
	}
}

char	**get_directories(t_list **env)
{
	t_list	*tmp;
	char	**paths;
	char	**path_dir;

	tmp = *env;
	while (tmp && strncmp(tmp->data, "PATH", 4) != 0)
		tmp = tmp->next;
	if (!tmp)
		return (NULL);
	paths = ft_split(tmp->data + 5, ':');
	path_dir = malloc(sizeof(char *) * (arr_size(paths) + 1));
	i = 0;
	while (i < arr_size(paths))
	{
		path_dir[i] = ft_strjoin(paths[i], "/");
		i++;
	}
	path_dir[i] = NULL;
	free_array(paths);
	return (path_dir);
}

char	*get_cmd_path(char **paths, char *cmd)
{
	char	*buf1;
	char	*buf2;
	int		i;

	i = 0;
	while (paths[i])
	{
		buf1 = ft_strjoin(paths[i], "/");
		buf2 = ft_strjoin(buf1, cmd);
		free(buf1);
		if (access(buf2, 0) == 0)
			return (buf2);
		free(buf2);
		i++;
	}
	ft_putstr_fd("Minishell: error: Command not found.\n", STDERR_FILENO);
	g_exit = 1;
	return (NULL);
}

void	exec(t_minishell *ms, char **cmd_arr)
{
	char	**paths;
	char	*cmd_path;

	if (is_built_in(ms, cmd_arr))
		free_ms(ms);
	paths = get_directories(ms->env);
	cmd_path = get_cmd_path(paths, cmd_arr[0]);
	free_array(paths);
	if (!cmd_path)
	{
		free(cmd_path);
		free(ms);
	}
	if (execve(cmd_path, cmd, envp) == -1)
	{
		free(cmd_path);
		g_exit = errno;
		free_ms(ms);
	}
}
