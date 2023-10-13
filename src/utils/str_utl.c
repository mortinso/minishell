/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 16:48:00 by mortins-          #+#    #+#             */
/*   Updated: 2023/10/12 17:18:04 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//Returns lenght of string when it reaches c
int	strlen_chr(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

//Compares s1 and s2 until s2 reaches c
int	strcmp_chr(char *s1, char *s2, char c)
{
	int	i;

	i = 0;
	while (i < strlen_chr(s2, c) - 1)
		i++;
	return (s1[i] - s2[i]);
}
