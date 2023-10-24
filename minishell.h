/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchan <wchan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 16:13:47 by wchan             #+#    #+#             */
/*   Updated: 2023/10/24 15:32:06 by wchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H
# include "libft/ft_printf.h"
# include "libft/libft.h"
# include "libft/get_next_line.h"
# include <stdbool.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include <errno.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include "buildin.h"
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

# define PATH_MAX 4096
# define MAX_INPUT 1024
# define MAX_HISTORY 100
# define PID_MAX 32768

int	g_exit_code;

typedef enum e_type
{
	REDIR_IN,
	REDIR_OUT,
	STR,
	PIPE
}				t_type;

typedef enum e_err_message
{
	SYNTAX,
	MALLOC,
	NONE
}				t_err_message;

typedef struct s_token_check
{
	bool	single_quote_open;
	bool	double_quote_open;
	bool	multiple_spec_char;
	bool	digit;
}				t_token_check;

typedef struct s_token
{
	t_type			type;
	char			*value;
	bool			double_symbol;
	t_token_check	check;
}				t_token;

typedef struct s_quote_open
{
	bool	single_quote;
	bool	double_quote;
}				t_quote_open;

typedef struct s_count
{
	int	token_char;
	int	single_quote;
	int	double_quote;
	int	heredoc;
	int	heredoc_open;
	int	pipe;
	int	cur_pipe;
}				t_count;

typedef struct s_arg
{
	char	**str;
	bool	*double_symbol;
}				t_arg;

typedef struct s_fd
{
	int	default_in;
	int	default_out;
	int	in;
	int	out;
	int	file_in;
	int	pipe[2];
}				t_fd;

typedef struct s_command_line
{
	t_arg	arg[3];
	int		nbr_arg[3];
	int		count_arg[3];
	t_type	*redir_order;
	int		count_redir_order;
	int		nbr_redir;
}				t_command_line;

//main.c
void	ft_minishell(char *line, char ***g_env,
			char command_history[MAX_HISTORY][MAX_INPUT], int command_count);
void	ft_execute_minishell(char *line, char ***g_env);

//minishell_utils.c
char	*ft_strndup(const char *s1, size_t n);
char	*ft_strstr(const char *haystack, const char *needle);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strtok(char *str, const char *delim);
int		check_and_increment(const char *d, char **next_token);

//handle_file.c
void	ft_handle_file_heredoc(int *fd, int *heredoc_open_count);
void	ft_handle_file(t_command_line *command_line,
			t_fd *fd, int *heredoc_open_count);
void	ft_handle_infile(t_fd *fd, t_command_line *command_line,
			int *heredoc_open_count, int *open_err);
void	ft_handle_outfile(t_fd *fd, t_command_line *command_line,
			int *open_err);

//handle_err.c
int		ft_err(int heredoc_count, t_err_message message,
			t_list *token_list, t_list **command_table);
int		ft_open_heredoc_err(int heredoc_count, char *message,
			t_list **token_list);
void	ft_open_err(char *error_message, char *file, int g_exit_code);

//free.c
void	ft_free_token(void *content);
void	ft_free_command_table(void *content);
void	ft_del_list(void *content);
void	mini_freestrarr(char **arr);

//singal.c
char	*print_prompt(void);
void	handle_sigint(int sig);
void	handle_sigquit(int sig);
void	init_signal(void);
void	init_signal_child(void);

//lexer.c
int		ft_lexer(char *s, t_list **token_list, t_count *count, char ***g_env);
int		ft_get_token_value(char **s, t_token *token, t_count *count);
int		ft_check_token_char(char **s, t_count *count,
			t_token_check *check, int *spec_char_pos);
int		ft_get_token_type(t_token *token, t_count count,
			t_token *prev_token, t_list **token_list);
int		ft_check_heredoc_and_expandor(t_token *token, t_count *count,
			t_token *prev_token, char ***g_env);

//lexer_utils.c
void	ft_quote_count(char *s, int *single_quote_count,
			int *double_quote_count);
int		ft_create_token_list(t_list **token_list,
			t_count *count, t_token **token);
bool	ft_check_quote(char token_value_char, t_count *count,
			bool *single_quote_open, bool *double_quote_open);
int		ft_get_token_redir_type(t_token *token);
void	ft_remove_quote(t_token *token);

//expandor.c
int		ft_expandor(t_token *token, t_count count, char ***g_env);
int		ft_check_expand_char(t_token *token, size_t *i,
			t_count count, char ***g_env);
int		ft_expand_exit_status(char **token_value,
			size_t *i, int count_pipe);
int		ft_check_expand_token(char **token_value, size_t *i,
			char type, char ***g_env);
int		ft_expand_token(char *key, char *value, char **token_value, size_t *i);

//expandor_utils.c
int		ft_get_split_pos(char *token_value, size_t cur_pos, char type);

//heredoc.c
int		ft_read_heredoc(t_token *token, t_count *count, char ***g_env);
int		ft_heredoc_get_input(t_token *token, int fd,
			t_count *count, char ***g_env);
int		ft_handle_heredoc_signal(int fd, char *str);
int		ft_heredoc_expandor(char **str, t_count *count, char ***g_env);
void	ft_unlink_heredoc(int count);

//heredoc_utils.c
void	ft_itoa_array_uint(unsigned int n, char res[]);

//parser.c
int		ft_parser(t_list *token_list, t_list **command_table, t_count count);
void	ft_lst_split_pipe(t_list *current_cmd_head, int *nbr_arg,
			t_list **next_cmd_head, int *nbr_redir);
int		ft_get_command_line(t_command_line **command_line,
			t_list *current_cmd_head);

//parser_utils.c
int		ft_create_command_table(t_list **command_table, t_count count,
			t_command_line **command_line, t_list *current_cmd_head);
int		ft_initialize_command_line(t_command_line **command_line);
int		ft_check_token_value(t_command_line **command_line, t_list **tmp);
int		ft_dup_token_value(t_command_line **command_line,
			int token_type, t_token *token);

//executor.c
int		ft_executor(t_list *command_table, t_count count, char ***g_env);
int		ft_executor_line(t_list **tmp, t_fd *fd,
			t_count *count, char ***g_env);
int		ft_dup_fd(t_command_line *command_line, t_fd *fd, t_list *tmp);
void	ft_execute_command_line(t_command_line *command_line,
			t_fd fd, char ***g_env, pid_t pid);
void	ft_get_g_exit_code(t_count count, pid_t *pid);

//executor_utils.c
int		ft_get_cmd_path(t_command_line *command_line, char ***g_env);
int		ft_check_cmd_path(t_command_line *command_line,
			char **path, char ***g_env);
int		ft_strtok_cmd_path(t_command_line *command_line,
			char cmd_path[PATH_MAX], char *token, char *tmp);

#endif