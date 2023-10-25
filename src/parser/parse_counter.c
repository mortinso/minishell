/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_counter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 11:26:00 by mortins-          #+#    #+#             */
/*   Updated: 2023/10/24 17:52:24 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// how many words are in str
int	word_counter(char *str)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (str && str[i])
	{
		while (str[i] && meta_char(str[i]) == 1)
			i++;
		if (str[i] && meta_char(str[i]) != 1)
			words++;
		if (str[i] && meta_char(str[i]) == 2)
			i = str_others(str, i);
		else if (str[i] && meta_char(str[i]) == 3)
			i = str_quotes(str, str[i], i);
		else if (str[i] && str[i] == '$')
			i = str_envar(str, i);
		else if (str[i] && !meta_char(str[i]))
			i = str_plain(str, i);
	}
	return (words);
}
