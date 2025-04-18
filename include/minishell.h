#ifndef MINISHELL_H
# define MINISHELL_H

// system libraries
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <termios.h>

# include <fcntl.h>   // For open flags
# include <readline/readline.h> // for readline()
# include <readline/history.h> // for add_history()

// builtin
# include "builtins.h"

// libft
# include "../lib/libft/libft.h"

# define RUNNING_COMMAND 0
# define WAIT_FOR_COMMAND 1
# define HEREDOC 2
# define FD_UNSET "-42"
# define SUCCESS 0
# define FAILURE 1

// ANSI COLORS
# define ANSI_COLOR_GREEN "\x1B[32m"
# define ANSI_COLOR_DEFAULT "\x1B[0m"

// shell sign
# define SHELL_PROMPT ANSI_COLOR_GREEN"[(what the)shell]$ "ANSI_COLOR_DEFAULT

extern volatile int	global_signal;

typedef struct s_env
{
	char			*key;
	char			*value;
	int				*index;
	struct s_env	*next;
}					t_env;

typedef struct s_env_pack
{
	t_env	*sys_envlist;
	t_env	*mshell_env;
}			t_env_pack;

typedef struct s_cmd {
    char **argv;        // command and args {"ls", "-l", NULL}
    char *infile;       // for <
    char *outfile;      // for > or >>
    int append;         // 1 for >>, 0 for >
	int is_piped;		// if pipe comes after 1, 0 if does not
	char *is_heredoc;	// if there is something means it is for heredoc, otherwise no heredoc
    struct s_cmd *next;   // linked to the next one if it exists
	struct s_cmd *previous;
} 			t_cmd; // WHAT ABOUT HEREDOC



// clean_utility.c
void				clean_array(char **array);
void				clean_out_all(t_env *env1, t_env *env2, char *str1,
						char *str2);
t_env				*cleanup_env(t_env *env_list);

// chang_mode.c
int					change_mode(int mode);

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
t_env_pack	export_std_fd(t_env_pack env_pack);
void    attatch_node(t_env **env_list, char *key, char   *value);
t_env   *node_finder(t_env *env_list, char *key);
t_env *custom_export(t_env *env_list, char *key, char *value);

// extract_env_list.c
t_env				*extract_env_list(char **envp);

// env_list_creator.
t_env				*create_env_list(int env_count);

// utility1.c
char				*find_value_from_env(t_env *env_list, char *key);
int					arrlen(char **arr);

// init_env_pack.c
char				*init_getpid(void);
t_env_pack			init_env_pack(char **envp, char *cur_dir);

// minishell.c
void    minishell(t_env_pack env_pack);

// restore_std_fd.c
void    restore_std_fd(t_env_pack env_pack);

// exit_process.c
void exit_preparation(t_env_pack env_pack);

// tokenization.c
char **line_tokenized(char *line);

// cmd_args_extractor.c
t_cmd *cmd_args_extractor(char **tokenz);

// cmd_syntax_analyzer.c
char **syntax_analyzer(char **tokenz);

// expansion.c
char **dollar_expansion(char **tokenz, t_env *env);

// ┌────────────── ⋆⋅☆⋅⋆ ── Temporary ── ⋆⋅☆⋅⋆ ──────────────┐

void print_cmd_temp(t_cmd *cmd_args);

// └─────────────────────────────────────────────────────────┘




// Minji



#endif
