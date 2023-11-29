/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replacer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 17:55:44 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/11/27 12:16:34 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**var_split(char *str);
char	*var_iter(t_list **env, char *var);

char	*replace_cond(t_minishell *ms, char *str, char *buf1, int flag)
{
	char	*res;
	char	*buf2;

	res = NULL;
	buf2 = NULL;
	if (str[0] == '$')
		res = replace_dollar(ms, str, buf1, flag);
	else if (meta_char(str[0]) == 3)
		res = replace_quotes(ms, str, buf1, flag);
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

char	*replace_loop(t_minishell *ms, char **arr, int flag)
{
	int		i;
	char	*res;
	char	*buf1;

	i = 0;
	res = NULL;
	while (arr[i])
	{
		buf1 = ft_strdup(res);
		free(res);
		if (flag == 0 && arr_size(arr) >= 2 && ft_strcmp(arr[i], "$") == 0 \
			&& arr[i + 1] && arr[i + 1][0] && (arr[i + 1][0] == '\'' \
			|| arr[i + 1][0] == '\"'))
			res = NULL;
		else if (arr_size(arr) != 1 && (ft_strcmp(arr[i], "\"\"") == 0
				|| ft_strcmp(arr[i], "\'\'") == 0))
			res = ft_strdup(buf1);
		else
			res = replace_cond(ms, arr[i], buf1, flag);
		free(buf1);
		i++;
	}
	return (res);
}

//Joins all substituted strings from the split str
char	*replacer(t_minishell *ms, char *str, int flag)
{
	char	*res;
	char	**arr;

	arr = var_split(str);
	if (!arr)
		return (NULL);
	res = replace_loop(ms, arr, flag);
	free_array(arr);
	return (res);
}

/* If $ is encountered in the array, it replaces the variable with its value
E.g.:
array         new_array
echo   ---->  echo
$HOME  ---->  /ddiniz/home
$VAR   ---->  value */
int	env_var(t_minishell *ms)
{
	int		i;
	int		size;
	char	*buf;

	i = 0;
	size = arr_size(ms->main_arr);
	if (empty_var(ms->main_arr, ms->env))
		return (1);
	while (i < size)
	{
		buf = ft_strdup(ms->main_arr[i]);
		free(ms->main_arr[i]);
		ms->main_arr[i] = replacer(ms, buf, 0);
		if (!ms->main_arr[i])
			malloc_error(ms);
		free(buf);
		i++;
	}
	return (0);
}
