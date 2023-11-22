/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:21:07 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/11/22 14:39:54 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//check if there is an echo flag
//Returns 1 if yes, 0 if no
int	echo_flag(char *str)
{
	int	i;

	i = 0;
	if (str[i] != '-')
		return (1);
	i++;
	while (str[i] && str[i] == 'n')
		i++;
	if (str[i])
		return (1);
	return (0);
}

void	echo_print(char **cmd_args, int pos)
{
	int	i;

	while (cmd_args && pos < arr_size(cmd_args))
	{
		i = 0;
		if (ft_strcmp("\'\'", cmd_args[pos]) == 0
			|| ft_strcmp("\"\"", cmd_args[pos]) == 0)
			pos++;
		while (i < (int)ft_strlen(cmd_args[pos]) && cmd_args[pos][i])
		{
			if (cmd_args[pos][i])
				printf("%c", cmd_args[pos][i++]);
		}
		pos++;
		if (cmd_args && cmd_args[0]
			&& pos < arr_size(cmd_args)
			&& ft_strcmp("\'\'", cmd_args[pos]) != 0
			&& ft_strcmp("\"\"", cmd_args[pos]) != 0)
		{
			printf(" ");
		}
	}
}

int	ft_echo(t_minishell *ms, char **cmd_args)
{
	int		j;
	int		cmds;
	int		n_flag;

	j = 1;
	n_flag = 0;
	ms->exit = 0;
	cmds = arr_size(cmd_args);
	if (cmd_args[1] && echo_flag(cmd_args[1]) == 0)
	{
		n_flag = 1;
		j++;
	}
	echo_print(cmd_args, j);
	if (cmds == 1)
		return (printf("\n"));
	if (!n_flag)
		printf("\n");
	return (0);
}
