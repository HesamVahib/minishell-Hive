/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvahib <hvahib@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 13:35:50 by michoi            #+#    #+#             */
/*   Updated: 2025/06/01 23:19:21 by hvahib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define _GNU_SOURCE // for O_TMPFILE flag, only available on linux

// system libraries
# include <fcntl.h>             // For open flags
# include <readline/history.h>  // for add_history()
# include <readline/readline.h> // for readline()
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h> // for ioctl(0, TIOCSTI, "\n");
# include <termios.h>

// builtin
# include "builtins.h"

// execution
# include "execution.h"

// libft
# include "../lib/libft/libft.h"

# define RUNNING_COMMAND 0
# define WAIT_FOR_COMMAND 1
# define HEREDOC 2
# define FD_UNSET "-42"
# define SUCCESS 0
# define FAILURE 1

// ANSI COLORS
# define ANSI_COLOR_GREEN "\001\x1B[32m\002"
# define ANSI_COLOR_DEFAULT "\001\x1B[0m\002"

// shell sign
# define SHELL_PROMPT ANSI_COLOR_GREEN "[(what the)shell]$ " ANSI_COLOR_DEFAULT

extern volatile int	g_signal;

typedef struct s_env
{
	char			*key;
	char			*value;
	// int				*index;
	struct s_env	*next;
}					t_env;

typedef struct s_env_pack
{
	t_env			*sys_envlist;
	t_env			*mshell_env;
}					t_env_pack;

typedef struct s_cmd
{
	int error;    // if the cmd itself has an error so it is non-executable!
	char **argv;   // command and args {"ls", "-l", NULL}
	char *infile;  // for <
	char *outfile; // for > or >>
	int				infile_fd;
	int				outfile_fd;
	int				heredoc_fd;
	int append;              // 1 for >>, 0 for >
	int is_piped;            // if pipe comes after 1, 0 if does not
	char *is_heredoc;        // if there is something means it is for heredoc,
								// otherwise no heredoc
	char **heredoc_limiters; // all limiters
	int		redirect_order; // 1 means infile and 2 means heredoc
	struct s_cmd *next;      // linked to the next one if it exists
	struct s_cmd	*previous;
} t_cmd; // WHAT ABOUT HEREDOC

// clean_utility.c
void				clean_out_all(t_env *env1, t_env *env2, char *str1,
						char *str2);
t_env				*cleanup_env(t_env *env_list);

// chang_mode.c
int					change_mode(int mode);

// sig_handlers.c
void				sighandler(int signal);
int					sig_handler_heredoc(void);

// main.c
void				clean_out_all(t_env *env1, t_env *env2, char *str1,
						char *str2);

// // command_sighandler.c
// void running_command_sighandler(int signal);

// set_start.c
int					is_same_value(char *s1, char *s2);
t_env				*remove_node(t_env *head, t_env *node);
t_env				*set_start(t_env *env_list);

// custom_export.c
t_env_pack			export_std_fd(t_env_pack env_pack);
t_env				*node_finder(t_env *env_list, char *key);
t_env				*update_env(t_env *env_list, char *key, char *value);
t_env				*custom_export(t_env *env_list, char *key, char *value);

// extract_env_list.c
t_env				*extract_env_list(char **envp);

// env_list_creator.
t_env				*create_env_list(int env_count);

// utility1.c
char				*ft_strnjoin(char *s1, char *s2, size_t n);
char				*extract_var_key(char *start_ptr);
char				*append_char(char *str, char c);
char				*find_value_from_env(t_env *env_list, char *key);
int					arrlen(char **arr);

// utility2.c
char				*ft_strndup(const char *s, int n);

// init_env_pack.c
char				*init_getpid(void);
t_env_pack			init_env_pack(char **envp, char *cur_dir);

// minishell.c
void				free_cmd_list(t_cmd *cmd_args);
void				minishell(t_env_pack env_pack);

// restore_std_fd.c
void				restore_std_fd(t_env_pack env_pack);

// exit_process.c
void				exit_preparation(t_env_pack env_pack);

// tokenization.c
char				**line_tokenized(char *line, t_env *env);

// tokenz_util_quotes.c
char				**quotes_chkr(char **cmd_line);
char				*remove_adjacent_quotes(char *str);
char				**adjacent_quotes(char **cmd_line);

// tokenz_util_wsplitter.c
char				**word_splitter(char *line);

// tokenz_utils.c
char				*double_backslash_remover(char *cmd_line);

// lexer.c
char				*append_char(char *str, char c);
void				init_cmd_list(t_cmd *cmd_list, int n_pipe);
t_cmd				*cmd_args_extractor(char **tokenz);

// lexer_utils.c
bool				special_char(char *tokenz);
int					pipe_counter(char **tokenz);
void				init_cmd_list(t_cmd *cmd_list, int n_pipe);
int					open_create_files(t_cmd *cmd_list, char *type);
char				**limiter_collector(char **delim_list, char *new_delim);

// lexer_utils.c
int					count_arguments(char **tokenz, int *j);
int					is_redirection(const char *token);
int					is_pipe(const char *token);
void				handle_next_command(t_cmd **cur, int *i);

// cmd_syntax_analyzer.c
char				**syntax_analyzer(char **tokenz);

// expansion.c
char				**dollar_expansion(char **tokenz, t_env *env);

// heredoc.c
int					heredoc_processing(t_cmd *cmd_args);

// expansion.utils.c
char				*process_dollars(char *token, t_env *env);
char				**surplus_dollar_remover(char **cmd_line);
char				*stitch_strings(char **temp_split);

// ft_cmdlen.c
int					ft_cmdlen(char *line);

// ┌────────────── ⋆⋅☆⋅⋆ ── Temporary ── ⋆⋅☆⋅⋆ ──────────────┐

void				print_cmd_temp(t_cmd *cmd_args);

// └─────────────────────────────────────────────────────────┘

// Minji

// utils
int					update_node(t_env *env, char *key, char *new_value);
bool				is_in_array(const char **arr, char *s);
int					envlen(t_env *env);
int					set_and_get_exit_status(int code, bool set);
#endif
