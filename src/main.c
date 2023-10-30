/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 15:59:22 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/10/30 12:37:07 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//	'readline' records whatever is inputed in terminal, and returns a memory
//	allocated char *buffer
int	g_exit = 0;

int	main(int ac, char **av, char **envp)
{
	t_minishell			*ms;

	ms = malloc(sizeof(t_minishell));
	ms->env = env_init(envp);
	ms->exp = export_init(ms->env);
	while (1)
	{
		signal_init();
		ms->prompt = set_prompt(ms);
		ms->str = readline(ms->prompt);
		if (ft_strlen(ms->str) != 0)
			add_history(ms->str);
		if (ms->str && syntax_error(ms))
			continue ;
		var_init(ms);
		run(ms);
		signal_exit(ms);
		free(ms->str);
		free(ms->prompt);
		free_array(ms->main_arr);
		free_cmd_list(ms->cmdlist);
	}
	(void)av;
	(void)ac;
	exit (g_exit);
}

// `>output>>append echo 1 2 3 <input<<heredoc | <in<<here ls -l >out>>app`
