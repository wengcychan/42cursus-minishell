/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_err.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchan <wchan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 18:20:43 by wchan             #+#    #+#             */
/*   Updated: 2023/06/05 16:35:55 by wchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_err(int heredoc_count, t_err_message message,
		t_list *token_list, t_list **command_table)
{
	ft_lstiter(token_list, &ft_free_token);
	ft_lstclear(&token_list, &ft_del_list);
	if (command_table)
	{
		if (*command_table)
		{
			ft_lstiter(*command_table, &ft_free_command_table);
			ft_lstclear(command_table, &ft_del_list);
		}
	}
	ft_unlink_heredoc(heredoc_count);
	if (message == MALLOC)
		ft_putstr_fd("malloc failed\n", 2);
	else if (message == SYNTAX)
		ft_putstr_fd("syntax error\n", 2);
	if (message != NONE)
		g_exit_code = 2;
	return (-1);
}

int	ft_open_heredoc_err(int heredoc_count, char *message,
		t_list **token_list)
{
	ft_lstiter(*token_list, &ft_free_token);
	ft_lstclear(token_list, &ft_del_list);
	ft_unlink_heredoc(heredoc_count);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
	return (-1);
}

void	ft_open_err(char *error_message, char *file, int g_exit_code)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(error_message, 2);
	ft_putstr_fd("\n", 2);
	if (g_exit_code)
		exit(g_exit_code);
}
