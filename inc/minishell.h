/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:01:34 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/12/08 11:49:58 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//----------------------------------INCLUDES------------------------------------
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <linux/limits.h>
# include <errno.h>
# include <limits.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>

//libft
# include "../libft/src/libft.h"

//readline, rl_on_new_line, rl_replace_line, rl_redisplay
# include <readline/readline.h>
# include <readline/history.h>

//signal
# include <signal.h>

# include <termios.h>
# include <term.h>
# include <curses.h>

extern int	g_sig;

//-----------------------------------STRUCT-------------------------------------
typedef struct s_cmdlist
{
	char				**cmd_args;
	struct s_cmdlist	*next;
}	t_cmdlist;

typedef struct s_minishell
{
	int				exit;
	char			*str;
	t_list			**env;
	t_list			**exp;
	char			*prompt;
	int				fdin_buf;
	int				fdout_buf;
	int				cmd_in_fd;
	int				cmd_count;
	char			**main_arr;
	t_cmdlist		*cmdlist;
}	t_minishell;

//------------------------------------SRCS--------------------------------------
//++++++++++++++++ built-ins/[.....] ++++++++++++++++++++++++++++++++++++++++++
// cd.c
void					cd(t_minishell *ms, char **path);

// echo.c
int						ft_echo(t_minishell *ms, char **cmd_args);

// pwd.c
void					pwd(t_minishell *ms);

// env.c
t_list					**env_init(char **envp);
void					env_override(char *str, t_list **env);

// exit.c
void					ft_exit(t_minishell *ms, char **args, int parent);

// export.c
t_list					**export_init(t_minishell *ms);
int						export_error(t_minishell *ms, char *str);
char					*export_str(char *str);
int						export_override(char *str, t_list **export);
void					export(t_minishell *ms, char **arr);

// unset.c
void					unset(t_minishell *ms, char **arr);

//++++++++++++++++ error_handling/[.....] +++++++++++++++++++++++++++++++++++++
// errors.c
int						syntax_error(t_minishell *ms);
void					malloc_error(t_minishell *ms);
int						open_error(t_minishell *ms, char *filename, int child);
void					pipe_error(t_minishell *ms, int *pipe_fd);
void					fork_error(t_minishell *ms, int *pipe_fd);

//errors2.c
int						export_error_msg(t_minishell *ms, char *error);
void					heredoc_eof(char *limiter);

// syntax_errors.c
int						token_message(char token);
int						start_syntax(char *str);
int						end_syntax(char *str);
int						redir_syntax(char *str);
int						double_redir_syntax(char *str);

// syntax_errors2.c
int						sucession_syntax(char *str);
int						quote_syntax(char *str);
int						pipe_syntax(char *str);
int						dollar_syntax(char *str);
int						token_syntax(char *str);

//++++++++++++++++ parser/[.........] +++++++++++++++++++++++++++++++++++++++++
// parse_counter.c
int						word_counter(char *str);

// parse_split.c
char					**split_main(t_minishell *ms, char *str);
int						split_word(char *str);
char					*split_temp(t_minishell *ms, char *str, int word_len);

// parse_str.c
int						str_plain(char *str, int i);
int						str_quotes(char *str, char c, int i);
int						str_envar(char *str, int i);
int						str_others(char *str, int i);
int						meta_char(char c);

//++++++++++++++++ run/[.....] +++++++++++++++++++++++++++++++++++++++++++++++
// cmd_validator.c
int						is_exec(t_minishell *ms, char *cmd, char **paths);
int						is_usable(t_minishell *ms, char	*cmd, char *cmd_path, \
	char **paths_array);

// exec.c
void					exec(t_minishell *ms, char **cmd_arr);
char					**special_path(const char *cmd);
char					**get_paths(t_list **env, char *cmd);
char					*get_cmd_path(t_minishell *ms, char **paths, char *cmd);

// exec_built_ins.c
int						is_built_in(char *str);
void					built_ins(t_minishell *ms, char **cmd_args, int parent);

// redirections.c
void					reset_fds(t_minishell *ms);
int						redirect_in(t_minishell *ms, char *file, int heredoc, \
	int child);
int						redirect_out(t_minishell *ms, char *file, int append, \
	int child);
int						redirect(t_minishell *ms, char **main_arr, int pos, \
	int child);

// heredoc_utils.c
void					change_terminal(void);
char					*create_filename(int here_num);
int						create_file(t_minishell *ms, char *filename);

// heredoc.c
char					*heredoc(t_minishell *ms, char *limiter, int here_num);

// run.c
void					run(t_minishell *ms);
void					child(t_minishell *ms, int *pipe_fd, int cmds_run, \
	int pos);
void					parent(t_minishell *ms, int *pipe_fd, int cmds_run, \
	int pos);

//++++++++++++++++ replacer/[.........] +++++++++++++++++++++++++++++++++++++++
//rep.c
char					**replaced_arr(t_minishell *ms);
char					*replace_str(t_minishell *ms, char *str);

// replacer_utl.c
char					*var_iter(t_minishell *ms, char *var);
char					*var_str(t_list *env, char *var);

//++++++++++++++++ structs/[.....] ++++++++++++++++++++++++++++++++++++++++++++
// cmd_utils.c
void					cmdlist_print(t_cmdlist **cmdlist);
int						cmd_args(char **arr, int pos);
int						cmd_count(char **arr);

// content.c
int						init_heredoc(t_minishell *ms, char **main_arr);
char					**cmd_with_flags(t_minishell *ms, char **arr, int pos);

// init.c
int						var_init(t_minishell *ms);

// +++++++++++++++ utils/[.....] ++++++++++++++++++++++++++++++++++++++++++++++
// array_utl.c
int						arr_size(char **arr);
void					arr_print(char *str, char **arr);
char					**list_to_array(t_minishell *ms, t_list **list);
char					**ft_arrdup(t_minishell *ms, char **old);

// list_utl.c
void					list_print(t_list **list);
void					list_sort(t_minishell *ms, t_list **exp);
void					list_remove(t_list **list, int pos);
int						list_check_dup(t_list **list, char *str);
void					list_swap(t_minishell *ms, t_list *list);

// str_utl.c
int						strlen_chr(char *str, char c);
int						strcmp_chr(char *s1, char *s2, char c);
char					*str_front_trim(char *str, char *trim);
int						strcmp_nochr(char *s1, char *s2, char c);

// str_utl2.c
char					*ft_strndup(char *str, int len);

// quote_utl.c
int						quote_num(char *str);
int						skip_quotes(char *str, int pos);
char					*remove_quotes(char *str);

// +++++++++++++++ ./[.....] ++++++++++++++++++++++++++++++++++++++++++++++++++
// frees.c
void					free_ms(t_minishell *ms);
int						free_array(char **arr);
void					free_cmd_list(t_cmdlist *cmdlist);
void					free_list_malloc(t_list **exp);

// frees2.c
void					free_hdoc(t_minishell *ms);
void					close_std_fds(void);

// prompt.c
char					*set_prompt(t_minishell *ms);

// signals.c
void					signal_init(void);
void					signal_process_interrupt(int signum);
void					signal_exit(t_minishell *ms);
void					post_process_signal(void);

// signals2.c
void					heredoc_signal(int signum);

#endif
