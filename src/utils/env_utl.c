/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:14:44 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/10/12 16:58:45 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//replaces `str` by its value (`str` would be something like "$HOME")
char	*env_var_str(char *str, t_list **env)
{
	char	*buf1;
	char	*buf2;
	t_list	*tmp;

	tmp = *env;
	buf1 = ft_strtrim(str, "$");
	while (tmp)
	{
		if (strcmp_chr(buf1, (char *)tmp->data, '=') == 0)
		{
			buf2 = ft_strtrim(tmp->data, buf1);
			free(buf1);
			buf1 = ft_strtrim(buf2, "=");
			free(buf2);
			str = ft_strdup(buf1);
			free(buf1);
			return (str);
		}
		tmp = tmp->next;
	}
	return (str);
}

// reads main_arr and replaces all environment variables by their values
void	env_var(t_list **env, char **arr)
{
	int		i;
	int		size;
	char	*buf;

	i = 0;
	size = arr_size(arr);
	while (i < size)
	{
		if (arr[i][0] == '$')
		{
			buf = env_var_str(arr[i], env);
			free(arr[i]);
			arr[i] = ft_strdup(buf);
		}
		i++;
	}
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
