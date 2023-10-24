/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchan <wchan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 13:43:35 by wchan             #+#    #+#             */
/*   Updated: 2023/10/24 15:33:16 by wchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_get_cmd_path(t_command_line *command_line, char ***g_env)
{
	char		cmd_path[PATH_MAX];
	char		*token;
	char		*tmp;
	char		*path;

	path = NULL;
	if (ft_check_cmd_path(command_line, &path, g_env))
		return (0);
	tmp = command_line->arg[STR].str[0];
	token = ft_strtok(path, ":");
	if (ft_strtok_cmd_path(command_line, cmd_path, token, tmp))
		return (-1);
	return (0);
}

int	ft_check_cmd_path(t_command_line *command_line, char **path, char ***g_env)
{
	struct stat	buffer;

	if (!ft_strcmp(command_line->arg[STR].str[0], ""))
		exit(0);
	if (!stat(command_line->arg[STR].str[0], &buffer))
	{
		if (!ft_strstr(command_line->arg[STR].str[0], "/"))
			ft_open_err("command not found",
				command_line->arg[STR].str[0], 127);
		else if (S_ISDIR(buffer.st_mode))
			ft_open_err("is a directory", command_line->arg[STR].str[0], 126);
		else if (!(buffer.st_mode & S_IRUSR))
			ft_open_err("Permission denied",
				command_line->arg[STR].str[0], 126);
		return (1);
	}
	if (ft_strstr(command_line->arg[STR].str[0], "./")
		|| ft_strstr(command_line->arg[STR].str[0], "/"))
		ft_open_err("No such file or directory",
			command_line->arg[STR].str[0], 127);
	*path = mini_getenv("PATH", g_env);
	if (!*path)
		ft_open_err("No such file or directory",
			command_line->arg[STR].str[0], 127);
	return (0);
}

int	ft_strtok_cmd_path(t_command_line *command_line,
		char cmd_path[PATH_MAX], char *token, char *tmp)
{
	struct stat	buffer;

	while (token)
	{
		ft_strcpy(cmd_path, token);
		str_concat_dst(cmd_path, "/");
		str_concat_dst(cmd_path, command_line->arg[STR].str[0]);
		if (!stat(cmd_path, &buffer) && (S_IFREG & buffer.st_mode))
		{
			command_line->arg[STR].str[0] = ft_strdup(cmd_path);
			if (!command_line->arg[STR].str[0])
				return (-1);
			free(tmp);
			return (0);
		}
		token = ft_strtok(NULL, ":");
	}
	ft_open_err("command not found", command_line->arg[STR].str[0], 127);
	return (0);
}
