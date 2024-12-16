/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 19:22:12 by anoukan           #+#    #+#             */
/*   Updated: 2024/12/16 01:13:56 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
# include <signal.h>
# include <stdlib.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include "../libft/libft/libft.h"
# include "errors.h"

//prompt colors
#define BLUE	"\033[0;34m"
#define RESET	"\033[0m"

// Structure

// Defines
# define ECHO "echo"
# define CD "cd"
# define PWD "pwd"
# define EXPORT "export"
# define UNSET "unset"
# define ENV "env"
# define EXIT "exit"
# define HD "<<"
# define EXPAND "$"

// Define path
# define PATH "/bin/"

// Define ID
# define ECHO_ID 1
# define CD_ID 2
# define PWD_ID 3
# define EXPORT_ID 4
# define UNSET_ID 5
# define ENV_ID 6
# define EXIT_ID 7
# define BUILTIN_ID_MIN 1
# define BUILTIN_ID_MAX 10

# define HD_ID 9
# define EXPAND_ID 10
# define MINISHELL_ID 16

# define HEREDOC_FILENO -42
# define HEREDOC_QUOTES_FILENO -4242


// Enum
typedef enum e_redir
{
	R_OUTPUT,
	R_INPUT,
	R_HEREDOC,
	R_APPEND,
	R_INVALID,
}								t_enum_redir;

typedef enum e_cmd_type
{
	CMD_BUILTIN = 1,
	CMD_EXTERN,
}								t_cmd_type;

// Exec
# define IN 0
# define OUT 1

# define RE 0
# define WE 1

// Structure
//
typedef struct s_safe_fd
{
	int							fd;
	struct s_safe_fd					*next;
}								t_safe_fd;
typedef struct s_redir
{
	t_enum_redir						type;
	char							*redir;
	struct s_redir						*next;
}								t_redir;

typedef struct s_command
{
	char							*in;
	char							*command;
	char							**arg;
	char							**clean_arg;
	int							id;
	struct s_command					*subcommand;
	bool							builtin;
	bool							pipe;
	int							pipe_position;
	int							pipe_fds[2];
	int							pid;
	t_redir							*redirection;
	int							infile_fd;
	int							outfile_fd;
}								t_command;

typedef struct s_export_list
{
	char							*name;
	char							*value;
	struct s_export_list					*next;
}								t_export_list;

typedef struct s_minishell
{
	char							**env;
	char							**hidden_env;
	int							std_fds[2];
	int							*exit_status;
	char							**hidden_path;
	char							**paths;
	char							*pwd;
	char							*old_pwd;
	int							res_last_command;
	char							**hd;
	t_export_list						**export_list;
}								t_minishell;

// safe malloc
enum							e_action
{
	ALLOC_COMMAND,
	ALLOC_MINISHELL,
	DESTROY_COMMAND,
	NUKE,
};

enum e_fd {
	CLOSE_FD,
	OPEN_FD,
};

typedef struct s_safe_malloc
{
	void						*ptr;
	bool						mark;
	struct s_safe_malloc		*next;
}								t_safe_malloc;

// Parsing
char								**relexer(char **in);
char								**expand_in(char **arg, t_minishell *minishell);
t_command							*command_init(char *in);
t_command							*parsing(char *str, t_minishell *minishell);
t_command							*trim(char *in, char *in_command, bool builtin,
									int id);
t_redir								*extract_redir(char **in);
char								**clean_arg(char **arg);

char								*add_char(char *s, char c);
char								*clean_name(char *var);

char								**remove_quote(char **arg);

// Divider for parsing
size_t								check_pipe(char *in);

// Input chekcer
bool								input_checker(t_minishell *minishell,
									char *command);

char								*tiny_expand(char *s, t_minishell *minishell);
// FREE
void								free_minishell(t_minishell *minishell);
void								free_command(t_command *command);
int								ft_minishell(t_minishell *minishell);

// UTILS
char								*display_prompt(char *prompt,
									t_minishell *minishell);
void								sighandler(int sig);
char								**get_env(char **env);
bool								checker_command(char *in, char *command);
int								nbr_of_line(char **env);

// Split Element
size_t								ft_countword(const char *s, char c);
int								ft_split_free(char **dest);
void								ft_split_write_word(char *dest, const char *src,
									int start, int end);
char								**split_element(char *s, char c);

// ENV_UTILITY
int								get_env_var(t_minishell *minishell, char *var,
									int len);

// Debug
void								ft_print(char **s, int i);
void								ft_print_redir(t_redir *list);
void								print_command(t_command *command, char *name);

// export list
int								add_node_export(t_export_list **list,
									char *name, char *value);
t_export_list							**init_export_list(char **env);
void								print_export_list(t_export_list **list);
void								merge_sort(t_export_list **head_ref);
char								*get_name_env(char *var);
char								*get_value_env(char *var);
int								modify_value(t_export_list **lst, char *name,
									char *value);
t_export_list							*find_export_node(char *name,
									t_export_list **lst);
int								delete_export_node(t_export_list **lst,
									char *name);

// Securtity
bool								check_access(char *path);

// sert a creer des mallocs dans une liste chaine
void								*safe_malloc(size_t size, enum e_action action);

// strdup but safe
char								*safe_strdup(char *s, enum e_action action);

char								*ft_itoa_safe(int n, enum e_action action);

char								*ft_strjoin_safe(char const *s1, char const *s2,
									enum e_action action);

char								**ft_split_safe(char const *s, char c,
									enum e_action action);

// BIN
// CD
int								ft_cd(t_command *command,
									t_minishell *minishell);
char								*get_path(char *in, t_minishell *minishell);
char								*get_home(t_minishell **minishell);
char								*path_constructor(t_minishell *minishell,
									char *in);
char								*get_current_path(t_minishell *minishell);
int								change_pwd(t_minishell *minishell, char *in);
void								remove_path(char *dest);
void								add_path(char *dest, char *to_add);

// ECHO
int								ft_echo(t_command *command);
int								echo_print(char **arg, bool eof, int i);
int								check_flag(char **arg);

// ENV
int								ft_env(t_minishell *minishell);

// EXIT
void								ft_exit(t_minishell *minishell,
									t_command *command, bool fail);

// EXPAND
int								ft_expand(t_command *command,
									t_minishell *minishell);

// PWD
int								ft_pwd(t_minishell *minishell);

// UNSET
int								ft_unset(t_command *command,
									t_minishell *minishell);

// EXPORT
int								ft_export(t_command *command,
									t_minishell *minishell);
int								create_var(t_minishell *minishell, char *var);
int								delete_var(t_minishell *minishell, int line);
int								modify_value_env(t_minishell *minishell,
									char *name, char *value);



int								ft_exec(t_minishell *minishell,
									t_command *command);
int								ft_exec_builtins(t_minishell *minishell,
									t_command *command);
int								ft_exec_extern(t_minishell *minishell,
									t_command *command);
void								process_input_line(char *line, t_minishell *m);

char								*get_cmd_path(char *cmd_name, t_minishell *m, int *err);
// Utils
void								exec_error(char *error, t_minishell *minishell,
									t_command *command);
int								count_cmd(t_command *command);
int								heredoc_handler(int fd, t_redir *redir);
int								handle_redirections(t_command *cmd);

// signal
# define NO_SIG 0

extern volatile sig_atomic_t	g_sig;

int								set_signals_to_minishell(void);
int								set_signals_to_default(void);
int								set_signals_to_ignore(void);
int								set_signals_to_heredoc(void);

void								minishell_signal_handler(int signal);
void								heredoc_signal_handler(int signal);

// Utils

int								in_quote(int status, char type);
char								**add_line(char **tab, char *to_add,
									enum e_action action);

// need to add all the fd there for the closing;
void add_safe_fd(int fd, enum e_fd type);

// init no env
char								**init_no_env(void);
t_export_list **init_no_env_export(void);


#endif
