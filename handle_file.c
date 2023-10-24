/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchan <wchan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 18:17:52 by wchan             #+#    #+#             */
/*   Updated: 2023/10/24 15:33:18 by wchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_handle_file_heredoc(int *fd, int *heredoc_open_count)
{
	char		filename[13];
	char		count_str[5];

	ft_itoa_array_uint(*heredoc_open_count, count_str);
	ft_strcpy(filename, "tmp_file");
	str_concat_dst(filename, count_str);
	*fd = open(filename, O_RDONLY);
	unlink(filename);
	(*heredoc_open_count)++;
}

void	ft_handle_file(t_command_line *command_line,
		t_fd *fd, int *heredoc_open_count)
{
	int	i;
	int	open_err;

	open_err = 0;
	i = 0;
	(*command_line).count_arg[REDIR_IN] = 0;
	(*command_line).count_arg[REDIR_OUT] = 0;
	fd->file_in = fd->in;
	while (i < (*command_line).nbr_redir)
	{
		if ((*command_line).redir_order[i] == REDIR_IN)
			ft_handle_infile(fd, command_line, heredoc_open_count, &open_err);
		else
			ft_handle_outfile(fd, command_line, &open_err);
		i++;
	}
}

void	ft_handle_infile(t_fd *fd, t_command_line *command_line,
			int *heredoc_open_count, int *open_err)
{
	if (!command_line->arg[REDIR_IN].double_symbol
		[(*command_line).count_arg[REDIR_IN]])
		fd->in = open(command_line->arg[REDIR_IN].str
			[(*command_line).count_arg[REDIR_IN]],
				O_RDONLY | S_IRUSR);
	else
		ft_handle_file_heredoc(&fd->in, heredoc_open_count);
	if (fd->in == -1)
	{
		if (!*open_err)
		{
			ft_open_err(strerror(errno), command_line->arg[REDIR_IN].str
			[(*command_line).count_arg[REDIR_IN]], 0);
			fd->file_in = fd->in;
		}
		*open_err = 1;
	}
	if ((*command_line).count_arg[REDIR_IN]
		!= command_line->nbr_arg[REDIR_IN] - 1 && fd->in != -1)
		close(fd->in);
	(*command_line).count_arg[REDIR_IN]++;
	if (!*open_err)
		fd->file_in = fd->in;
}

void	ft_handle_outfile(t_fd *fd, t_command_line *command_line, int *open_err)
{
	if (!*open_err)
	{
		if (!command_line->arg[REDIR_OUT].double_symbol
			[(*command_line).count_arg[REDIR_OUT]])
			fd->out = open(command_line->arg[REDIR_OUT].str
				[(*command_line).count_arg[REDIR_OUT]],
					O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
		else
			fd->out = open(command_line->arg[REDIR_OUT].str
				[(*command_line).count_arg[REDIR_OUT]],
					O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
		if (fd->out == -1)
		{
			ft_open_err(strerror(errno), command_line->arg[REDIR_OUT].str
			[(*command_line).count_arg[REDIR_OUT]], 0);
			*open_err = 1;
		}
		if ((*command_line).count_arg[REDIR_OUT]
			!= command_line->nbr_arg[REDIR_OUT] - 1 && fd->out != -1)
			close(fd->out);
	}
	(*command_line).count_arg[REDIR_OUT]++;
}
