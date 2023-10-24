/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchan <wchan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 18:19:17 by wchan             #+#    #+#             */
/*   Updated: 2023/06/02 18:36:50 by wchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_create_command_table(t_list **command_table, t_count count,
		t_command_line **command_line, t_list *current_cmd_head)
{
	t_list	*new_node;

	(*command_line) = (t_command_line *)malloc(sizeof(t_command_line));
	if (!(*command_line))
		return (ft_err(count.heredoc, MALLOC, current_cmd_head, command_table));
	new_node = ft_lstnew(*command_line);
	if (!new_node)
	{
		free(*command_line);
		return (ft_err(count.heredoc, MALLOC, current_cmd_head, command_table));
	}
	ft_lstadd_back(command_table, new_node);
	return (0);
}

int	ft_initialize_command_line(t_command_line **command_line)
{
	int	i;

	i = REDIR_IN;
	while (i <= STR)
	{
		if (!(*command_line)->nbr_arg[i])
			(*command_line)->arg[i].str = NULL;
		else
		{
			(*command_line)->arg[i].str = (char **)malloc(sizeof(char *)
					* ((*command_line)->nbr_arg[i] + 1));
			if (!(*command_line)->arg[i].str)
				return (-1);
			(*command_line)->arg[i].double_symbol = (bool *)malloc(sizeof(bool)
					* ((*command_line)->nbr_arg[i] + 1));
			if (!(*command_line)->arg[i].double_symbol)
				return (-1);
		}
		i++;
	}
	(*command_line)->redir_order = (t_type *)malloc(sizeof(t_type)
			* (*command_line)->nbr_redir);
	if (!(*command_line)->redir_order)
		return (-1);
	return (0);
}

int	ft_check_token_value(t_command_line **command_line, t_list **tmp)
{
	t_token	*token;
	int		token_type;

	token = (t_token *)(*tmp)->content;
	token_type = token->type;
	if (token_type == REDIR_IN || token_type == REDIR_OUT)
	{
		(*command_line)->arg[token->type].double_symbol
		[(*command_line)->count_arg[token_type]] = token->double_symbol;
		(*command_line)->redir_order
		[(*command_line)->count_redir_order] = token_type;
		(*command_line)->count_redir_order++;
		(*tmp) = (*tmp)->next;
		token = (t_token *)(*tmp)->content;
	}
	if (token_type != PIPE)
	{
		if (ft_dup_token_value(command_line, token_type, token))
			return (-1);
	}
	return (0);
}

int	ft_dup_token_value(t_command_line **command_line,
		int token_type, t_token *token)
{
	if (token_type == STR)
	{
		if (!ft_strcmp(token->value, "")
			&& (*command_line)->nbr_arg[STR] > 1)
			return (0);
	}
	(*command_line)->arg[token_type].str
	[(*command_line)->count_arg[token_type]] = ft_strdup(token->value);
	if (!(*command_line)->arg[token_type].str
		[(*command_line)->count_arg[token_type]])
		return (-1);
	(*command_line)->count_arg[token_type]++;
	return (0);
}
