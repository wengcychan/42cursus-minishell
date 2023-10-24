/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchan <wchan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 16:13:47 by wchan             #+#    #+#             */
/*   Updated: 2023/06/02 15:22:04 by wchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_lexer(char *s, t_list **token_list, t_count *count, char ***g_env)
{
	t_token	*token;
	t_token	*prev_token;
	int		check;

	ft_quote_count(s, &count->single_quote, &count->double_quote);
	token = NULL;
	while (*s)
	{
		prev_token = token;
		if (ft_create_token_list(token_list, count, &token))
			return (-1);
		if (ft_get_token_value(&s, token, count))
			return (ft_err(count->heredoc, MALLOC, *token_list, NULL));
		if (ft_get_token_type(token, *count, prev_token, token_list))
			return (-1);
		check = ft_check_heredoc_and_expandor(token, count, prev_token, g_env);
		if (check == -1)
			return (ft_open_heredoc_err(count->heredoc, strerror(errno),
					token_list));
		else if (check == 1 || check == 2)
			return (ft_err(count->heredoc, check, *token_list, NULL));
	}
	if (token->type != STR)
		return (ft_err(count->heredoc, SYNTAX, *token_list, NULL));
	return (0);
}

int	ft_get_token_value(char **s, t_token *token, t_count *count)
{
	t_token_check	check;
	int				spec_char_pos;

	count->token_char = 0;
	spec_char_pos = 0;
	check.single_quote_open = false;
	check.double_quote_open = false;
	check.multiple_spec_char = false;
	check.digit = true;
	while (**s == ' ')
		(*s)++;
	while (**s != '\0')
	{
		if (ft_check_token_char(s, count, &check, &spec_char_pos))
			break ;
		(*s)++;
	}
	token->value = ft_strndup(*s - count->token_char, count->token_char);
	if (!token->value)
		return (-1);
	while (**s == ' ')
		(*s)++;
	return (0);
}

int	ft_check_token_char(char **s, t_count *count,
			t_token_check *check, int *spec_char_pos)
{
	ft_check_quote(**s, count, &(check->single_quote_open),
		&(check->double_quote_open));
	if (**s == ' ' && !check->single_quote_open && !check->double_quote_open)
		return (-1);
	if (ft_isdigit(**s) == 0 && **s != '<' && **s != '>')
		check->digit = false;
	if ((**s == '|' || **s == '<' || **s == '>')
		&& !check->single_quote_open && !check->double_quote_open)
	{
		if (**s == '|')
			count->pipe++;
		if (*spec_char_pos != 0 && !check->digit && !check->multiple_spec_char)
			return (-1);
		else if (*(*s + 1) != '|' && *(*s + 1) != '<' && *(*s + 1) != '>')
		{
			count->token_char++;
			(*s)++;
			return (-1);
		}
		check->multiple_spec_char = true;
	}
	(*spec_char_pos)++;
	count->token_char++;
	return (0);
}

int	ft_get_token_type(t_token *token, t_count count,
	t_token *prev_token, t_list **token_list)
{
	token->double_symbol = false;
	ft_quote_count(token->value, &count.single_quote, &count.double_quote);
	if (ft_strstr(token->value, "|") && !count.single_quote
		&& !count.double_quote)
	{
		token->type = PIPE;
		if (ft_strlen(token->value) > 1)
			return (ft_err(count.heredoc, SYNTAX, *token_list, NULL));
	}
	else if ((ft_strstr(token->value, "<") || ft_strstr(token->value, ">"))
		&& !count.single_quote && !count.double_quote)
	{
		if (ft_get_token_redir_type(token))
			return (ft_err(count.heredoc, SYNTAX, *token_list, NULL));
	}
	else
		token->type = STR;
	if (!prev_token && token->type == PIPE)
		return (ft_err(count.heredoc, SYNTAX, *token_list, NULL));
	if (prev_token && prev_token->type == PIPE && token->type == PIPE)
		return (ft_err(count.heredoc, SYNTAX, *token_list, NULL));
	if (prev_token && (prev_token->type == REDIR_IN
			|| prev_token->type == REDIR_OUT) && token->type != STR)
		return (ft_err(count.heredoc, SYNTAX, *token_list, NULL));
	return (0);
}

int	ft_check_heredoc_and_expandor(t_token *token, t_count *count,
		t_token *prev_token, char ***g_env)
{
	int	check_heredoc;

	if (prev_token && (prev_token->type == REDIR_IN
			&& prev_token->double_symbol))
	{
		check_heredoc = ft_read_heredoc(token, count, g_env);
		if (check_heredoc == 1 || check_heredoc == 2)
			count->heredoc++;
		if (check_heredoc)
			return (check_heredoc);
	}
	else if (token->type == STR)
	{
		if (ft_expandor(token, *count, g_env))
			return (1);
		ft_remove_quote(token);
	}
	return (0);
}
