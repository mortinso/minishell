/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 16:48:00 by mortins-          #+#    #+#             */
/*   Updated: 2023/10/20 18:34:40 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Returns length of string when it reaches c.
int	strlen_chr(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

// Compares s1 and s2 until s2 reaches c, including c.
int	strcmp_chr(char *s1, char *s2, char c)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && (s1[i] == s2[i]) && i < strlen_chr(s2, c))
		i++;
	return (s1[i] - s2[i]);
}

int	strchr_malloc(char *s, char c)
{
	int	i;

	i = 0;
	if (!s || !s[i])
		return (0);
	while (s[i] && s[i] != c)
		i++;
	if (s[i] && s[i] == c)
		return (1);
	return (0);
}

char	*str_front_trim(char *str, char *trim)
{
	int		i;
	int		j;
	char	*buf;

	j = 0;
	while (str[j] && ft_strchr(trim, str[j]))
		j++;
	i = ft_strlen(str) - j;
	buf = calloc(sizeof(char), (i + 1));
	if (!buf)
		return (0);
	i = 0;
	while (str[j])
		buf[i++] = str[j++];
	return (buf);
}

// Compares s1 and s2 until s2 reaches c, excluding c.
// Since it excludes c, we have to make sure that we reached the end of s1,
// otherwise it shouldn't return 0.
int	strcmp_nochr(char *s1, char *s2, char c)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && (s1[i] == s2[i]) && i < strlen_chr(s2, c) - 1)
		i++;
	if (i < (int)ft_strlen(s1) - 1)
		return (1);
	return (s1[i] - s2[i]);
}
