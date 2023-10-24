/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchan <wchan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 15:01:34 by wchan             #+#    #+#             */
/*   Updated: 2023/10/24 15:33:22 by wchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_read_heredoc(t_token *token, t_count *count, char ***g_env)
{
	char	filename[13];
	char	count_str[5];
	int		fd;
	int		check_get_input;

	ft_remove_quote(token);
	ft_itoa_array_uint(count->heredoc, count_str);
	ft_strcpy(filename, "tmp_file");
	str_concat_dst(filename, count_str);
	fd = open(filename, O_WRONLY | O_CREAT | O_EXCL | O_TRUNC, 0600);
	if (fd == -1)
		return (-1);
	g_exit_code = -1;
	check_get_input = ft_heredoc_get_input(token, fd, count, g_env);
	if (check_get_input == -1)
		return (2);
	else if (check_get_input == -2)
		return (1);
	g_exit_code = 0;
	close(fd);
	count->heredoc++;
	return (0);
}

int	ft_heredoc_get_input(t_token *token, int fd,
		t_count *count, char ***g_env)
{
	char	*str;

	while (g_exit_code != 130)
	{
		write(1, "> ", 2);
		str = get_next_line(0);
		if (!str)
			return (0);
		if (ft_handle_heredoc_signal(fd, str))
			return (-1);
		if (!ft_strncmp(str, token->value, ft_strlen(token->value))
			&& str[ft_strlen(token->value)] == '\n')
			break ;
		if (ft_heredoc_expandor(&str, count, g_env))
		{
			free(str);
			close(fd);
			return (-2);
		}
		write(fd, str, ft_strlen(str));
		free(str);
	}
	free(str);
	return (0);
}

int	ft_handle_heredoc_signal(int fd, char *str)
{
	if (g_exit_code == 130)
	{
		g_exit_code = 1;
		free(str);
		close(fd);
		return (-1);
	}
	return (0);
}

int	ft_heredoc_expandor(char **str, t_count *count, char ***g_env)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(*str))
	{
		if ((*str)[i] == '$')
		{
			if ((*str)[i + 1] == '?')
			{
				if (ft_expand_exit_status(str, &i, count->pipe))
					return (-1);
			}
			else
			{
				if (ft_check_expand_token(str, &i, 'h', g_env))
					return (-1);
			}
		}
		i++;
	}
	return (0);
}

void	ft_unlink_heredoc(int count)
{
	int		i;
	char	filename[13];
	char	count_str[5];

	i = 0;
	while (i < count)
	{
		ft_itoa_array_uint(i, count_str);
		ft_strcpy(filename, "tmp_file");
		str_concat_dst(filename, count_str);
		unlink(filename);
		i++;
	}
}
