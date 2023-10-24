/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_env_unset.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lidzhang <lidzhang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 11:36:43 by lidzhang          #+#    #+#             */
/*   Updated: 2023/06/07 13:06:07 by lidzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_message(char *flag)
{
	g_exit_code = 1;
	write(STDERR_FILENO, flag, ft_strlen(flag));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, "not a valid identifier", 22);
	write(STDERR_FILENO, "\n", 1);
}

char	**create_new_env(int size)
{
	char	**new_env;

	new_env = (char **)malloc(sizeof(char *) * (size + 1));
	if (!new_env)
		return (NULL);
	return (new_env);
}

static int	check_input(char *var, char ***g_env)
{
	unsigned long	i;
	char			**tmp;
	unsigned int	flag;

	i = -1;
	tmp = ft_split(var, '=');
	if (ft_atoi(tmp[0]))
		return (invalid_var(tmp, 1));
	else
	{
		while (++i < strlen(tmp[0]))
		{
			if (ft_isalnum(tmp[0][i]) == 0
				&& ft_isalpha(tmp[0][i]) == 0)
				return (invalid_var(tmp, 1));
		}
		if (find_env_key(tmp[0], g_env) == -1
			&& ft_strlen(tmp[0]) != ft_strlen(var))
			return (invalid_var(tmp, 1));
	}
	ft_free_split(tmp);
	return (0);
}

static int	copy_env_vars(char *key, char ***g_env, char **new_env)
{
	int	j;
	int	k;

	j = -1;
	k = 0;
	while ((*g_env)[++j])
	{
		if (!ft_strncmp((*g_env)[j], key, ft_strlen(key))
			&& (*g_env)[j][ft_strlen(key)] == '=')
			continue ;
		new_env[k] = ft_strdup((*g_env)[j]);
		if (!new_env[k])
		{
			mini_freestrarr(new_env);
			g_exit_code = 1;
			return (-1);
		}
		k++;
	}
	new_env[k] = NULL;
	return (1);
}

int	unsetenv_builtin(char **argv, char ***g_env)
{
	int		i;
	char	**new_env;

	i = 0;
	g_exit_code = 0;
	if (!argv[1])
		return (1);
	while (argv[++i])
	{
		if (check_input(argv[i], g_env))
		{
			error_message(argv[i]);
			return (-1);
		}
		new_env = create_new_env(env_len(*g_env) - 1);
		if (!new_env)
			return (-1);
		if (copy_env_vars(argv[i], g_env, new_env) == -1)
			return (-1);
		mini_freestrarr(*g_env);
		*g_env = new_env;
	}
	return (1);
}
