/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 18:12:34 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/12/06 15:18:29 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//Creates cmdlist. Initializes cmd_arr
//Similar to ft_lstnew.
t_cmdlist	*cmdlist_lstnew(t_minishell *ms, int cmd_index)
{
	t_cmdlist	*cmdlist;

	cmdlist = malloc(sizeof(t_cmdlist));
	if (!cmdlist)
		malloc_error(ms);
	cmdlist->cmd_args = cmd_with_flags(ms, ms->main_arr, cmd_index);
	cmdlist->next = NULL;
	return (cmdlist);
}

t_cmdlist	*cmd_list_init(t_minishell *ms)
{
	int			cmd_n;
	int			i;
	t_cmdlist	*node;
	t_cmdlist	*cmdlist;

	i = 0;
	cmd_n = 0;
	if (ms->cmd_count <= 0)
		return (NULL);
	cmdlist = NULL;
	while (cmd_n < ms->cmd_count)
	{
		node = cmdlist_lstnew(ms, i);
		while (ms->main_arr[i] && ft_strcmp(ms->main_arr[i], "|") != 0)
			i++;
		if (ms->main_arr[i] && ft_strcmp(ms->main_arr[i], "|") == 0)
			i++;
		ft_lstadd_back((t_list **)&cmdlist, (t_list *)node);
		cmd_n++;
	}
	return (cmdlist);
}

int	var_init(t_minishell *ms)
{
	char	**new_arr;

	ms->cmd_in_fd = 0;
	ms->fdin_buf = dup(STDIN_FILENO);
	ms->fdout_buf = dup(STDOUT_FILENO);
	ms->main_arr = split_main(ms, ms->str);
	if (init_heredoc(ms, ms->main_arr))
		return (1);
	new_arr = replaced_arr(ms);
	free_array(ms->main_arr);
	ms->main_arr = ft_arrdup(new_arr);
	free_array(new_arr);
	ms->cmd_count = cmd_count(ms->main_arr);
	ms->cmdlist = cmd_list_init(ms);
	signal_init();
	return (0);
}

/* echo $ABC"a" b

$ABC="a | cat Makefile"
echo
a | cat Makefilea
b

echo

b
 */