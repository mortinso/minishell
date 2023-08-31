/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 15:49:30 by mortins-          #+#    #+#             */
/*   Updated: 2023/08/31 13:46:56 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//	Outputs the character 'c' to the given file descriptor

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
