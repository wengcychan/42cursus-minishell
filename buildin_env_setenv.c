/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_env_setenv.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchan <wchan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 10:00:50 by lidzhang          #+#    #+#             */
/*   Updated: 2023/06/07 15:47:03 by wchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**realloc_env(int new_size, char ***g_env)
{
	int		i;
	char	**new_env;

	new_env = create_new_env(new_size);
	if (!new_env)
		return (NULL);
	i = 0;
	while (i < new_size && (*g_env)[i] != NULL)
	{
		new_env[i] = ft_strdup((*g_env)[i]);
		if (!new_env[i])
		{
			while (i-- > 0)
				free(new_env[i]);
			free(new_env);
			return (NULL);
		}
		free((*g_env)[i]);
		i++;
	}
	free(*g_env);
	return (new_env);
}

static void	new_entry(char **arr, int pos, char *key, char *new_value)
{
	char	*tmp;

	tmp = ft_strjoin("=", new_value);
	if (new_value)
		arr[pos] = ft_strjoin(key, tmp);
	else
		arr[pos] = ft_strjoin(key, "=");
	free(tmp);
	tmp = NULL;
}

void	set_env_var(char *key, char *new_value, char ***g_env)
{
	int		pos;
	char	**tmp_env;

	pos = find_env_key(key, g_env);
	if (pos != -1)
	{
		free((*g_env)[pos]);
		new_entry(*g_env, pos, key, new_value);
	}
	else
	{
		pos = env_len((*g_env));
		tmp_env = realloc_env(pos + 1, g_env);
		if (!tmp_env)
			return ;
		new_entry(tmp_env, pos, key, new_value);
		tmp_env[pos + 1] = NULL;
		*g_env = tmp_env;
	}
}
