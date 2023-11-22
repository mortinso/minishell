/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 18:05:31 by mortins-          #+#    #+#             */
/*   Updated: 2023/11/22 14:24:58 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Prints current working directory
void	pwd(t_minishell *ms)
{
	char	cwd[PATH_MAX + 1];
	int		i;

	i = 0;
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		printf("%s\n", getcwd(cwd, sizeof(cwd)));
		while (cwd[i])
			cwd[i++] = 0;
	}
	else
	{
		perror("Minishell: pwd");
		ms->exit = errno;
		return ;
	}
	ms->exit = 0;
}
// PATH_MAX is defined in <limits.h> and represents the maximum length of a
// file path on the current system (including the null terminator).
