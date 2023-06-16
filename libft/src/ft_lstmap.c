/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 17:12:10 by mortins-          #+#    #+#             */
/*   Updated: 2023/05/19 16:29:18 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

//	Applies the function ’f’ on the content of each node
//	Creates a new list resulting of the applications of the function ’f’.

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*d)(void *))
{
	t_list	*head;
	t_list	*node;
	void	*content;

	if (!(lst && f && d))
		return (NULL);
	head = NULL;
	while (lst)
	{
		content = f(lst -> content);
		node = ft_lstnew(content);
		if (!node)
		{
			d(content);
			ft_lstclear(&head, d);
			return (NULL);
		}
		ft_lstadd_back(&head, node);
		lst = lst -> next;
	}
	ft_lstclear(&lst, d);
	return (head);
}
