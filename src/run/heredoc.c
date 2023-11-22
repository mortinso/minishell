/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:46:04 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/11/01 19:16:37 by mortins-         ###   ########.fr       */
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

static void	restore_stdin(void)
{
	int	terminal_fd;

	terminal_fd = open("/dev/tty", O_RDWR);
	if (terminal_fd < 0)
		open_error(NULL, NULL, 1);
	dup2(terminal_fd, STDIN_FILENO);
	close(terminal_fd);
}

void	heredoc_child(t_minishell *ms, char *file, char *limiter)
{
	char	*line;
	int		fd;

	line = NULL;
	signal(SIGINT, SIG_DFL);
	change_terminal();
	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (fd < 0)
		open_error(ms, file, 1);
	while (1)
	{
		write(STDOUT_FILENO, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (line == NULL || !line[0])
			heredoc_eof(limiter);
		if (line == NULL || !line[0] || strcmp_nochr(limiter, line, '\n') == 0)
			break ;
		ft_putstr_fd(line, fd);
		free(line);
	}
	close(fd);
	free(line);
	exit (g_exit);
	free_ms(ms);
}

char	*create_file(int here_num)
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

	filename = create_file(here_num);
	restore_stdin();
	pid = fork();
	if (pid < 0)
		fork_error(ms);
	if (pid == 0)
		heredoc_child(ms, filename, limiter);
	else
	{
		signal(SIGINT, signal_process_interrupt);
		waitpid(pid, NULL, 0);
	}
	return (filename);
}
