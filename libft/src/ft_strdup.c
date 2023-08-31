/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 12:40:31 by mortins-          #+#    #+#             */
/*   Updated: 2023/08/31 13:47:12 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//	Returns a pointer to a new string duplicated from the string 's'

char	*ft_strdup(const char *s)
{
	char	*buff;

	buff = (char *) malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!buff)
		return (NULL);
	ft_strlcpy(buff, s, ft_strlen(s) + 1);
	return (buff);
}
