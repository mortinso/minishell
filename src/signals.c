/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 16:08:59 by mortins-          #+#    #+#             */
/*   Updated: 2023/10/30 18:38:23 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//	CTRL-C sends an "Interrupt" signal.
//	For documentation on rl_functions, read:
//	https://tiswww.case.edu/php/chet/readline/readline.html#Command-Line-Editing
void	signal_interrupt(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_exit = 128 + SIGINT;
	}
}

void	signal_process_interrupt(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

//	CTRL-D represents "No input".
//	When pressed, str is NULL and it exits the shell.
void	signal_exit(t_minishell *ms)
{
	if (!(ms->str))
		free_ms(ms);
}

//	CTRL-C sends an "Interrupt" signal.
//	CTRL-\ sends a "Quit" signal.
//	When using SIG_IGN in signal(), it ignores the signal received.
void	signal_init(void)
{
	signal(SIGINT, signal_interrupt);
	signal(SIGQUIT, SIG_IGN);
}
