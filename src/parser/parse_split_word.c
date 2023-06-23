/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_split_word.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 18:45:34 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/06/23 17:16:36 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	split_word_quotes(char *str, char c, int i)
{
	if (str[i] && str[i] == c)
	{
		i++;
		while (str[i] && str[i] != c)
			i++;
		if (str[i])
			i++;
		if (str[i] && meta_char(str[i]) == 0)
		{
			while (str[i] && meta_char(str[i]) == 0)
				i++;
		}
	}
	return (i);
}

int	split_word_redirect(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '>')
	{
		while (str[i] && str[i] == '>')
			i++;
	}
	else if (str[i] == '<')
	{
		while (str[i] && str[i] == '<')
			i++;
	}
	return (i);
}

int	split_word_envar(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '$')
	{
		i++;
		while (str[i] && meta_char(str[i]) == 0)
			i++;
	}
	else if (str[i] && str[i] == '|')
		i++;
	return (i);
}

// size of str until next specific character
int	split_word(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '\'')
		return (split_word_quotes(str, '\'', 0));
	if (str[i] == '\"')
		return (split_word_quotes(str, '\"', 0));
	if (str[i] == '>' || str[i] == '<')
		return (split_word_redirect(str));
	if (str[i] == '|' || str[i] == '$')
		return (split_word_envar(str));
	if (str[i] && (meta_char(str[i]) == 0))
	{
		while (str[i] && (meta_char(str[i]) == 0))
			i++;
		if (str[i] && str[i] == '\'')
			return (split_word_quotes(str, '\'', i));
		else if (str[i] && str[i] == '\"')
			return (split_word_quotes(str, '\"', i));
	}
	return (i);
}
