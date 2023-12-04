/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 17:23:42 by mortins-          #+#    #+#             */
/*   Updated: 2023/11/30 17:24:21 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	heredoc_signal(int signum)
{
	if (signum == SIGINT)
	{
		g_sig = SIGINT;
		printf("\n");
		close(STDIN_FILENO);
	}
}
