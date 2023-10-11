/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 16:53:12 by mortins-          #+#    #+#             */
/*   Updated: 2023/10/06 12:49:41 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_ms(t_minishell *ms)
{
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
	free(ms);
	exit (g_exit);
}

int	free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] && i < arr_size(arr))
		free(arr[i++]);
	if (arr)
		free(arr);
	return (0);
}

void	malloc_error(t_minishell *ms)
{
	write(2, "Error: Malloc failed\n", 22);
	g_exit = 12;
	free_ms(ms);
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
		free(tmp->content->cmd_flags);
		if (tmp->content->input)
			free_list(&tmp->content->input);
		if (tmp->content->output)
			free_list(&tmp->content->output);
		if (tmp->content->append)
			free_list(&tmp->content->append);
		if (tmp->content->heredoc)
			free_list(&tmp->content->heredoc);
		// etc...
		free(tmp->content);
		free(tmp);
	}
}

void	free_list_malloc(t_list **exp)
{
	t_list	*tmp;

	while (*exp)
	{
		tmp = *exp;
		*exp = (*exp)->next;
		free(tmp->data);
		free(tmp);
	}
	free(exp);
}
