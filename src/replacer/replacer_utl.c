/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replacer_utl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 17:25:15 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/12/05 15:37:26 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//Compares env variables with var.
//Returns the value of var if it finds it in env.
// var = HOME
// env: HOME=/nfs/homes/ddiniz-m
// return: /nfs/homes/ddiniz-m
char	*var_cmp(char *env, char *var)
{
	char	*buf1;
	char	*buf2;

	if (!var)
		return (NULL);
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
