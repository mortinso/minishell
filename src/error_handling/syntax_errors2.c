/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:05:56 by mortins-          #+#    #+#             */
/*   Updated: 2023/10/30 20:02:13 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	skip_quotes(char *str, int i);

//Checks if there are any >, < or | in sucession (divided by whitespace)
//Example: hello > > world; hello > | world: hello > < world
int	sucession_syntax(char *str)
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

// Checks for unclosed quote marks
int	quote_syntax(char *str)
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

int	pipe_syntax(char *str)
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

int	dollar_syntax(char *str)
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

int	token_syntax(char *str)
{
	int		i;
	char	c;

	i = 0;
	c = 0;
	while (i < (int)ft_strlen(str))
	{
		if (meta_char(str[i]) == 3)
			i += skip_quotes(str, i);
		if (i < (int)ft_strlen(str) && (str[i] == '&' || str[i] == '(' \
			|| str[i] == ')' || str[i] == ';'))
			c = str[i];
		i++;
	}
	if (c != 0)
		return (token_message(c));
	return (0);
}
