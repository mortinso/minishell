/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utl2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 10:37:02 by mortins-          #+#    #+#             */
/*   Updated: 2023/12/04 14:22:40 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_strndup(char *str, int len)
{
	char	*res;

	res = malloc(sizeof(char) * len + 1);
	if (!res)
	{
		printf("Minishell: Malloc error!\n");
		return (NULL);
	}
	ft_strlcpy(res, str, len + 1);
	return (res);
}
