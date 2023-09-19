/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 17:08:39 by mortins-          #+#    #+#             */
/*   Updated: 2023/09/19 17:41:46 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	cd_home(void)
{

	if (!getenv("HOME")) // replace with our env
	{
		write(2, "Minishell: cd: HOME is undefined\n", 29);
			// NEED TO CHANGE EXIT_STATUS
		return (-1);
	}
	else if (chdir(getenv("HOME")) != 0)  // replace with our env
	{
		perror("Minishell: cd: HOME");
		// NEED TO CHANGE EXIT_STATUS
		return (-1);
	}
	// NEED TO CHANGE EXIT_STATUS
	return (0);
}

// Returns 0 on success.
// Returns -1 on error
int	cd(char *path)
{
	if (!path || !path[0])
		return (cd_home());
	else if (chdir(path) != 0)
	{
		perror("Minishell: cd");
		// NEED TO CHANGE EXIT_STATUS
		return (-1);
	}
	// NEED TO CHANGE EXIT_STATUS
	return (0);
}
