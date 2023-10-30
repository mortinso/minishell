/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replacer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 17:55:44 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/10/30 19:18:58 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**var_split(char *str);
char	*var_iter(t_list **env, char *var);

char	*replace_dollar(char *str, char *buf, t_list **env, int flag)
{
	char	*res;
	char	*buf1;
	char	*buf2;

	buf2 = NULL;
	if (str[0] && str[1] && str[0] == '$' && str[1] == '?')
		return (dollar_cond(buf));
	if (ft_strcmp(str, "$") == 0 || (str[1] && !ft_isalnum(str[1])
			&& str[1] != '_' && str[1] != '\\') || str[1] == '?')
		return (ft_strjoin(buf, str));
	buf1 = ft_strtrim(str, "$");
	buf2 = replace_str(buf1, env);
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

char	*replace_quotes(char *str, char *buf, t_list **env, int flag)
{
	char	*res;
	char	*buf1;

	res = NULL;
	buf1 = NULL;
	if (str[0] == '\'')
		res = replace_single(str, buf, env, flag);
	else if (str[0] == '\"')
	{
		res = remove_quotes(str, '\"');
		buf1 = replacer(res, env, 1);
		free(res);
		res = ft_strjoin(buf, buf1);
	}
	else
		res = ft_strjoin(buf, str);
	free(buf1);
	return (res);
}

char	*replace_cond(char *str, char *buf1, t_list **env, int flag)
{
	char	*res;
	char	*buf2;

	res = NULL;
	buf2 = NULL;
	if (str[0] == '$')
		res = replace_dollar(str, buf1, env, flag);
	else if (meta_char(str[0]) == 3)
		res = replace_quotes(str, buf1, env, flag);
	else if (flag == 2)
	{
		buf2 = add_quotes(str, '\'');
		res = ft_strjoin(buf1, buf2);
		free(buf2);
	}
	else
		res = ft_strjoin(buf1, str);
	return (res);
}

//Joins all substituted strings from the split str
char	*replacer(char *str, t_list **env, int flag)
{
	int		i;
	char	*res;
	char	*buf1;
	char	**arr;

	i = 0;
	res = NULL;
	arr = var_split(str);
	if (!arr)
		return (NULL);
	while (arr[i])
	{
		buf1 = ft_strdup(res);
		free(res);
		if (flag == 0 && arr_size(arr) >= 2 && ft_strcmp(arr[i], "$") == 0 \
			&& arr[i + 1] && arr[i + 1][0] && arr[i + 1][0] == '\'')
			res = NULL;
		else
			res = replace_cond(arr[i], buf1, env, flag);
		free(buf1);
		i++;
	}
	free_array(arr);
	return (res);
}

/* If $ is encountered in the array, it replaces the variable with its value
E.g.:
array         new_array
echo   ---->  echo
$HOME  ---->  /ddiniz/home
$VAR   ---->  value */
void	env_var(t_minishell *ms, t_list **env, char **arr)
{
	int		i;
	char	*buf;

	i = 0;
	while (i < arr_size(arr))
	{
		buf = ft_strdup(arr[i]);
		free(arr[i]);
		arr[i] = replacer(buf, env, 0);
		if (!arr[i])
			malloc_error(ms);
		free(buf);
		i++;
	}
}
