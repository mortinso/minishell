/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 17:28:49 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/06/22 19:20:14 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// In the future this function will have to interpretopen quotes
int	str_words_quotes(t_var *var, char *str, char c, int i)
{
	if (str[i] && str[i] == c)
	{
		i++;
		if (str[i] && str[i] != c)
			var->words++;
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

int	str_words_redirect(t_var *var, char *str, int i)
{
	if (str[i] == '>')
	{
		var->words++;
		while (str[i] && str[i] == '>')
			i++;
	}
	else if (str[i] == '<')
	{
		var->words++;
		while (str[i] && str[i] == '<')
			i++;
	}
	return (i);
}

int	str_words_envar(t_var *var, char *str, int i)
{
	if (str[i] == '$')
	{
		i++;
		var->words++;
		while (str[i] && meta_char(str[i]) == 0)
			i++;
	}
	else if (str[i] && str[i] == '|')
	{
		var->words++;
		i++;
	}
	return (i);
}

// how many words are in str
void	str_words(t_var *var, char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		i = str_words_quotes(var, str, '\'', i);
		i = str_words_quotes(var, str, '\"', i);
		i = str_words_redirect(var, str, i);
		i = str_words_envar(var, str, i);
		if (str[i] && (meta_char(str[i]) == 0))
		{
			var->words++;
			while (str[i] && (meta_char(str[i]) == 0))
				i++;
			if ((str[i] && (meta_char(str[i]) == 3)))
				var->words--;
		}
		else if (str[i] && meta_char(str[i]) == 1)
		{
			while (str[i] && meta_char(str[i]) == 1)
				i++;
		}
	}
}

// Return 0 if regular char;
// Return 1 if space or tab;
// Return 2 if any other meta character;
int	meta_char(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	if (c == '$' || c == '>' || c == '<' || c == '|')
		return (2);
	if (c == '\'' || c == '\"')
		return (3);
	return (0);
}
