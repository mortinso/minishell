/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 18:12:34 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/06/20 18:56:01 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_var	*var_struct_init(void)
{
	t_var	*var;

	var = malloc(sizeof(t_var));
	return (var);
}

void	var_init(t_var *var, char *str)
{
	var->words = 0;
	str_words(var, str);
	var->main_arr = split_main(var, str);
}
