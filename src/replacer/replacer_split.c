/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replacer_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 12:34:46 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/11/23 12:12:18 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	skip_quotes(char *str, int pos);

int	skip_var(char *str, int pos)
{
	if (str[pos] == '$')
	{
		pos++;
		if ((str[pos] && str[pos] >= 48 && str[pos] <= 57) || str[pos] == '?')
			pos++;
		else if (str[pos] && (ft_isalpha(str[pos]) || str[pos] == '_'))
		{
			pos++;
			while (str[pos] && (ft_isalnum(str[pos]) || str[pos] == '_'))
				pos++;
		}
	}
	return (pos);
}

//Returns how many "words" it'll split str into
int	var_split_size(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < (int)ft_strlen(str))
	{
		count++;
		if (str[i] && str[i] != '$' && meta_char(str[i]) != 3)
			while (str[i] && str[i] != '$' && meta_char(str[i]) != 3)
				i++;
		else if (meta_char(str[i]) == 3)
			i = skip_quotes(str, i);
		else if (str[i] == '$')
			i = skip_var(str, i);
		else
			i++;
	}
	return (count);
}

//Receives previous position returns lenght of word it started on
int	var_split_word_size(char *str, int prev)
{
	int	i;

	i = prev;
	if (str[i] && str[i] != '$' && meta_char(str[i]) != 3)
		while (str[i] && str[i] != '$' && meta_char(str[i]) != 3)
			i++;
	else if (meta_char(str[i]) == 3)
		i = skip_quotes(str, i);
	else if (str[i] == '$')
		i = skip_var(str, i);
	else
		i++;
	return (i - prev);
}

//Creates each string of the split array
char	*var_split_temp(char *str, int word_len, int pos)
{
	int		i;
	char	*temp;

	i = 0;
	temp = NULL;
	temp = malloc(sizeof(char) * (word_len + 1));
	if (!temp)
		return (NULL);
	while (str[pos] && i < word_len)
		temp[i++] = str[pos++];
	temp[i] = '\0';
	return (temp);
}

//Splits str to be easier to work with
//E.g.: abc"abc$HOME"$PATHb becomes:
// arr0 = abc
// arr1 = "abc$HOME"
// arr2 = $PATHb
char	**var_split(char *str)
{
	int		i;
	int		pos;
	int		size;
	char	**buff;
	int		word_len;

	i = 0;
	pos = 0;
	word_len = 0;
	size = var_split_size(str);
	buff = malloc(sizeof(char *) * (size + 1));
	if (!buff)
		return (NULL);
	while (i < size)
	{
		word_len = var_split_word_size(str, pos);
		buff[i] = var_split_temp(str, word_len, pos);
		if (!buff[i])
			return (NULL);
		pos += var_split_word_size(str, pos);
		i++;
	}
	buff[i] = 0;
	return (buff);
}
