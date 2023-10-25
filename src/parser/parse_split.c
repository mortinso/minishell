/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 18:02:32 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/10/24 17:52:48 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Splits str into an array of char *
char	**split_main(t_minishell *ms, char *str)
{
	int		i;
	int		word_len;
	char	**buff;
	int		ms_words;

	i = 0;
	ms_words = word_counter(str);
	buff = malloc(sizeof(char *) * (ms_words + 1));
	if (!buff)
		malloc_error(ms);
	while (i < ms_words)
	{
		while (*str && meta_char(*str) == 1)
			str++;
		word_len = split_word(str);
		buff[i++] = split_temp(ms, str, word_len);
		str = str + word_len;
	}
	buff[i] = 0;
	return (buff);
}

// Returns the length of str until the next whitespace or separating meta-char
int	split_word(char *str)
{
	int	i;

	i = 0;
	if (str[i] && meta_char(str[i]) == 3)
		return (str_quotes(str, str[i], i));
	if (str[i] && meta_char(str[i]) == 2)
		return (str_others(str, i));
	if (str[i] && str[i] == '$')
		return (str_envar(str, i));
	if (str[i] && !meta_char(str[i]))
		return (str_plain(str, i));
	return (i);
}

char	*split_temp(t_minishell *ms, char *str, int word_len)
{
	int		i;
	char	*temp;

	i = 0;
	temp = NULL;
	temp = malloc(sizeof(char) * (word_len + 1));
	if (!temp)
		malloc_error(ms);
	while (*str && i < word_len)
		temp[i++] = *str++;
	temp[i] = '\0';
	return (temp);
}
