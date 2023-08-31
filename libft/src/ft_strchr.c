/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 14:44:49 by mortins-          #+#    #+#             */
/*   Updated: 2023/08/31 13:47:08 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//	Returns a pointer to the first occurrence of the character 'c'
//	in the string 's'

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != (char)c)
		i++;
	if (s[i] == (char)c)
		return ((char *)s + i);
	return (0);
}
