/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 17:08:00 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/10/06 11:56:20 by ddiniz-m         ###   ########.fr       */
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

//Returns lenght of string when it reaches c
int	strlen_chr(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

//Compares s1 and s2 until s2 reaches c
int	strcmp_chr(char *s1, char *s2, char c)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (i < strlen_chr(s2, c) - 1)
	{
		n += s1[i] - s2[i];
		i++;
	}
	return (n);
}
