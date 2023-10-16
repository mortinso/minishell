/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 18:05:31 by mortins-          #+#    #+#             */
/*   Updated: 2023/10/13 15:53:57 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Prints current working directory
void	pwd(void)
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
		g_exit = errno;
		return ;
	}
	g_exit = 0;
}
// PATH_MAX is defined in <limits.h> and represents the maximum length of a
// file path on the current system (including the null terminator).
