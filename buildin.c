/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchan <wchan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 21:50:01 by lidanzhang        #+#    #+#             */
/*   Updated: 2023/06/05 16:35:55 by wchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_builtins(char const *s1, char const *s2)
{
	int	cmp;

	if (!s1 || !s2)
		return (0);
	cmp = ft_strncmp(s1, s2, ft_strlen(s2));
	if (cmp == 0)
		return (1);
	return (0);
}

int	mini_builtin(char **argv, char ***g_env)
{
	if (check_builtins(argv[0], "exit"))
		exit_buildin(argv, *g_env);
	else if (check_builtins(argv[0], "echo"))
	{
		g_exit_code = 0;
		return (echo_builtin(argv + 1));
	}
	else if (check_builtins(argv[0], "export"))
		return (export_builtin(argv, g_env));
	else if (check_builtins(argv[0], "pwd"))
		return (builtin_pwd(argv, g_env));
	else if (check_builtins(argv[0], "env"))
	{
		print_env(*g_env);
		g_exit_code = 0;
		return (1);
	}
	else if (check_builtins(argv[0], "cd"))
		return (cd_builtin(argv + 1, g_env));
	else if (check_builtins(argv[0], "unset"))
		return (unsetenv_builtin(argv, g_env));
	return (0);
}
