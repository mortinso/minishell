/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 17:08:15 by mira              #+#    #+#             */
/*   Updated: 2023/10/26 16:51:44 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_list	**env_init(char **envp)
{
	int		i;
	char	*buf;
	t_list	*node;
	t_list	**env;

	i = 0;
	env = (t_list **)malloc(sizeof(env));
	*env = NULL;
	while (envp[i])
	{
		buf = ft_strdup(envp[i]);
		node = ft_lstnew(buf);
		ft_lstadd_back(env, node);
		i++;
	}
	return (env);
}

//Checks if there is alredy str in env;
void	env_override(char *str, t_list **env)
{
	t_list	*tmp;
	t_list	*node;

	tmp = *env;
	while (tmp)
	{
		if (!ft_strchr(str, '='))
			break ;
		if (strcmp_chr(tmp->data, str, '=') == 0)
		{
			free(tmp->data);
			tmp->data = ft_strdup(str);
			break ;
		}
		tmp = tmp->next;
	}
	if (!tmp && ft_strchr(str, '='))
	{
		node = ft_lstnew(ft_strdup(str));
		ft_lstadd_back(env, node);
	}
}
