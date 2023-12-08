/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 16:08:59 by mortins-          #+#    #+#             */
/*   Updated: 2023/12/08 15:17:01 by ddiniz-m         ###   ########.fr       */
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
	}
}

void	signal_process_interrupt(int signum)
{
	if (signum == SIGQUIT)
		g_sig = SIGQUIT;
	if (signum == SIGINT)
		g_sig = SIGINT;
	if (signum == SIGPIPE)
		g_sig = SIGPIPE;
}

//	CTRL-D represents "No input".
//	When pressed, str is NULL and it exits the shell.
void	signal_exit(t_minishell *ms)
{
	if (!(ms->str))
	{
		write(STDOUT_FILENO, "\n", 1);
		free_ms(ms);
	}
}

//	CTRL-C sends an "Interrupt" signal.
//	CTRL-\ sends a "Quit" signal.
//	When using SIG_IGN in signal(), it ignores the signal received.
void	signal_init(void)
{
	signal(SIGINT, signal_interrupt);
	signal(SIGQUIT, SIG_IGN);
}

void	post_process_signal(void)
{
	if (!g_sig)
		return ;
	if (g_sig == SIGQUIT)
		ft_putstr_fd("Quit\n", STDERR_FILENO);
	if (g_sig == SIGINT)
		printf("\n");
	g_sig = 0;
}
