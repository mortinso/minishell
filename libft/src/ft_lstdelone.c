/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 16:09:40 by mortins-          #+#    #+#             */
/*   Updated: 2023/08/31 13:46:27 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//	Deletes and frees the given node using the function ’del’ and free

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	del(lst -> content);
	free(lst);
}
