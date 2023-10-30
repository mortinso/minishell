/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replacer_utl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 17:25:15 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/10/26 14:28:46 by ddiniz-m         ###   ########.fr       */
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
