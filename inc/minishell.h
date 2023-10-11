/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:01:34 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/10/06 15:29:36 by ddiniz-m         ###   ########.fr       */
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

extern int g_exit;

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
// signals.c
void					signal_init(void);
void					signal_interrupt(int signum);
void					signal_exit(t_minishell *ms);

// prompt.c
char					*set_prompt(t_minishell *ms);

// +++++++++++++++ struct/[.....] +++++++++++++++
//cmd_utils.c
void					cmdlist_print(t_cmdlist **cmdlist);
int						cmd_args(char **arr, int pos);
int						cmd_count(char **arr);
int						strcmp_chr(char *s1, char *s2, char c);
int						strlen_chr(char *str, char c);

//content.c
t_list					*redir_lst(char **arr, int index, char *limiter);
char					**cmd_with_flags(t_minishell *ms, char **arr, int pos);

// init.c
void					var_init(t_minishell *ms);

// list.c
void					list_print(t_list **list);
void					list_sort(t_list **list);
void					list_remove(t_list **list, int pos);
int						list_check_dup(t_list **list, char *str);
void					list_swap(t_list *list);

// +++++++++++++ parser/[.........] +++++++++++++
// parse_split.c
char					**split_main(t_minishell *ms, char *str);
int						split_word(char *str);
char					*split_temp(t_minishell *ms, char *str, int word_len);

// parse_counter.c
void					str_counter(t_minishell *ms, char *str);

// parse_str.c
int						str_plain(char *str, int i);
int						str_quotes(char *str, char c, int i);
int						str_envar(char *str, int i);
int						str_others(char *str, int i);
int						meta_char(char c);

//parse.c
void					parse_main(t_minishell *ms);

// ++++++++++++++ built-ins/[.....] +++++++++++++
//cd.c
void						cd(t_minishell *ms, char **path);

//echo.c
int						echo(char **cmd_flags);

// pwd.c
void					pwd(void);

//env.c
t_list					**env_init(char **envp);
void					env_override(char *str, t_list **env);

//exit.c
unsigned long long int	exit_atoull(const char *s);
int						exit_format_error(char *arg);
void					ft_exit(t_minishell *ms, char **args);

//export.c
t_list					**export_init(t_list **env);
int						export_error(char **arr);
char					*export_str(char *str);
int						export_override(char *str, t_list **export);
void					export(char **arr, t_list **export, t_list **env);

//unset.c
void					unset_env(t_list **env, char *str);
void					unset_exp(t_list **exp, char *str);
void					unset(t_list **env, t_list **exp, char **arr);

// ++++++++++++++++ utils/[.....] +++++++++++++++
//array_utils.c
int						arr_size(char **arr);
char					**arr_cpy(t_minishell *ms, char **arr, int pos, int size);
void					arr_print(char *str, char **arr);

// frees.c
void					free_ms(t_minishell *ms);
int						free_array(char **arr);
void					free_cmd_list(t_cmdlist *cmdlist);
void					malloc_error(t_minishell *ms);
void					free_list_malloc(t_list **exp);

//str_utils.c
void					env_var(t_list **env, char **arr);

// ++++++++++++++++ exec/[.....] +++++++++++++++
//exec_utils.c
char					**path_init(t_minishell *ms);
char					*is_exec(char *str, char **paths);
int						is_built_in(char *str);
void					built_ins(t_minishell *ms, char **cmd_with_flags);
int						last_cmd(t_minishell *ms, t_cmdlist *cmdlist, int i);
void					exp_env_unset(t_minishell *ms, char **cmd_with_flags);

//exec.c
void					exec(t_minishell *ms, t_cmdlist *cmdlist);
void					child_process(t_minishell *ms, t_cmdlist *cmdlist, int *pipe_fd, int i);
void					parent_process(int *pipe_fd);


//open_file.c
int						open_file_in(t_content *content, t_list *lst);
int						open_file_hdoc(t_content *content, t_list *lst);
int						open_file_out(t_content *content, t_list *lst);
int						open_file_app(t_content *content, t_list *lst);

//redir_hdoc.c
int						redir_check_out(t_content *content, char **arr, int pos);
int						redir_check_in(t_content *content, char **arr, int pos);
int						redir_in(t_content *content, char **arr, int pos);
int						redir_out(t_content *content, char **arr, int pos);
void					set_fd(t_minishell *ms);

//run_pipes.c
int						run(t_minishell *ms);

#endif
