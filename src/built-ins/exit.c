/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 15:29:16 by mortins-          #+#    #+#             */
/*   Updated: 2023/11/01 16:43:22 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Converts a (char *) to an (unsigned long long int)
unsigned long long int	exit_atoull(const char *s)
{
	unsigned long long	num;
	unsigned long long	i;

	i = 0;
	num = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
			i++;
		else if (s[i] == '-' || s[i] == '+')
			i++;
		else if (s[i] >= '0' && s[i] <= '9')
		{
			num = (num * 10) + (s[i] - '0');
			i++;
		}
	}
	return (num);
}

// Checks if arg has any formatting errors: alpha chars, multiple '-'/'+',
// special chars, '-'/'+' out of place, etc.
int	exit_format_error(char *arg)
{
	char	quotes;
	int		i;
	int		n;

	i = 0;
	quotes = 0;
	n = 0;
	while (arg && arg[i])
	{
		if (!quotes && arg[i] && (arg[i] == '\'' || arg[i] == '\"'))
			quotes = arg[i];
		else if (arg[i] && !n && (arg[i] == '-' || arg[i] == '+'))
			n = 1;
		else if (arg[i] && arg[i] != quotes && !ft_isdigit(arg[i]))
			return (1);
		else if (quotes && arg[i] && arg[i] == quotes)
			quotes = 0;
		i++;
	}
	return (0);
}

int	other_exit_status(char *arg)
{
	int	num;

	num = ft_atoi(arg);
	if (num > 0)
	{
		while (num > 256)
			num -= 256;
		return (num);
	}
	else
	{
		while (num < 0)
			num += 256;
		return (num);
	}
}

/*
	In bash, <exit [n]> prints an error if n is larger than LLONG_MAX or smaller
	than LLONG_MIN. Therefore I had to create a function that could convert
	(char)n into a number larger than a long long int, so an unsigned long long
	int. By checking if n contains a '-' I know if the number is negative or not,
	so that I can add 1 to LLONG_MAX on line 91.33. (since exit_atoull() converts
	n to an unsigned number).
*/
void	ft_exit(t_minishell *ms, char **args)
{
	if (arr_size(args) > 2)
	{
		write(STDERR_FILENO, "Minishell: exit: too many arguments\n", 36);
		g_exit = 1;
	}
	else if (arr_size(args) == 2 && args[1] && args[1][0])
	{
		if (exit_format_error(args[1]) || (ft_strchr(args[1], '-') \
			&& exit_atoull(args[1]) > (unsigned long long)(LLONG_MAX) + 1) \
			|| exit_atoull(args[1]) > (unsigned long long)(LLONG_MAX))
		{
			write(STDERR_FILENO, "Minishell: exit: ", 17);
			ft_putstr_fd(args[1], STDERR_FILENO);
			write(STDERR_FILENO, ": numeric argument required\n", 28);
			g_exit = 2;
		}
		else if (0 <= ft_atoi(args[1]) && exit_atoull(args[1]) <= 255)
			g_exit = (int)exit_atoull(args[1]);
		else
			g_exit = other_exit_status(args[1]);
	}
	free_ms(ms);
}
