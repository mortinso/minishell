/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replacer_split2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 19:15:27 by mortins-          #+#    #+#             */
/*   Updated: 2023/11/22 14:50:58 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//Takes str without quotes, removes anything else that needs removing and calls
//	var_iter to compare str with env variables.
char	*replace_str(t_minishell *ms, char *str)
{
	char	*buf1;
	char	*buf2;

	buf2 = NULL;
	buf1 = ft_strdup(str);
	if (!buf1)
		return (buf1);
	if (ft_strchr(buf1, '$'))
		buf2 = replacer(ms, buf1, 0);
	else
		buf2 = var_iter(ms->env, buf1);
	free(buf1);
	if (!buf2)
		return (NULL);
	return (buf2);
}

char	*replace_single(t_minishell *ms, char *str, char *buf, int flag)
{
	char	*res;
	char	*buf1;

	buf1 = NULL;
	if (!closed_quotes(str, '\''))
		buf1 = remove_quotes(str, '\'');
	else
		buf1 = ft_strdup(str);
	if (flag == 1)
		res = replace_cond(ms, buf1, buf, 2);
	else
		res = ft_strjoin(buf, buf1);
	free(buf1);
	return (res);
}
