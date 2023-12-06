/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 12:36:00 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/12/06 15:17:23 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	quote_num(char *str)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (str[i])
	{
		if (meta_char(str[i]) == 3)
		{
			i = skip_quotes(str, i);
			n += 2;
		}
		else
			i++;
	}
	return (n);
}

int	skip_quotes(char *str, int pos)
{
	char	quote;

	if (meta_char(str[pos]) == 3)
	{
		quote = str[pos++];
		while (str[pos] && str[pos] != quote)
			pos++;
		pos++;
	}
	return (pos);
}

//Removes quotes from str. Used for case echo "'$HOME'"
char	*remove_quotes(char *str)
{
	int		i;
	int		j;
	char	*buf;
	char	quote;

	i = 0;
	j = 0;
	buf = calloc(sizeof(char), (ft_strlen(str) - quote_num(str) + 1));
	while (str[i])
	{
		if (meta_char(str[i]) == 3)
		{
			quote = str[i++];
			while (str[i] && str[i] != quote)
				buf[j++] = str[i++];
			if (str[i])
				i++;
		}
		else
			buf[j++] = str[i++];
	}
	return (buf);
}

char	*add_quotes(char *str, char c)
{
	int		i;
	int		j;
	char	*buf;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	buf = calloc(sizeof(char), ft_strlen(str) + 3);
	buf[j++] = c;
	while (str[i])
		buf[j++] = str[i++];
	buf[j] = c;
	return (buf);
}

// Returns 1 if there are open quotes
// Returns 0 if there are closed quotes
int	closed_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i] && meta_char(str[i]) != 3)
		i++;
	if (str[i] == '\'')
	{
		i++;
		while (str[i] && str[i] != '\'')
			i++;
	}
	else if (str[i] == '\"')
	{
		i++;
		while (str[i] && str[i] != '\"')
			i++;
	}
	i++;
	if (i == (int)ft_strlen(str))
		return (0);
	return (1);
}
