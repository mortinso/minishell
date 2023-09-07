/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 17:28:49 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/09/06 16:22:44 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	str_plain(char *str, int i)
{
	if (str[i] && !meta_char(str[i]))
	{
		while (str[i] && !meta_char(str[i]))
			i++;
		if (str[i] && str[i] == '$')
			return (str_envar(str, i));
		else if (str[i] && meta_char(str[i]) == 3)
			return (str_quotes(str, str[i], i));
	}
	return (i);
}

//	Need to figure out how to stop the whole proccess
//	Need a separate function to check if there are unclosed quote marks
/*
	Error:
	-Unclosed quotes: Should give syntax error, stop the process and change
		exit status
*/
int	str_quotes(char *str, char c, int i)
{
	if (str[i] && str[i] == c)
	{
		i++;
		while (str[i] && str[i] != c)
			i++;
		if (!str[i])
			return (i); // Should stop the process and syntax error
		i++;
		if (str[i] && !meta_char(str[i]))
			return (str_plain(str, i));
		else if (str[i] && str[i] == '$')
			return (str_envar(str, i));
		else if (str[i] && meta_char(str[i]) == 3)
			return (str_quotes(str, str[i], i));
	}
	return (i);
}

int	str_envar(char *str, int i)
{
	if (str[i] == '$')
	{
		i++;
		if (str[i] && meta_char(str[i]) == 3)
			return (str_quotes(str, str[i], i));
		else if (str[i] && !meta_char(str[i]))
			return (str_plain(str, i));
	}
	return (i);
}

int	str_others(char *str, int i)
{
	if (str[i] && str[i] == '|')
		i++;
	else if (str[i] == '>')
	{
		i++;
		if (str[i] && str[i] == '>')
			i++;
	}
	else if (str[i] == '<')
	{
		i++;
		if (str[i] && (str[i] == '<' || str[i] == '>'))
			i++;
	}
	return (i);
}

/*
	Return 0 if regular char;
	Return 1 if space or tab;
	Return 2 if any other meta character;
	Return 3 if quotation mark;
	Return 4 if dollar sign; ---> currently only used to distinguish between '$'
	and regular chars in other functions
*/
int	meta_char(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	if (c == '>' || c == '<' || c == '|')
		return (2);
	if (c == '\'' || c == '\"')
		return (3);
	if (c == '$')
		return (4);
	return (0);
}
