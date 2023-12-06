/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 17:01:18 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/12/06 13:35:20 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	arr_size(char **arr)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!arr)
		return (0);
	while (arr[i])
	{
		if (arr[i][0])
			count++;
		i++;
	}
	return (count);
}

void	arr_print(char *str, char **arr)
{
	int	i;
	int	j;

	i = 0;
	if (!arr)
		return ;
	j = arr_size(arr);
	printf("	%s:\n", str);
	while (arr[i] && i < j)
		printf("			%s\n", arr[i++]);
}

char	**list_to_array(t_list **list)
{
	int		i;
	int		size;
	t_list	*tmp;
	char	**buf;

	i = 0;
	tmp = *list;
	size = ft_lstsize(tmp);
	buf = malloc(sizeof(char *) * (size + 1));
	while (tmp && i < size)
	{
		buf[i] = ft_strdup((char *)tmp->data);
		tmp = tmp->next;
		i++;
	}
	buf[i] = 0;
	return (buf);
}

char	**ft_arrdup(char **old)
{
	char	**new;
	int		index;

	index = 0;
	new = malloc(sizeof(char *) * (arr_size(old) + 1));
	while (old && old[index])
	{
		new[index] = ft_strdup(old[index]);
		index++;
	}
	new[index] = NULL;
	return (new);
}
