/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replacer_split2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 19:15:27 by mortins-          #+#    #+#             */
/*   Updated: 2023/10/30 19:15:54 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//Takes str without quotes, removes anything else that needs removing and calls
//	var_iter to compare str with env variables.
char	*replace_str(char *str, t_list **env)
{
	char	*buf1;
	char	*buf2;

	buf2 = NULL;
	buf1 = ft_strdup(str);
	if (!buf1)
		return (buf1);
	if (strchr_malloc(buf1, '$'))
		buf2 = replacer(buf1, env, 0);
	else
		buf2 = var_iter(env, buf1);
	free(buf1);
	if (!buf2)
		return (NULL);
	return (buf2);
}

char	*replace_single(char *str, char *buf, t_list **env, int flag)
{
	char	*res;
	char	*buf1;

	buf1 = NULL;
	if (!closed_quotes(str, '\''))
		buf1 = remove_quotes(str, '\'');
	else
		buf1 = ft_strdup(str);
	if (flag == 1)
		res = replace_cond(buf1, buf, env, 2);
	else
		res = ft_strjoin(buf, buf1);
	free(buf1);
	return (res);
}
