/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 15:59:22 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/10/12 16:54:22 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//	'readline' records whatever is inputed in terminal, and returns a memory
//	allocated char *buffer
int	g_exit = 0;

int	main(int ac, char **av, char **envp)
{
	t_minishell	*ms;

	ms = malloc(sizeof(t_minishell));
	ms->env = env_init(envp);
	ms->exp = export_init(ms->env);
	signal_init();
	while (1)
	{
		ms->prompt = set_prompt(ms);
		ms->str = readline(ms->prompt);
		add_history(ms->str);
		if (ms->str && syntax_error(ms))
			continue ;
		var_init(ms);
		parse_main(ms);
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
/*	ERRORS:
	- `exit 2 | exit 3` should change exit status
*/

/*
	Need to figure out how we're actually gonna do heredoc
*/

// `>output>>append echo 1 2 3 <input<<heredoc | <in<<here ls -l >out>>app`

/*	To do:
	- `export VAR` should create an environment variable VAR when there isn't
		already one
	- Return error message when command is invalid
	- Figure out where/how we are gonna substitute ($VAR) by it's actual value
 */
