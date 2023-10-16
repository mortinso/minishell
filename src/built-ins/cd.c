/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 17:08:39 by mortins-          #+#    #+#             */
/*   Updated: 2023/10/13 17:04:05 by mortins-         ###   ########.fr       */
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
		g_exit = 1;
	}
	else if (chdir(home) != 0)
	{
		perror("Minishell: cd: HOME");
		g_exit = 1;
	}
	else
		g_exit = 0;
	if (home)
		free(home);
}

void	cd_env(t_minishell *ms, char *old_pwd)
{
	char	pwd[PATH_MAX + 1];
	char	**var;
	int		i;

	i = 0;
	var = malloc(sizeof(char *) * 4);
	getcwd(pwd, sizeof(pwd));
	var[0] = ft_strdup("export");
	var[1] = ft_strjoin("PWD=", pwd);
	var[2] = ft_strjoin("OLDPWD=", old_pwd);
	var[3] = NULL;
	export(var, ms->exp, ms->env);
	free_array(var);
	while (old_pwd[i])
		old_pwd[i++] = 0;
	while (pwd[i])
		pwd[i++] = 0;
}

void	cd(t_minishell *ms, char **path)
{
	char	old_pwd[PATH_MAX + 1];
	int		i;

	i = 0;
	getcwd(old_pwd, sizeof(old_pwd));
	if (path && arr_size(path) > 2)
	{
		write(2, "Minishell: cd: too many arguments\n", 34);
		g_exit = 1;
		while (old_pwd[i])
			old_pwd[i++] = 0;
		return ;
	}
	else if (!path || !path[1] || !path[1][0])
		cd_home(ms);
	else if (chdir(path[1]) != 0)
	{
		perror("Minishell: cd");
		g_exit = 1;
	}
	else
		g_exit = 0;
	cd_env(ms, old_pwd);
}
