/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_cd_util1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchan <wchan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 10:01:12 by lidzhang          #+#    #+#             */
/*   Updated: 2023/10/24 15:33:00 by wchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	str_concat_dst(char *dst, const char *src)
{
	while (*dst)
		dst++;
	while (*src)
	{
		*dst = *src;
		dst++;
		src++;
	}
	*dst = '\0';
}

void	process_path_token(char *current_path, char *token)
{
	char	*last_slash;

	if (ft_strcmp(token, "..") == 0)
	{
		last_slash = ft_strrchr(current_path, '/');
		if (last_slash != NULL)
		{
			if (last_slash != current_path)
				*last_slash = '\0';
			else
				*(last_slash + 1) = '\0';
		}
	}
	else
	{
		if (current_path[ft_strlen(current_path) - 1] != '/')
			str_concat_dst(current_path, "/");
		str_concat_dst(current_path, token);
	}
}

void	ft_strcpy(char *dst, const char *src)
{
	while (*src)
	{
		*dst = *src;
		dst++;
		src++;
	}
	*dst = '\0';
}

char	*replace_tilde(char *path, char ***g_env)
{
	char	*home;
	char	*new_path;

	new_path = NULL;
	home = mini_getenv("HOME", g_env);
	if (home)
	{
		new_path = malloc(strlen(home) + strlen(path) + 1);
		if (!new_path)
			return (NULL);
		if (new_path)
		{
			ft_strcpy(new_path, home);
			ft_strlcat(new_path, &path[1], strlen(home) + strlen(path) + 1);
		}
	}
	return (new_path);
}
