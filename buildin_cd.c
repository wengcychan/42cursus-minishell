/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchan <wchan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 10:53:23 by lidanzhang        #+#    #+#             */
/*   Updated: 2023/06/06 14:52:41 by wchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	if_yes(int status, char ***g_env)
{
	if (status == 0)
	{
		printf("%s\n", mini_getenv("PWD", g_env));
		return (1);
	}
	return (-1);
}

static int	cd_assist(char **argv, char ***g_env)
{
	int		status;
	char	*tmp;

	if (argv[0] == NULL)
		return (if_yes(change_directory((const char *)
					mini_getenv("HOME", g_env), argv, g_env), g_env));
	if (argv[0][0] == '-' && argv[0][1] == '-')
		return (if_yes(change_directory((const char *)
					mini_getenv("HOME", g_env), argv, g_env), g_env));
	else if (argv[0][0] == '~')
	{
		tmp = replace_tilde(argv[0], g_env);
		if (!tmp)
			return (-1);
		status = change_directory((const char *) tmp, argv, g_env);
		free (tmp);
		return (if_yes(status, g_env));
	}
	else if (argv[0][0] == '-' && argv[0][1] == '\0')
		return (if_yes(change_directory((const char *)
					mini_getenv("OLDPWD", g_env), argv, g_env), g_env));
	else
		return (change_directory((const char *)argv[0], argv, g_env) + 1);
}

int	cd_builtin(char **argv, char ***g_env)
{
	int		status;

	status = cd_assist(argv, g_env);
	if (status == 0)
		g_exit_code = 1;
	return (1);
}

int	change_directory(const char *path, char **argv, char ***g_env)
{
	int			status;
	char		old_path[PATH_MAX];
	char		new_path[PATH_MAX];

	getcwd(old_path, sizeof(old_path));
	status = chdir(path);
	if (status == 0)
	{
		getcwd(new_path, sizeof(new_path));
		update_env(old_path, new_path, g_env);
	}
	else
	{
		if (mini_getenv("OLDPWD", g_env) == NULL && argv[0][0] == '-')
			printf("cd: OLDPWD not set\n");
		else
		{
			write(STDERR_FILENO, "bash: cd: ", strlen("bash: cd: "));
			write(STDERR_FILENO, path, strlen(path));
			write(STDERR_FILENO, ": ", 2);
			write(STDERR_FILENO, strerror(errno), strlen(strerror(errno)));
			write(STDERR_FILENO, "\n", 1);
		}
	}
	return (status);
}

void	update_env(const char *old_path, const char *new_path, char ***g_env)
{
	set_env_var("OLDPWD", (char *)old_path, g_env);
	set_env_var("PWD", (char *)new_path, g_env);
}
