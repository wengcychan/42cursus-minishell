/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchan <wchan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 16:18:43 by wchan             #+#    #+#             */
/*   Updated: 2023/06/06 16:06:15 by wchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_executor(t_list *command_table, t_count count, char ***g_env)
{
	t_fd	fd;
	t_list	*tmp;
	pid_t	pid[PID_MAX];

	fd.default_in = dup(STDIN_FILENO);
	fd.default_out = dup(STDOUT_FILENO);
	fd.in = fd.default_in;
	fd.out = fd.default_out;
	tmp = command_table;
	count.heredoc_open = 0;
	count.cur_pipe = 0;
	while (tmp)
	{
		pid[count.cur_pipe] = ft_executor_line(&tmp, &fd, &count, g_env);
		if (pid[count.cur_pipe] == -1)
			return (-1);
		count.cur_pipe++;
		tmp = tmp->next;
	}
	dup2(fd.default_in, STDIN_FILENO);
	dup2(fd.default_out, STDOUT_FILENO);
	close(fd.default_in);
	close(fd.default_out);
	ft_get_g_exit_code(count, pid);
	return (0);
}

int	ft_executor_line(t_list **tmp, t_fd *fd,
		t_count *count, char ***g_env)
{
	t_command_line	*command_line;
	pid_t			pid;

	command_line = (t_command_line *)(*tmp)->content;
	ft_handle_file(command_line, fd, &count->heredoc_open);
	if (ft_dup_fd(command_line, fd, *tmp))
	{
		perror("pipe failed");
		return (-1);
	}
	if (!count->pipe && mini_builtin(command_line->arg[STR].str, g_env))
	{
		if (fd->file_in == -1 || fd->out == -1)
			g_exit_code = 1;
		return (-2);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork failed");
		return (-1);
	}
	ft_execute_command_line(command_line, *fd, g_env, pid);
	return (pid);
}

int	ft_dup_fd(t_command_line *command_line, t_fd *fd, t_list *tmp)
{
	dup2(fd->in, 0);
	if (fd->in != -1 && fd->in != fd->default_in)
		close(fd->in);
	if (fd->in != fd->pipe[0] && fd->pipe[0] && command_line->nbr_arg[REDIR_IN])
		close(fd->pipe[0]);
	if (tmp->next)
	{
		if (pipe(fd->pipe) == -1)
			return (-1);
		fd->in = fd->pipe[0];
	}
	if (!command_line->nbr_arg[REDIR_OUT])
	{
		if (tmp->next)
			fd->out = fd->pipe[1];
		else
			fd->out = dup(fd->default_out);
	}
	dup2(fd->out, 1);
	if (fd->out != -1 && fd->out != fd->default_out)
		close(fd->out);
	if (command_line->nbr_arg[REDIR_OUT] && tmp->next)
		close(fd->pipe[1]);
	return (0);
}

void	ft_execute_command_line(t_command_line *command_line,
			t_fd fd, char ***g_env, pid_t pid)
{
	init_signal_child();
	if (pid == 0)
	{
		if (fd.in != -1 && fd.in != fd.default_in)
			close(fd.in);
		if (fd.file_in == -1 || fd.out == -1)
			exit(1);
		if (mini_builtin(command_line->arg[STR].str, g_env))
			exit(g_exit_code);
		else
		{
			if (ft_get_cmd_path(command_line, g_env))
			{
				ft_putstr_fd("malloc failed\n", 2);
				exit(2);
			}
			if (execve(command_line->arg[STR].str[0],
					command_line->arg[STR].str, *g_env) == -1)
			{
				perror("execve: ");
				exit(127);
			}
		}
	}
}

void	ft_get_g_exit_code(t_count count, pid_t *pid)
{
	int		i;
	int		status;

	if (*pid != -2)
	{
		i = 0;
		while (i < (count.pipe) + 1)
		{
			waitpid(pid[i], &status, 0);
			i++;
		}
		waitpid(pid[count.pipe], &status, 0);
		if (WIFEXITED(status))
			g_exit_code = WEXITSTATUS(status);
	}
}
