/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 16:57:08 by mortins-          #+#    #+#             */
/*   Updated: 2023/11/28 11:31:55 by ddiniz-m         ###   ########.fr       */
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
		ms->exit = 2;
		return (1);
	}
	return (0);
}

void	malloc_error(t_minishell *ms)
{
	ft_putstr_fd("Minishell: error: malloc failed\n", STDERR_FILENO);
	ms->exit = 12;
	free_ms(ms);
}

int	open_error(t_minishell *ms, char *filename, int child)
{
	ft_putstr_fd("Minishell: ", STDERR_FILENO);
	perror(filename);
	if (child)
	{
		ms->exit = 1;
		free_ms(ms);
	}
	else
		return (1);
	return (0);
}

void	pipe_error(t_minishell *ms, int *pipe_fd)
{
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	ft_putstr_fd("Minishell: error: pipe failed\n", STDERR_FILENO);
	ms->exit = 1;
	free_ms(ms);
}

void	fork_error(t_minishell *ms, int *pipe_fd)
{
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	ft_putstr_fd("Minishell: error: fork failed\n", STDERR_FILENO);
	ms->exit = 1;
	free_ms(ms);
}
