/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 18:02:32 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/06/22 18:46:01 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*split_temp(char *str, int word_len)
{
	int		i;
	char	*temp;

	i = 0;
	temp = NULL;
	temp = malloc(sizeof(char) * (word_len + 1));
	if (!temp)
		return (NULL);
	while (*str && i < word_len)
		temp[i++] = *str++;
	temp[i] = '\0';
	return (temp);
}

// splits str
char	**split_main(t_var *var, char *str)
{
	int		i;
	int		word_len;
	char	**buff;

	i = 0;
	printf("Words = %d\n", var->words);
	buff = malloc(sizeof(char *) * (var->words + 1));
	if (!buff)
		return (NULL);
	while (i < var->words)
	{
		while (*str && meta_char(*str) == 1)
			str++;
		word_len = split_word(str);
		buff[i++] = split_temp(str, word_len);
		str = str + word_len;
	}
	buff[i] = 0;
	return (buff);
}
