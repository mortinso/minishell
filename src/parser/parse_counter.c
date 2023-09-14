/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_counter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 11:26:00 by mortins-          #+#    #+#             */
/*   Updated: 2023/09/14 17:15:49 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// how many words are in str
void	str_counter(t_minishell *ms, char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		while (str[i] && meta_char(str[i]) == 1)
			i++;
		if (str[i] && meta_char(str[i]) != 1)
			ms->words++;
		if (str[i] && meta_char(str[i]) == 2)
			i = str_others(str, i);
		else if (str[i] && meta_char(str[i]) == 3)
			i = str_quotes(str, str[i], i);
		else if (str[i] && str[i] == '$')
			i = str_envar(str, i);
		else if (str[i] && !meta_char(str[i]))
			i = str_plain(str, i);
	}
}
