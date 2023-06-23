/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 18:05:31 by mortins-          #+#    #+#             */
/*   Updated: 2023/06/23 15:18:16 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Prints current working directory
void	pwd(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", getcwd(cwd, sizeof(cwd)));
	else
	{
		perror("Error");
		return ;
	}
	// NEED TO CHANGE EXIT_STATUS
}
// PATH_MAX is defined in <limits.h> and represents the maximum length of a
// file path on the current system (including the null terminator).
