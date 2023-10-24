/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchan <wchan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 16:13:47 by wchan             #+#    #+#             */
/*   Updated: 2023/06/02 14:14:52 by wchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_parser(t_list *token_list, t_list **command_table, t_count count)
{
	t_list			*current_cmd_head;
	t_list			*next_cmd_head;
	t_command_line	*command_line;

	current_cmd_head = token_list;
	next_cmd_head = current_cmd_head;
	command_line = NULL;
	while (next_cmd_head)
	{
		if (ft_create_command_table(command_table, count,
				&command_line, current_cmd_head))
			return (-1);
		ft_lst_split_pipe(current_cmd_head, command_line->nbr_arg,
			&next_cmd_head, &(command_line->nbr_redir));
		if (ft_get_command_line(&command_line, current_cmd_head))
			return (ft_err(count.heredoc, MALLOC,
					current_cmd_head, command_table));
		ft_lstiter(current_cmd_head, &ft_free_token);
		ft_lstclear(&current_cmd_head, &ft_del_list);
		current_cmd_head = next_cmd_head;
	}
	return (0);
}

void	ft_lst_split_pipe(t_list *current_cmd_head, int *nbr_arg,
			t_list **next_cmd_head, int *nbr_redir)
{
	t_token	*token;
	t_list	*tmp;

	nbr_arg[REDIR_IN] = 0;
	nbr_arg[REDIR_OUT] = 0;
	nbr_arg[STR] = 0;
	*nbr_redir = 0;
	tmp = current_cmd_head;
	while (tmp)
	{
		token = (t_token *) tmp->content;
		nbr_arg[token->type]++;
		if (token->type == PIPE)
		{
			nbr_arg[STR] -= nbr_arg[REDIR_IN] + nbr_arg[REDIR_OUT];
			*nbr_redir = nbr_arg[REDIR_IN] + nbr_arg[REDIR_OUT];
			*next_cmd_head = tmp->next;
			tmp->next = NULL;
			return ;
		}
		tmp = tmp->next;
	}
	nbr_arg[STR] -= nbr_arg[REDIR_IN] + nbr_arg[REDIR_OUT];
	*nbr_redir = nbr_arg[REDIR_IN] + nbr_arg[REDIR_OUT];
	*next_cmd_head = NULL;
}

int	ft_get_command_line(t_command_line **command_line, t_list *current_cmd_head)
{
	t_list	*tmp;
	int		i;

	(*command_line)->count_arg[REDIR_IN] = 0;
	(*command_line)->count_arg[REDIR_OUT] = 0;
	(*command_line)->count_arg[STR] = 0;
	(*command_line)->count_redir_order = 0;
	(*command_line)->redir_order = NULL;
	if (ft_initialize_command_line(command_line))
		return (-1);
	tmp = current_cmd_head;
	while (tmp)
	{
		if (ft_check_token_value(command_line, &tmp))
			return (-1);
		tmp = tmp->next;
	}
	i = REDIR_IN;
	while (i <= STR)
	{
		if ((*command_line)->arg[i].str)
			(*command_line)->arg[i].str[(*command_line)->count_arg[i]] = NULL;
		i++;
	}
	return (0);
}
