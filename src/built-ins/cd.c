/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 17:08:39 by mortins-          #+#    #+#             */
/*   Updated: 2023/12/07 12:49:23 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	cd_home(t_minishell *ms)
{
	char	*home;

	home = ft_strtrim(var_str(*ms->env, "HOME="), "HOME=");
	if (!home)
	{
		write(2, "Minishell: cd: HOME is undefined\n", 29);
		exit (1);
	}
	else if (chdir(home) != 0)
	{
		perror("Minishell: cd: HOME");
		exit (1);
	}
	else
		ms->exit = 0;
	if (home)
		free(home);
}

void	cd_env(t_minishell *ms, char *old_pwd)
{
	char	pwd[PATH_MAX + 1];
	char	**var;

	var = malloc(sizeof(char *) * 4);
	if (!var)
		malloc_error(ms);
	ft_bzero(pwd, PATH_MAX + 1);
	getcwd(pwd, sizeof(pwd));
	var[0] = ft_strdup("export");
	var[1] = ft_strjoin("PWD=", pwd);
	var[2] = ft_strjoin("OLDPWD=", old_pwd);
	var[3] = NULL;
	export(ms, var);
	free_array(var);
	ft_bzero(old_pwd, ft_strlen(old_pwd));
	ft_bzero(pwd, ft_strlen(pwd));
}

void	cd(t_minishell *ms, char **path)
{
	char	old_pwd[PATH_MAX + 1];

	ft_bzero(old_pwd, PATH_MAX + 1);
	getcwd(old_pwd, sizeof(old_pwd));
	if (path && arr_size(path) > 2)
	{
		write(2, "Minishell: cd: too many arguments\n", 34);
		ft_bzero(old_pwd, ft_strlen(old_pwd));
		ms->exit = 1;
		return ;
	}
	else if (!path || !path[1] || !path[1][0])
		cd_home(ms);
	else if (chdir(path[1]) != 0)
	{
		perror("Minishell: cd");
		ms->exit = 1;
		return ;
	}
	else
		ms->exit = 0;
	cd_env(ms, old_pwd);
}
