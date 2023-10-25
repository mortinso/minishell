/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 17:36:41 by mortins-          #+#    #+#             */
/*   Updated: 2023/10/25 14:50:04 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	reset_fds(t_minishell *ms)
{
	dup2(ms->fdout_buf, STDOUT_FILENO);
	close(ms->fdout_buf);
	dup2(ms->fdin_buf, STDIN_FILENO);
	close(ms->fdin_buf);
}

void	redirect_out(t_list *out, int append)
{
	int	fd;

	while (out)
	{
		if (append == 0)
			fd = open(out->data, O_CREAT | O_RDWR | O_TRUNC, 0664);
		else
			fd = open(out->data, O_CREAT | O_RDWR | O_APPEND, 0664);
		if (fd < 0)
		{
			write(2, "Minishell: ", 11);
			perror(out->data);
			g_exit = errno;
			//open error;
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
		out = out->next;
	}
}

void	redirect_in(t_list *in)
{
	int	fd;

	while (in)
	{
		fd = open(in->data, O_RDONLY);
		if (fd < 0)
		{
			write(2, "Minishell: ", 11);
			perror(in->data);
			g_exit = errno;
			//open error;
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
		in = in->next;
	}
}

void	redirect(t_content *cmd, char **main_arr, int pos)
{
	t_content	*tmp_cmd;
	t_list		*here_buf;
	int			tmp_pos;

	tmp_cmd = cmd;
	tmp_pos = pos;
	while (main_arr[tmp_pos] && main_arr[tmp_pos][0] && ft_strcmp(main_arr[\
		tmp_pos], "|") != 0)
	{
		if (ft_strcmp(main_arr[tmp_pos], ">") == 0)
			redirect_out(tmp_cmd->output, 0);
		if (ft_strcmp(main_arr[tmp_pos], ">>") == 0)
			redirect_out(tmp_cmd->append, 1);
		if (ft_strcmp(main_arr[tmp_pos], "<") == 0)
			redirect_in(tmp_cmd->input);
		if (ft_strcmp(main_arr[tmp_pos], "<<") == 0)
		{
			heredoc(tmp_cmd->heredoc->data);
			here_buf = tmp_cmd->heredoc->next;
			free(tmp_cmd->heredoc);
			tmp_cmd->heredoc = here_buf;
		}
		tmp_pos++;
	}
}
