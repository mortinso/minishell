/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 15:19:33 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/06/23 15:29:52 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// In the future this function will look through the separated string and
// interpret it before deciding what to do with it (i.e. what commands to
// execute, what to redirect, what to pipe, etc.)
void	parse_main(t_var *var)
{
	arr_print("MAIN ARRAY", var->main_arr);
}
