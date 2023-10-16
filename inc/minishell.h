/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:01:34 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/10/12 17:25:50 by mortins-         ###   ########.fr       */
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

extern int	g_exit;

//-----------------------------------STRUCT-------------------------------------
typedef struct s_content
{
	int		fd_in;
	int		fd_out;
	t_list	*input;
	t_list	*output;
	t_list	*append;
	t_list	*heredoc;
	char	**cmd_flags;
}	t_content;

typedef struct s_cmdlist
{
	t_content			*content;
	struct s_cmdlist	*next;
}	t_cmdlist;

typedef struct s_minishell
{
	char			*str;
	int				words;
	t_list			**env;
	t_list			**exp;
	int				running;
	char			**paths;
	char			*prompt;
	int				fdin_buf;
	int				fdout_buf;
	int				cmd_count;
	char			**main_arr;
	t_cmdlist		*cmdlist;
}	t_minishell;

//------------------------------------SRCS--------------------------------------
//++++++++++++++++ built-ins/[.....] ++++++++++++++++++++++++++++++++++++++++++
// cd.c
void					cd(t_minishell *ms, char **path);

// echo.c
int						echo(char **cmd_flags);

// pwd.c
void					pwd(void);

// env.c
t_list					**env_init(char **envp);
void					env_override(char *str, t_list **env);

// exit.c
void					exit_status(char **args);
void					ft_exit(t_minishell *ms, char **args, int exit);

// export.c
t_list					**export_init(t_list **env);
int						export_error(char **arr);
char					*export_str(char *str);
int						export_override(char *str, t_list **export);
void					export(char **arr, t_list **export, t_list **env);

// unset.c
void					unset_env(t_list **env, char *str);
void					unset_exp(t_list **exp, char *str);
void					unset(t_list **env, t_list **exp, char **arr);

//++++++++++++++++ error_handling/[.....] +++++++++++++++++++++++++++++++++++++
// errors.c
int						syntax_error(t_minishell *ms);
int						token_message(char token);
void					malloc_error(t_minishell *ms);

// syntax_errors.c
int						begin_error(char *str);
int						end_of_string_error(char *str);
int						redir_error(char *str);
int						double_redir_error(char *str, char c);
int						sucession_error(char *str);

// syntax_errors2.c
int						quote_error(char *str);
int						pipe_error(char *str);
int						dollar_error(char *str);

//++++++++++++++++ exec/[.....] +++++++++++++++++++++++++++++++++++++++++++++++
// exec_built_ins.c
int						is_built_in(char *str);
void					built_ins(t_minishell *ms, char **cmd_with_flags, \
	int exit);
void					exp_env_unset(t_minishell *ms, char **cmd_with_flags);

// exec_utils.c
char					**path_init(t_minishell *ms);
char					*is_exec(char *str, char **paths);
void					last_cmd(t_minishell *ms, t_cmdlist *cmdlist, int i);

// exec.c
void					exec(t_minishell *ms, t_cmdlist *cmdlist);
void					child_process(t_minishell *ms, t_cmdlist *cmdlist, \
	int *pipe_fd, int i);
void					parent_process(int *pipe_fd);

// open_file.c
int						open_file_in(t_content *content, t_list *lst);
int						open_file_hdoc(t_content *content, t_list *lst);
int						open_file_out(t_content *content, t_list *lst);
int						open_file_app(t_content *content, t_list *lst);

// redir_hdoc.c
int						redir_check_out(t_content *content, char **arr, \
	int pos);
int						redir_check_in(t_content *content, char **arr, int pos);
int						redir_in(t_content *content, char **arr, int pos);
int						redir_out(t_content *content, char **arr, int pos);
void					set_fd(t_minishell *ms);

// run_pipes.c
int						run(t_minishell *ms);

//++++++++++++++++ parser/[.........] +++++++++++++++++++++++++++++++++++++++++
// parse_counter.c
void					str_counter(t_minishell *ms, char *str);

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

// parse.c
void					parse_main(t_minishell *ms);

//++++++++++++++++ structs/[.....] ++++++++++++++++++++++++++++++++++++++++++++
// cmd_utils.c
void					cmdlist_print(t_cmdlist **cmdlist);
int						cmd_args(char **arr, int pos);
int						cmd_count(char **arr);

// content.c
t_list					*redir_lst(char **arr, int index, char *limiter);
char					**cmd_with_flags(t_minishell *ms, char **arr, int pos);

// init.c
void					var_init(t_minishell *ms);

// +++++++++++++++ utils/[.....] ++++++++++++++++++++++++++++++++++++++++++++++
// array_utl.c
int						arr_size(char **arr);
char					**arr_cpy(t_minishell *ms, char **arr, int pos, \
	int size);
void					arr_print(char *str, char **arr);

// env_utl.c
char					*env_var_str(char *str, t_list **env);
void					env_var(t_list **env, char **arr);
char					*var_str(t_list *env, char *var);

// list_utl.c
void					list_print(t_list **list);
void					list_sort(t_list **list);
void					list_remove(t_list **list, int pos);
int						list_check_dup(t_list **list, char *str);
void					list_swap(t_list *list);

// str_utl.c
int						strlen_chr(char *str, char c);
int						strcmp_chr(char *s1, char *s2, char c);
int						strcmp_nochr(char *s1, char *s2, char c);

// +++++++++++++++ ./[.....] ++++++++++++++++++++++++++++++++++++++++++++++++++
// frees.c
void					free_ms(t_minishell *ms);
int						free_array(char **arr);
void					free_cmd_list(t_cmdlist *cmdlist);
void					free_list_malloc(t_list **exp);

// prompt.c
char					*set_prompt(t_minishell *ms);

// signals.c
void					signal_init(void);
void					signal_interrupt(int signum);
void					signal_exit(t_minishell *ms);

#endif
