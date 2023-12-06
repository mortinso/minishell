/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 16:53:12 by mortins-          #+#    #+#             */
/*   Updated: 2023/12/06 15:12:45 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_ms(t_minishell *ms)
{
	int	exit_status;

	if (!ms)
		exit(ms->exit);
	close(0);
	close(1);
	close(2);
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
	if (ms->cmdlist)
		free_cmd_list(ms->cmdlist);
	free_list_malloc(ms->env);
	free_list_malloc(ms->exp);
	exit_status = ms->exit;
	free(ms);
	rl_clear_history();
	exit (exit_status);
}

int	free_array(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return (1);
	while (arr[i])
		free(arr[i++]);
	if (arr)
		free(arr);
	return (0);
}

void	free_list(t_list **list)
{
	t_list	*tmp;

	while (*list)
	{
		tmp = *list;
		*list = (*list)->next;
		free(tmp);
	}
}

void	free_cmd_list(t_cmdlist *cmdlist)
{
	t_cmdlist	*tmp;
	t_cmdlist	*head;

	head = cmdlist;
	while (head)
	{
		tmp = head;
		head = head->next;
		free_array(tmp->cmd_args);
		free(tmp);
	}
}

void	free_list_malloc(t_list **list)
{
	t_list	*tmp;

	while (*list)
	{
		tmp = *list;
		*list = (*list)->next;
		free(tmp->data);
		free(tmp);
	}
	if (list)
		free(list);
}
