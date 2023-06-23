/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 18:40:31 by mortins-          #+#    #+#             */
/*   Updated: 2023/06/23 17:16:05 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*set_prompt(t_var *var)
{
	char	cwd[PATH_MAX];
	char	*prompt;
	char	*buf;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		prompt = malloc(sizeof(char) * 25);
		if (!prompt)
			malloc_error(var);
		prompt = "\033[1;33mMinishell $> \033[0m";
		return (prompt);
	}
	buf = ft_strjoin("\033[1;33m", ft_strrchr(getcwd(cwd, sizeof(cwd)), '/') \
		+ 1);
	if (!buf)
		malloc_error(var);
	prompt = ft_strjoin(buf, " $> \033[0m");
	if (!prompt)
		malloc_error(var);
	free(buf);
	return (prompt);
}
