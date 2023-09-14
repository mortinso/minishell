/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 18:40:31 by mortins-          #+#    #+#             */
/*   Updated: 2023/09/13 15:52:33 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*set_prompt(t_minishell *ms)
{
	char	cwd[PATH_MAX];
	char	*prompt;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		prompt = malloc(sizeof(char) * 12);
		if (!prompt)
			malloc_error(ms);
		prompt = "Minishell$> ";
		return (prompt);
	}
	prompt = ft_strjoin(ft_strrchr(getcwd(cwd, sizeof(cwd)), '/') + 1, "$> ");
	if (!prompt)
		malloc_error(ms);
	return (prompt);
}
