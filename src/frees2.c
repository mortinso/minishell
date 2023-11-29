/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 12:39:55 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/11/28 12:41:35 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_hdoc(t_minishell *ms)
{
	if (ms->fdin_buf != -1)
		close(ms->fdin_buf);
	if (ms->fdout_buf != -1)
		close(ms->fdout_buf);
	if (ms->str)
		free(ms->str);
	if (ms->prompt)
		free(ms->prompt);
	if (ms->main_arr)
		free_array(ms->main_arr);
	free_list_malloc(ms->env);
	free_list_malloc(ms->exp);
	free(ms);
}

void	close_std_fds(void)
{
	close(0);
	close(1);
	close(2);
}
