/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 17:08:00 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/09/22 13:16:18 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	cmdlist_print(t_cmdlist **cmdlist)
{
	int			i;
	t_cmdlist	*tmp;

	i = 1;
	tmp = *cmdlist;
	printf("\nLIST:\n");
	while (tmp)
	{
		printf("	NODE%i:\n", i);
		printf("		CONTENT:\n");
		arr_print("	Command with flags", tmp->content->cmd_flags);
		printf("		Input:\n");
		list_print(&tmp->content->input);
		printf("		Output:\n");
		list_print(&tmp->content->output);
		printf("		HereDoc:\n");
		list_print(&tmp->content->heredoc);
		printf("		Append:\n");
		list_print(&tmp->content->append);
		i++;
		if (tmp->next)
			tmp = tmp->next;
		else
			break ;
	}
}

//Counts how many words a command has
int	cmd_args(char **arr, int pos)
{
	int	i;
	int	counter;

	i = pos;
	counter = 0;
	while (arr[i] && i < arr_size(arr))
	{
		if (arr[i][0] == '<' || arr[i][0] == '>')
			i += 2;
		else if (ft_strcmp(arr[i], "|") == 0)
			break;
		else
		{
			counter++;
			i++;
		}
	}
	return (counter);
}

//Counts how many valid commands there are in main->arr.
int	cmd_count(char **arr)
{
	int	i;
	int	cmd_n;

	i = 0;
	cmd_n = 0;
	while (arr[i])
	{
		cmd_n++;
		while (arr[i] && ft_strcmp(arr[i], "|") != 0)
			i++;
		if (arr[i] && ft_strcmp(arr[i], "|") == 0)
			i++;
	}
	return (cmd_n);
}
