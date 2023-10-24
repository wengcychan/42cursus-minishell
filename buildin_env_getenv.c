/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_env_getenv.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchan <wchan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 10:00:10 by lidzhang          #+#    #+#             */
/*   Updated: 2023/10/24 15:33:08 by wchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	compare_key(char *s1, char *s2)
{
	int	i;

	i = -1;
	while (s2[++i])
		if (s1[i] != s2[i])
			return (0);
	return (1);
}

int	find_env_key(char *var, char ***g_env)
{
	int		i;
	char	tmp[KEY_MAX];

	i = -1;
	while ((*g_env)[++i])
	{
		ft_strcpy(tmp, var);
		str_concat_dst(tmp, "=");
		if (compare_key((*g_env)[i], tmp))
			return (i);
	}
	return (-1);
}

char	*mini_getenv(char *key, char ***g_env)
{
	int		i;
	char	tmp[KEY_MAX];
	char	*dst;

	i = -1;
	while ((*g_env)[++i])
	{
		ft_strcpy(tmp, key);
		str_concat_dst(tmp, "=");
		if (compare_key((*g_env)[i], tmp))
		{
			dst = ft_strchr((*g_env)[i], '=') + 1;
			if (dst[0] == '\0')
				return (NULL);
			return (dst);
		}
	}
	return (NULL);
}
