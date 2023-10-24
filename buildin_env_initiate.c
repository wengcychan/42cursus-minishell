/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_env_initiate.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lidzhang <lidzhang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 13:28:45 by lidzhang          #+#    #+#             */
/*   Updated: 2023/06/07 14:19:02 by lidzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_len(char **envip)
{
	int		i;
	int		count;

	i = -1;
	count = 0;
	while (envip[++i])
		count++;
	return (count);
}

void	malloc_g_env(char **envip, char ***g_env)
{
	(*g_env) = (char **)malloc(sizeof(char *) * (env_len(envip) + 1));
	if (!(*g_env))
		return ;
	ft_bzero((*g_env), (env_len(envip) + 1));
}

void	init_env(int argc, char **argv, char **envip, char ***g_env)
{
	int	i;
	int	j;

	j = 0;
	(void)argc;
	(void)argv;
	malloc_g_env(envip, g_env);
	i = -1;
	while (envip[++i])
	{
		if (ft_strncmp(envip[i], "OLDPWD=", 7) == 0)
		{
			(*g_env)[j] = ft_strdup("OLDPWD=");
			if (!(*g_env)[j])
				exit_buildin(argv, *g_env);
		}
		else
		{
			(*g_env)[j] = ft_strdup(envip[i]);
			if (!(*g_env)[j])
				exit_buildin(argv, *g_env);
		}
		j++;
	}
	(*g_env)[i] = NULL;
}

void	print_env(char **g_env)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (g_env[i])
	{
		tmp = ft_strchr(g_env[i], '=') + 1;
		if (tmp[0] == '\0')
			i++;
		else
		{
			printf("%s\n", g_env[i]);
			i++;
		}
	}
}
