/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 19:09:33 by mortins-          #+#    #+#             */
/*   Updated: 2023/11/01 17:15:08 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_exec(char *cmd, char **paths)
{
	int		i;
	char	*buf;
	char	*buf2;

	i = 0;
	if (!paths)
		return (1);
	while (paths[i])
	{
		buf = ft_strjoin(paths[i++], "/");
		buf2 = ft_strjoin(buf, cmd);
		free(buf);
		if (access(buf2, F_OK) == 0)
			return (is_usable(cmd, buf2, paths));
		free(buf2);
	}
	return (1);
}

int	is_usable(char	*cmd, char *cmd_path, char **paths_array)
{
	struct stat	path_stat;

	stat(cmd_path, &path_stat);
	if (S_ISDIR(path_stat.st_mode) != 0)
	{
		ft_putstr_fd("Minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
		g_exit = 126;
	}
	else if (access(cmd_path, X_OK) == 0)
	{
		free(cmd_path);
		return (1);
	}
	else if (access(cmd_path, X_OK) != 0)
	{
		perror("Minishell: error: ");
		g_exit = 126;
	}
	else
		g_exit = 1;
	free(cmd_path);
	free_array(paths_array);
	return (0);
}
