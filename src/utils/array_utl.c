/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 17:01:18 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/10/30 17:14:00 by ddiniz-m         ###   ########.fr       */
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

char	**arr_cpy(t_minishell *ms, char **arr, int pos, int size)
{
	int		i;
	char	**buf;

	i = 0;
	buf = ft_calloc((size + 1), sizeof(char *));
	if (!buf)
		malloc_error(ms);
	while (i < size)
	{
		buf[i] = ft_calloc((ft_strlen(arr[pos]) + 1), sizeof(char));
		ft_strlcpy(buf[i], arr[pos], ft_strlen(arr[pos]) + 1);
		i++;
		pos++;
	}
	return (buf);
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
