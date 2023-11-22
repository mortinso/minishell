/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replacer_chr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:20:36 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/11/22 14:51:42 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**var_split(char *str);
char	*var_iter(t_list **env, char *var);

char	*replace_dollar(t_minishell *ms, char *str, char *buf, int flag)
{
	char	*res;
	char	*buf1;
	char	*buf2;

	buf2 = NULL;
	if (str[0] && str[1] && str[0] == '$' && str[1] == '?')
		return (dollar_cond(ms, buf));
	if (ft_strcmp(str, "$") == 0 || (str[1] && !ft_isalnum(str[1])
			&& str[1] != '_' && str[1] != '\\') || str[1] == '?')
		return (ft_strjoin(buf, str));
	buf1 = ft_strtrim(str, "$");
	buf2 = replace_str(ms, buf1);
	free(buf1);
	if (flag == 2)
	{
		buf1 = ft_strdup(buf2);
		free(buf2);
		buf2 = add_quotes(buf1, '\'');
		free(buf1);
	}
	res = ft_strjoin(buf, buf2);
	free(buf2);
	return (res);
}

char	*replace_quotes(t_minishell *ms, char *str, char *buf, int flag)
{
	char	*res;
	char	*buf1;

	res = NULL;
	buf1 = NULL;
	if (str[0] == '\'' && ft_strcmp(str, "\'\'") != 0)
		res = replace_single(ms, str, buf, flag);
	else if (str[0] == '\"' && ft_strcmp(str, "\"\"") != 0)
	{
		res = remove_quotes(str, '\"');
		buf1 = replacer(ms, res, 1);
		free(res);
		res = ft_strjoin(buf, buf1);
	}
	else
		res = ft_strjoin(buf, str);
	free(buf1);
	return (res);
}
