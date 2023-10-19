/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:00:32 by mortins-          #+#    #+#             */
/*   Updated: 2023/10/19 16:02:02 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	redirect_out(t_content *cmd, t_list *out, int append)
{
	while (out)
	{
		if (!append)
			cmd->fd_out = open(out->data, O_CREAT | O_RDWR | O_TRUNC, 0666);
		else
			cmd->fd_out = open(out->data, O_CREAT | O_RDWR | O_APPEND, 0666);
		if (cmd->fd_out < 0)
		{
			write(2, "Minishell: ", 11);
			perror(out->data);
			g_exit = errno;
			//open error;
		}
		dup2(cmd->fd_out, STDOUT_FILENO);
		close(cmd->fd_out);
		out = out->next;
	}
}

void	redirect_in(t_content *cmd, t_list *in)
{
	while (in)
	{
		cmd->fd_in = open(in->data, O_RDONLY);
		if (cmd->fd_in < 0)
		{
			write(2, "Minishell: ", 11);
			perror(in->data);
			g_exit = errno;
			//open error;
		}
		dup2(cmd->fd_in, STDIN_FILENO);
		close(cmd->fd_in);
		in = in->next;
	}
}

void	redirect(t_minishell *ms, t_content *cmd, char **main_arr, int pos)
{
	t_content	*tmp_cmd;
	t_list		*here_buf;
	int			tmp_pos;

	tmp_cmd = cmd;
	tmp_pos = pos;
	while (main_arr[tmp_pos] && main_arr[tmp_pos][0] && ft_strcmp(main_arr[\
		tmp_pos][0], "|") != 0)
	{
		if (ft_strcmp(main_arr[tmp_pos][0], ">") == 0)
			redirect_out(tmp_cmd->output, 0);
		if (ft_strcmp(main_arr[tmp_pos][0], ">>") == 0)
			redirect_out(tmp_cmd->append, 1);
		if (ft_strcmp(main_arr[tmp_pos][0], "<") == 0)
			redirect_in(tmp_cmd->input);
		if (ft_strcmp(main_arr[tmp_pos][0], "<<") == 0)
		{
			heredoc(tmp_cmd->heredoc->data);
			here_buf = tmp_cmd->heredoc->next;
			free(tmp_cmd->heredoc);
			tmp_cmd->heredoc = here_buf;
		}
		tmp_pos++;
	}
}
