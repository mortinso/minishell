/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 18:12:34 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/10/06 12:35:52 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	list_print(t_list **list)
{
	t_list	*tmp;

	tmp = *list;
	while (tmp)
	{
		printf("%s\n", (char *)tmp->data);
		tmp = tmp->next;
	}
}

void	list_sort(t_list **list)
{
	t_list	*head;
	t_list	*tmp;

	head = *list;
	tmp = head;
	while (tmp)
	{
		while (head->next)
		{
			if (ft_strcmp(head->data, head->next->data) > 0)
				list_swap(head);
			head = head->next;
		}
		tmp = tmp->next;
		head = *list;
	}
}

void	list_remove(t_list **list, int pos)
{
	int		i;
	t_list	*tmp;
	t_list	*target;

	i = 0;
	tmp = *list;
	if (pos == 0)
	{
		(*list) = (*list)->next;
		return ;
	}
	while (i < pos - 1)
	{
		tmp = tmp->next;
		i++;
	}
	target = tmp->next;
	tmp->next = target->next;
	free(target->data);
	free(target);
}

int	list_check_dup(t_list **list, char *str)
{
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = *list;
	while (tmp)
	{
		if (ft_strcmp(tmp->data, str) == 0)
			return (i);
		tmp = tmp->next;
		i++;
	}
	return (0);
}

void	list_swap(t_list *list)
{
	char	*str;
	t_list	*head;
	t_list	*tmp;

	str = NULL;
	head = list;
	if (!head && !head->next)
	{
		printf("List Swap Error\n");
		return ;
	}
	tmp = head;
	str = tmp->data;
	head->data = head->next->data;
	head->next->data = str;
}