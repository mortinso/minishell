/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 11:22:20 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/10/06 15:29:32 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*path_str(t_list *env)
{
	t_list	*tmp;

	tmp = env;
	while (tmp->data)
	{
		if (ft_strncmp((char *)tmp->data, "PATH=", 5) == 0)
			break ;
		tmp = tmp->next;
	}
	if (!tmp)
		return (NULL);
	return (tmp->data);
}

char	**path_init(t_minishell *ms)
{
	int		i;
	char	**paths;
	char	*env_path;
	char	**path_dir;
	char	*env_path_str;

	env_path_str = path_str(*ms->env);
	env_path = ft_strtrim(env_path_str, "PATH=");
	paths = ft_split(env_path, ':');
	path_dir = malloc(sizeof(char *) * (arr_size(paths) + 1));
	i = 0;
	while (i < arr_size(paths))
	{
		path_dir[i] = ft_strjoin(paths[i], "/");
		i++;
	}
	path_dir[i] = NULL;
	free(env_path);
	free_array(paths);
	return (path_dir);
}

char	*is_exec(char *str, char **paths)
{
	int		i;
	char	*buf;

	i = 0;
	while (paths[i])
	{
		buf = ft_strjoin(paths[i], str);
		if (!access(buf, F_OK))
			return (buf);
		free(buf);
		i++;
	}
	return (NULL);
}

int	is_built_in(char *str)
{
	if (ft_strcmp(str, "echo") == 0 || ft_strcmp(str, "cd") == 0 
		|| ft_strcmp(str, "pwd") == 0 || ft_strcmp(str, "export") == 0
		|| ft_strcmp(str, "unset") == 0 || ft_strcmp(str, "env") == 0 
		|| ft_strcmp(str, "exit") == 0)
		return (1);
	return (0);
}

void	built_ins(t_minishell *ms, char **cmd_flags)
{
	if (ft_strcmp(cmd_flags[0], "echo") == 0)
		echo(cmd_flags);
	if (ft_strcmp(cmd_flags[0], "cd") == 0)
		cd(ms, cmd_flags);
	if (ft_strcmp(cmd_flags[0], "pwd") == 0)
		pwd();
	if (ft_strcmp(cmd_flags[0], "exit") == 0)
	{
		free_array(ms->paths);
		ft_exit(ms, cmd_flags);
	}
}

void	exp_env_unset(t_minishell *ms, char **cmd_flags)
{
	if (ft_strcmp(cmd_flags[0], "export") == 0)
	{
		list_sort(ms->exp);
		if (export_error(cmd_flags))
			return ;
		if (arr_size(cmd_flags) > 1)
			export(cmd_flags, ms->exp, ms->env);
		else
			list_print(ms->exp);
	}
	if (ft_strcmp(cmd_flags[0], "unset") == 0)
	{
		if (arr_size(cmd_flags) > 1)
			unset(ms->env, ms->exp, cmd_flags);
	}
	if (ft_strcmp(cmd_flags[0], "env") == 0)
		list_print(ms->env);
}

int	last_cmd(t_minishell *ms, t_cmdlist *cmdlist, int i)
{
	pid_t	child;

	if (cmdlist)
	{
		exp_env_unset(ms, cmdlist->content->cmd_flags);
		if (redir_check_out(cmdlist->content, ms->main_arr, i)
			|| redir_check_in(cmdlist->content, ms->main_arr, i))
		{
			redir_in(cmdlist->content, ms->main_arr, i);
			redir_out(cmdlist->content, ms->main_arr, i);
		}
		child = fork();
		if (child == 0 && !is_built_in(cmdlist->content->cmd_flags[0]))
			exec(ms, cmdlist);
		else if (child == 0)
			exit (0);
		else
		{
			wait(NULL);
			if (is_built_in(cmdlist->content->cmd_flags[0]))
				built_ins(ms, cmdlist->content->cmd_flags);
		}
	}
	return (0);
}
