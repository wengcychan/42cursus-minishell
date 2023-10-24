/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchan <wchan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 16:13:47 by wchan             #+#    #+#             */
/*   Updated: 2023/06/02 14:13:45 by wchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_quote_count(char *s, int *single_quote_count,
			int *double_quote_count)
{
	bool	single_quote_open;
	bool	double_quote_open;

	single_quote_open = false;
	double_quote_open = false;
	*single_quote_count = 0;
	*double_quote_count = 0;
	while (*s)
	{
		if (*s == '\'' && !single_quote_open && !double_quote_open)
			single_quote_open = true;
		else if (*s == '\"' && !single_quote_open && !double_quote_open)
			double_quote_open = true;
		else if (*s == '\'' && single_quote_open)
		{
			(*single_quote_count)++;
			single_quote_open = false;
		}
		else if (*s == '\"' && double_quote_open)
		{
			(*double_quote_count)++;
			double_quote_open = false;
		}
		s++;
	}
}

int	ft_create_token_list(t_list **token_list, t_count *count, t_token **token)
{
	t_list	*new_node;

	(*token) = (t_token *)malloc(sizeof(t_token));
	if (!(*token))
		return (ft_err(count->heredoc, MALLOC, *token_list, NULL));
	new_node = ft_lstnew(*token);
	if (!new_node)
	{
		free((*token));
		return (ft_err(count->heredoc, MALLOC, *token_list, NULL));
	}
	ft_lstadd_back(token_list, new_node);
	return (0);
}

bool	ft_check_quote(char token_value_char, t_count *count,
			bool *single_quote_open, bool *double_quote_open)
{
	bool	valid_quote;

	valid_quote = true;
	if (token_value_char == '\'' && count->single_quote > 0
		&& !*single_quote_open && !*double_quote_open)
		*single_quote_open = true;
	else if (token_value_char == '\"' && count->double_quote > 0
		&& !*single_quote_open && !*double_quote_open)
		*double_quote_open = true;
	else if (token_value_char == '\'' && *single_quote_open)
	{
		count->single_quote--;
		*single_quote_open = false;
	}
	else if (token_value_char == '\"' && *double_quote_open)
	{
		count->double_quote--;
		*double_quote_open = false;
	}
	else
		valid_quote = false;
	return (valid_quote);
}

int	ft_get_token_redir_type(t_token *token)
{
	if (!ft_strcmp(token->value, "<"))
		token->type = REDIR_IN;
	else if (!ft_strcmp(token->value, ">"))
		token->type = REDIR_OUT;
	else if (!ft_strcmp(token->value, "<<"))
	{
		token->type = REDIR_IN;
		token->double_symbol = true;
	}
	else if (!ft_strcmp(token->value, ">>"))
	{
		token->type = REDIR_OUT;
		token->double_symbol = true;
	}
	else
		return (-1);
	return (0);
}

void	ft_remove_quote(t_token *token)
{
	int		i;
	bool	single_quote_open;
	bool	double_quote_open;
	t_count	count;

	ft_quote_count(token->value, &count.single_quote, &count.double_quote);
	if (count.single_quote > 0 || count.double_quote > 0)
	{
		i = 0;
		single_quote_open = false;
		double_quote_open = false;
		while (token->value[i])
		{
			if (ft_check_quote(token->value[i], &count,
					&single_quote_open, &double_quote_open))
			{
				if (token->value[i + 1])
					ft_strcpy(token->value + i, token->value + i + 1);
				else
					token->value[i] = '\0';
			}
			else
				i++;
		}
	}
}
