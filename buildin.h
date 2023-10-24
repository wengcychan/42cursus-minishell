/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchan <wchan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 09:45:25 by lidzhang          #+#    #+#             */
/*   Updated: 2023/10/24 15:32:46 by wchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILDIN_H
# define BUILDIN_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <dirent.h>
# include <stdbool.h>

# define BUFF 4096
# define LLONG_MAX 9223372036854775807LL
# define LONG_MAX 9223372036854775807LL
# define INT_MAX 2147483647
# define INT_MIN -2147483648
# define KEY_MAX 32767

int		env_len(char **envip);
void	init_env(int argc, char **argv, char **envip, char ***g_env);
void	print_env(char **g_env);
int		compare_key(char *s1, char *s2);
char	*mini_getenv(char *key, char ***g_env);
int		find_env_key(char *var, char ***g_env);
void	malloc_g_env(char **envip, char ***g_env);
char	**realloc_env(int new_size, char ***g_env);
void	set_env_var(char *key, char *new_value, char ***g_env);
int		unsetenv_builtin(char **argv, char ***g_env);
void	exit_buildin(char **argv, char **g_env);
char	*mini_strnew(size_t size);
int		cd_builtin(char **args, char ***g_env);
int		change_directory(const char *path, char **argv, char ***g_env);
void	str_concat_dst(char *dst, const char *src);
void	process_path_token(char *current_path, char *token);
void	update_env(const char *old_path, const char *new_path, char ***g_env);
char	*replace_tilde(char *path, char ***g_env);
void	ft_strcpy(char *dst, const char *src);
int		echo_builtin(char **argv);
int		export_builtin(char **argv, char ***g_env);
int		builtin_pwd(char **argv, char ***g_env);
int		mini_builtin(char **argv, char ***g_env);
void	ft_free_split(char **strs);
int		invalid_var(char **tmp_split, int free_flag);
int		is_valid_varname(char **argv, char ***g_env);
void	error_message(char *flag);
char	**create_new_env(int size);

#endif
