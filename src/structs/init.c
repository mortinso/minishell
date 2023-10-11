/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 18:12:34 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/10/06 15:18:03 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_content	*content_init(t_minishell *ms, int cmd_index)
{
	t_content	*content;

	content = malloc(sizeof(t_content));
	content->input = redir_lst(ms->main_arr, cmd_index, "<");
	content->output = redir_lst(ms->main_arr, cmd_index, ">");
	content->append = redir_lst(ms->main_arr, cmd_index, ">>");
	content->heredoc = redir_lst(ms->main_arr, cmd_index, "<<");
// ^^ Might have to change it depending on how we handle heredoc ^^
	content->cmd_flags = cmd_with_flags(ms, ms->main_arr, cmd_index);
	return (content);
}

//Creates cmdlist. Initializes content by calling content_init.
//Similar to ft_lstnew.
t_cmdlist	*cmdlist_lstnew(t_minishell *ms, int cmd_index)
{
	t_cmdlist	*cmdlist;

	cmdlist = malloc(sizeof(t_cmdlist));
	if (!cmdlist)
		malloc_error(ms);
	cmdlist->content = content_init(ms, cmd_index);
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
	//printf("\nCMD_COUNT = %i\n", ms->cmd_count);
	if (ms->cmd_count <= 0)
		return (NULL);
	cmdlist = NULL;
	while (cmd_n < ms->cmd_count)
	{
		node = cmdlist_lstnew(ms, i);
		i += arr_size(node->content->cmd_flags) + ((ft_lstsize(node->content->\
			output) + ft_lstsize(node->content->input) + ft_lstsize(node->\
			content->append) + ft_lstsize(node->content->heredoc)) * 2) + 1;
		ft_lstadd_back((t_list **)&cmdlist, (t_list *)node);
		cmd_n++;
	}
	return (cmdlist);
}

void	var_init(t_minishell *ms)
{
	ms->words = 0;
	ms->fdin_buf = dup(STDIN_FILENO);
	ms->fdout_buf = dup(STDOUT_FILENO);
	str_counter(ms, ms->str);
	ms->main_arr = split_main(ms, ms->str);
	env_var(ms->env, ms->main_arr);
	ms->cmd_count = cmd_count(ms->main_arr);
	ms->cmdlist = cmd_list_init(ms);
	//cmdlist_print(&ms->cmdlist);
}
