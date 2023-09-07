/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 15:59:22 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/09/06 16:11:39 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//	'readline' records whatever is inputed in terminal, and returns a memory
//	allocated char *buffer
int	main(void)
{
	t_var	*var;

	var = var_struct_init();
	signal_init();
	while (1)
	{
		var->prompt = set_prompt(var);
		var->str = readline(var->prompt);
		var_init(var);
		parse_main(var);
		add_history(var->str);
		signal_exit(var);
		free(var->str);
		free(var->prompt);
		free_array(var->main_arr);
	}
	free(var);
}

/*	To do:
	- Check for syntax errors before starting to parse <var>
	- Figure out where/how we are gonna substitute ($VAR) by it's actual value

	Syntax Errors:
	- Unclosed quote marks
	- Some pipe behavior `||`; `| |`

	Errors on:
	- str_quotes();

	Needs attention:
	- malloc_error();
	- pwd();
	- str_quotes()
 */
