/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   content.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 14:59:23 by mortins-          #+#    #+#             */
/*   Updated: 2023/09/14 16:25:38 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_list	*redir_lst(char **arr, int index, char *limiter)
{
	t_list	*node;
	t_list	*redir;

	redir = NULL;
	while (arr[index] && ft_strcmp(arr[index], "|") != 0)
	{
		if (ft_strcmp(arr[index], limiter) == 0)
		{
			node = ft_lstnew(arr[index + 1]);
			if (!node)
			{
				ft_lstclear(&redir, free);
				return (NULL);
			}
			ft_lstadd_back(&redir, node);
			index += 2;
		}
		else
			index++;
	}
	return (redir);
}

//Takes main array and position of a command, and returns an array with the
//command and it's flags
char	**cmd_with_flags(char **arr, int pos)
{
	int		i;
	char	**buf;
	int		args;

	i = 0;
	args = cmd_args(arr, pos);
	buf = malloc(sizeof(char *) * (args + 1));
	if (!buf)
		return (NULL);
	while (i < args && arr[pos])
		buf[i++] = arr[pos++];
	buf[i] = NULL;
	return (buf);
}
