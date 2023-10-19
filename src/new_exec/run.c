/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 14:37:46 by mortins-          #+#    #+#             */
/*   Updated: 2023/10/19 15:57:14 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	find_cmd_pos(char **main_arr, int pos)
{
	while (main_arr[pos] && main_arr[pos][0] && ft_strcmp(main_arr[pos][0], "|"\
		) != 0)
		pos++;
	if (main_arr[pos] && main_arr[pos][0] && ft_strcmp(main_arr[pos][0], "|") \
		== 0)
		pos++;
	return (pos);
}

/* void	child(t_minishell *ms, t_cmdlist *cmd)
{

} */

/* void	parent(t_minishell *ms, t_content *cmd)
{

} */

int	run(t_minishell *ms)
{
	t_cmdlist	*tmp;
	int			pos;

	tmp = ms->cmdlist;
	pos = 0;
	if (ms->cmd_count == 1)
	{
	//	parent
	}
	while (cmd_run < cmd_count)
	{
		child(ms, tmp->content, pos);
		pos = find_cmd_pos(ms->main_arr, pos);
		tmp = tmp->next;
	}
	//parent
	return ;
}
