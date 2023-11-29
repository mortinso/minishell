/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replacer_utl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 17:25:15 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/11/27 12:55:25 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*dollar_cond(t_minishell *ms, char *buf)
{
	char	*buf1;
	char	*res;

	res = NULL;
	buf1 = ft_itoa(ms->exit);
	res = ft_strjoin(buf, buf1);
	free(buf1);
	return (res);
}

//Compares env variables with var.
//Returns the value of var if it finds it in env.
// var = HOME
// env: HOME=/nfs/homes/ddiniz-m
// return: /nfs/homes/ddiniz-m
char	*var_cmp(char *env, char *var)
{
	char	*buf1;
	char	*buf2;

	if (strcmp_nochr(var, env, '=') == 0)
	{
		buf1 = str_front_trim(env, var);
		buf2 = str_front_trim(buf1, "=");
		free(buf1);
		return (buf2);
	}
	return (NULL);
}

char	*var_iter(t_list **env, char *var)
{
	char	*buf;
	t_list	*tmp;

	tmp = *env;
	while (tmp)
	{
		buf = var_cmp((char *)tmp->data, var);
		if (buf)
			return (buf);
		tmp = tmp->next;
		free(buf);
	}
	return (NULL);
}

int	empty_var(char **arr, t_list **env)
{
	char	*buf1;
	char	*buf2;

	if (arr_size(arr) == 1 && arr[0][0] && arr[0][0] == '$' \
		&& ft_strcmp(arr[0], "$") != 0 && ft_strcmp(arr[0], "$?") != 0)
	{
		buf1 = str_front_trim(arr[0], "$");
		buf2 = var_iter(env, buf1);
		free(buf1);
		if (!buf2)
		{
			free(buf2);
			return (1);
		}
		free(buf2);
	}
	return (0);
}

// equivalent to `env | grep var`
char	*var_str(t_list *env, char *var)
{
	t_list	*tmp;

	tmp = env;
	while (tmp->data)
	{
		if (ft_strncmp((char *)tmp->data, var, ft_strlen(var)) == 0)
			break ;
		tmp = tmp->next;
	}
	if (!tmp)
		return (NULL);
	return (tmp->data);
}
