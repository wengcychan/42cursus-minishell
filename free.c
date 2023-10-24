/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchan <wchan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 15:16:34 by wchan             #+#    #+#             */
/*   Updated: 2023/06/06 14:44:39 by wchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_token(void *content)
{
	t_token	*token;

	token = (t_token *)content;
	free(token->value);
}

void	ft_free_command_table(void *content)
{
	t_command_line	*command_line;
	int				i;
	int				j;

	command_line = (t_command_line *)content;
	i = REDIR_IN;
	while (i <= STR)
	{
		if (command_line->arg[i].str)
		{
			j = 0;
			while (j < command_line->count_arg[i]
				&& command_line->arg[i].str[j])
			{
				free(command_line->arg[i].str[j]);
				j++;
			}
			free(command_line->arg[i].str);
			free(command_line->arg[i].double_symbol);
		}
		i++;
	}
	if (command_line->redir_order)
		free(command_line->redir_order);
}

void	ft_del_list(void *content)
{
	free(content);
}

void	mini_freestrarr(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
	arr = NULL;
}

void	ft_free_split(char **strs)
{
	int	i;

	if (!strs)
		return ;
	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}
