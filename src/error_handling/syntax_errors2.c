/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:05:56 by mortins-          #+#    #+#             */
/*   Updated: 2023/10/19 11:51:29 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	skip_quotes(char *str, int i);

// Checks for unclosed quote marks
int	quote_error(char *str)
{
	int		i;
	char	c;

	i = 0;
	while (str && str[i])
	{
		if (meta_char(str[i]) == 3)
		{
			c = str[i++];
			while (str[i] && str[i] != c)
				i++;
			if (!str[i])
			{
				write(2, "MiniShell: syntax error: unclosed quote marks\n", 46);
				return (1);
			}
		}
		if (str[i])
			i++;
	}
	return (0);
}

int	pipe_error(char *str)
{
	int		i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] && meta_char(str[i]) == 3)
			i = str_quotes(str, str[i], i);
		else if (str[i] && str[i] == '|')
		{
			i++;
			while (str[i] && meta_char(str[i]) == 1)
				i++;
			if (str[i] && str[i] == '|')
				return (token_message('|'));
		}
		else
			i++;
	}
	return (0);
}

int	dollar_error(char *str)
{
	int		i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
				i++;
			if (!str[i])
				break ;
			i++;
		}
		else if (str[i] == '$' && str[i + 1] == '$')
			return (token_message('$'));
		else
			i++;
	}
	return (0);
}
