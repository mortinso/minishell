/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:01:34 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/09/18 17:38:15 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//----------------------------------INCLUDES------------------------------------
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

//libft
# include "../libft/src/libft.h"

//readline, rl_on_new_line, rl_replace_line, rl_redisplay
# include <readline/readline.h>
# include <readline/history.h>

//signal
# include <signal.h>

//-----------------------------------STRUCT-------------------------------------
typedef struct s_content
{
	char	**cmd_flags;
	t_list	*input;
	t_list	*output;
	t_list	*append;
	t_list	*heredoc;
}	t_content;

typedef struct s_cmdlist
{
	t_content			*content;
	struct s_cmdlist	*next;
}	t_cmdlist;

typedef struct s_minishell
{
	int				words;
	int				cmd_count;
	char			**main_arr;
	char			*prompt;
	char			*str;
	t_cmdlist		*cmdlist;
}	t_minishell;

//------------------------------------SRCS--------------------------------------
// signals.c
void		signal_init(void);
void		signal_interrupt(int signum);
void		signal_exit(t_minishell *ms);

// prompt.c
char		*set_prompt(t_minishell *ms);

// frees.c
void		free_ms(t_minishell *ms);
void		free_array(char **arr);
void		free_cmd_list(t_cmdlist *cmdlist);
void		malloc_error(t_minishell *ms);

// +++++++++++++++ struct/[.....] +++++++++++++++
//cmd_utils.c
void		cmdlist_print(t_cmdlist **cmdlist);
int			cmd_args(char **arr, int pos);
int			cmd_count(char **arr);

//content.c
t_list		*redir_lst(char **arr, int index, char *limiter);
char		**cmd_with_flags(char **arr, int pos);

// init.c
void		var_init(t_minishell *ms);

// list.c
void		list_print(t_list **list);

// +++++++++++++ parser/[.........] +++++++++++++
// parse.clist_print(tmp->content->input);

// parse_array.c
int			arr_size(char **arr);
char		**arr_cpy(char **arr, int pos, int size);
void		arr_print(char *str, char **arr);

// parse_split.c
char		**split_main(t_minishell *ms, char *str);
int			split_word(char *str);
char		*split_temp(char *str, int word_len);

// parse_counter.c
void		str_counter(t_minishell *ms, char *str);

// parse_str.c
int			str_plain(char *str, int i);
int			str_quotes(char *str, char c, int i);
int			str_envar(char *str, int i);
int			str_others(char *str, int i);
int			meta_char(char c);

//parse.c
void		parse_main(t_minishell *ms);

//errors
int			syntax_error(t_minishell *ms);

//errors2
int			token_message(char c);
int			sucession_error(char *str);
int			redir_error(char *str);
int			begin_pipe_error(char *str);
int			end_of_string_error(char *str);
int			heredoc_error(char *str);
int			begin_error(char *str);
int			double_redir_error(char *str, char c);

// ++++++++++++++ built-ins/[.....] +++++++++++++
// pwd.c
void		pwd(void);

#endif
