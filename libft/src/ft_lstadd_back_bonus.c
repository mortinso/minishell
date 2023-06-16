/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 15:13:48 by mortins-          #+#    #+#             */
/*   Updated: 2022/11/22 15:21:42 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

//	Adds the node ’new’ at the end of the list 'lst'

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	if (ft_lstlast(*lst))
		ft_lstlast(*lst)-> next = new;
	else
		*lst = new;
}
