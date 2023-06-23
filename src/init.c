/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 18:12:34 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/06/23 17:00:30 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_var	*var_struct_init(void)
{
	t_var	*var;

	var = malloc(sizeof(t_var));
	return (var);
}

void	var_init(t_var *var)
{
	var->words = 0;
	str_words(var, var->str);
	var->main_arr = split_main(var, var->str);
}
