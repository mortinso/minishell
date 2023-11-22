/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 16:57:08 by mortins-          #+#    #+#             */
/*   Updated: 2023/11/01 19:16:01 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	syntax_error(t_minishell *ms)
{
	if (quote_syntax(ms->str) || pipe_syntax(ms->str) || start_syntax(ms->str) \
		|| end_syntax(ms->str) || redir_syntax(ms->str) \
		|| double_redir_syntax(ms->str) || dollar_syntax(ms->str) \
		|| sucession_syntax(ms->str) || token_syntax(ms->str))
	{
		free(ms->prompt);
		free(ms->str);
		g_exit = 2;
		return (1);
	}
	return (0);
}

void	malloc_error(t_minishell *ms)
{
	ft_putstr_fd("Minishell: error: malloc failed\n", STDERR_FILENO);
	g_exit = 12;
	free_ms(ms);
}

int	open_error(t_minishell *ms, char *filename, int child)
{
	ft_putstr_fd("Minishell: ", STDERR_FILENO);
	perror(filename);
	if (child)
	{
		g_exit = 1;
		free_ms(ms);
	}
	else
		return (1);
	return (0);
}

void	pipe_error(t_minishell *ms)
{
	ft_putstr_fd("Minishell: error: pipe failed\n", STDERR_FILENO);
	g_exit = 1;
	free_ms(ms);
}

void	fork_error(t_minishell *ms)
{
	ft_putstr_fd("Minishell: error: fork failed\n", STDERR_FILENO);
	g_exit = 1;
	free_ms(ms);
}
