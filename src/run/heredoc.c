/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:46:04 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/11/30 17:26:46 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	change_terminal(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_cc[VQUIT] = _POSIX_VDISABLE;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

int	create_file(t_minishell *ms, char *filename)
{
	int	fd;

	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (fd < 0)
		open_error(ms, filename, 1);
	free(filename);
	return (fd);
}

void	heredoc_child(t_minishell *ms, char *filename, char *limiter)
{
	char	*line;
	int		fd;

	line = NULL;
	signal(SIGINT, heredoc_signal);
	change_terminal();
	fd = create_file(ms, filename);
	while (1)
	{
		line = readline("> ");
		if (g_sig == SIGINT)
			ms->exit = 128 + SIGINT;
		else if (!line)
			heredoc_eof(limiter);
		if (g_sig == SIGINT || !line || strcmp_nochr(limiter, line, '\n') == 0)
			break ;
		ft_putendl_fd(line, fd);
		free(line);
	}
	if (line)
		free(line);
	close(fd);
	free_hdoc(ms);
}

char	*create_filename(int here_num)
{
	int		i;
	char	*buf;
	char	*filename;

	i = 0;
	buf = NULL;
	filename = ft_strdup("/tmp/tmpxxx");
	while (i < here_num)
	{
		buf = ft_strdup(filename);
		free(filename);
		filename = ft_strjoin(buf, "x");
		free(buf);
		i++;
	}
	return (filename);
}

char	*heredoc(t_minishell *ms, char *limiter, int here_num)
{
	char	*filename;
	pid_t	pid;
	int		status;

	signal(SIGINT, SIG_IGN);
	filename = create_filename(here_num);
	pid = fork();
	if (pid < 0)
		fork_error(ms, NULL);
	if (pid == 0)
		heredoc_child(ms, filename, limiter);
	else
	{
		wait(&status);
		if (pid != -1 && WIFEXITED(status) && WEXITSTATUS(status) == (128 + \
			SIGINT))
		{
			g_sig = SIGINT;
			unlink(filename);
		}
	}
	return (filename);
}
