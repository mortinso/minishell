/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 16:44:37 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/10/22 16:54:54 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	skip_quotes(char *str, int i);

//Checks for metachar at the start of str
int	begin_error(char *str)
{
	int	i;

	i = 0;
	while (str[i] && meta_char(str[i]) == 1)
		i++;
	if (str[i] && str[i] == '|')
		return (token_message(str[i]));
	return (0);
}

//Checks for metachar at the end of str
int	end_of_string_error(char *str)
{
	int	pos;

	pos = ft_strlen(str) - 1;
	while (pos >= 0)
	{
		if (str[pos] && (str[pos] == '<' || str[pos] == '>'
				|| str[pos] == '|'))
			return (write(2, \
			"MiniShell: syntax error near unexpected token `newline'\n", 56));
		else if (meta_char(str[pos]) == 1)
			pos--;
		else
			break ;
	}
	return (0);
}

// Checks for ><
int	redir_error(char *str)
{
	int	i;
	int	size;

	i = 0;
	size = ft_strlen(str) - 1;
	while (i < size && str[i])
	{
		while (str[i] && str[i] != '>' && str[i] != '<' \
			&& meta_char(str[i]) != 3)
			i++;
		if (str[i] && meta_char(str[i]) == 3)
			i = skip_quotes(str, i);
		if (str[i] && str[i + 1] && (str[i] == '>' && str[i + 1] == '<'))
			return (token_message(str[i + 1]));
		if (str[i] && str[i + 1] && (str[i] == '<' && str[i + 1] == '|'))
			return (token_message(str[i + 1]));
		i++;
	}
	return (0);
}

//Checks for << | and for >> |
int	double_redir_error(char *str)
{
	char	redir;
	int		i;
	int		size;

	i = 0;
	size = ft_strlen(str) - 1;
	while (i < size)
	{
		while (i < size && meta_char(str[i]) != 3 && str[i] != '>' \
			&& str[i] != '<')
			i++;
		if (str[i] && meta_char(str[i]) == 3)
			i = skip_quotes(str, i);
		if (str[i] && i < size && (str[i] == '>' || str[i] == '<'))
		{
			redir = str[i];
			if (str[i + 1] == redir && (str[i + 2] == '|' || (str[i + 2] == ' ' \
				&& str[i + 3] == '|')))
				return (token_message('|'));
		}
		i++;
	}
	return (0);
}

//Checks if there are any >, < or | in sucession (divided by whitespace)
//Example: hello > > world; hello > | world: hello > < world
int	sucession_error(char *str)
{
	int	i;
	int	size;

	i = 0;
	size = ft_strlen(str) - 1;
	while (i < size)
	{
		while (str[i] && str[i] != '<' && str[i] != '>' \
			&& meta_char(str[i]) != 3)
			i++;
		if (str[i] && i < size && meta_char(str[i]) == 3)
			i = skip_quotes(str, i);
		if (str[i] && (str[i] == '<' || str[i] == '>'))
		{
			i++;
			if (str[i] && i < size && meta_char(str[i]) == 1)
			{
				while (str[i] && i < size && meta_char(str[i]) == 1)
					i++;
				if (str[i] && meta_char(str[i]) == 2)
					return (token_message(str[i]));
			}
		}
	}
	return (0);
}
