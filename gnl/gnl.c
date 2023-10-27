/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:48:39 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/10/25 16:08:05 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl.h"

char	*get_next_line(int fd)
{
	char	res;
	char	*line;

	if (read(fd, NULL, 0) < 0)
	{
		res = 0;
		return (NULL);
	}
	line = NULL;
	res = 0;
	while (read(fd, &res, 1) > 0)
	{
		line = get_lines(line, res);
		if (res == '\n')
			break ;
	}
	return (line);
}
