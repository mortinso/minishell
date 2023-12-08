/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   content.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 14:59:23 by mortins-          #+#    #+#             */
/*   Updated: 2023/12/08 13:23:18 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	init_heredoc(t_minishell *ms, char **main_arr)
{
	int		index;
	char	*buf;

	index = 0;
	if (!main_arr || !main_arr[0] || !main_arr[0][0])
		return (0);
	while (main_arr[index])
	{
		if (ft_strcmp(main_arr[index], "<<") == 0)
		{
			buf = heredoc(ms, main_arr[index + 1], index);
			free(main_arr[index + 1]);
			main_arr[index + 1] = ft_strdup(buf);
			free(buf);
			if (g_sig == SIGINT)
			{
				g_sig = 0;
				return (1);
			}
			index += 2;
		}
		else
			index++;
	}
	return (0);
}

int	split_expansion(t_minishell *ms, char **buf, char *str, int index)
{
	char	**buf2;
	int		temp_i;

	temp_i = 0;
	buf2 = split_main(ms, str);
	while (buf2[temp_i])
	{
		buf[index] = remove_quotes(buf2[temp_i]);
		index++;
		temp_i++;
	}
	free_array(buf2);
	return (index);
}

//Takes main array and position of a command, and returns an array with the
//command and it's flags
char	**cmd_with_flags(t_minishell *ms, char **arr, int pos)
{
	int		i;
	char	**buf;
	int		args;

	i = 0;
	args = cmd_args(arr, pos);
	buf = malloc(sizeof(char *) * (args + 1));
	if (!buf)
		malloc_error(ms);
	while (arr[pos] && !arr[pos][0])
		pos++;
	while (i < args)
	{
		if (arr[pos] && (ft_strcmp(arr[pos], ">") == 0 \
			|| ft_strcmp(arr[pos], ">>") == 0 || ft_strcmp(arr[pos], "<") == 0 \
			|| ft_strcmp(arr[pos], "<<") == 0))
			pos += 2;
		else if (ft_strcmp(arr[pos], "|") == 0)
			break ;
		else
			i = split_expansion(ms, buf, arr[pos++], i);
	}
	buf[i] = NULL;
	return (buf);
}
