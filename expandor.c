/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expandor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchan <wchan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 14:46:24 by wchan             #+#    #+#             */
/*   Updated: 2023/06/05 16:35:55 by wchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_expandor(t_token *token, t_count count, char ***g_env)
{
	size_t			i;
	size_t			len;

	ft_quote_count(token->value, &count.single_quote, &count.double_quote);
	len = ft_strlen(token->value);
	i = 0;
	token->check.single_quote_open = false;
	token->check.double_quote_open = false;
	while (i < len)
	{
		if (ft_check_expand_char(token, &i, count, g_env))
			return (-1);
		i++;
	}
	return (0);
}

int	ft_check_expand_char(t_token *token, size_t *i,
		t_count count, char ***g_env)
{
	ft_check_quote(token->value[*i], &count,
		&(token->check.single_quote_open),
		&(token->check.double_quote_open));
	if (token->value[*i] == '$'
		&& ((token->check.double_quote_open == 1 && count.double_quote > 0)
			|| (!token->check.single_quote_open
				&& !token->check.double_quote_open)))
	{
		if (token->value[*i + 1] == '?')
		{
			if (ft_expand_exit_status(&token->value, i, count.pipe))
				return (-1);
		}
		else
		{
			if (ft_check_expand_token(&token->value, i, 'c', g_env))
				return (-1);
		}
	}
	return (0);
}

int	ft_expand_exit_status(char **token_value,
			size_t *i, int count_pipe)
{
	char	exit_status[4];
	char	*tmp;

	if (count_pipe > 0)
		ft_strcpy(exit_status, "0");
	else
		ft_itoa_array_uint(g_exit_code, exit_status);
	tmp = (char *)malloc(sizeof(char) * (ft_strlen(*token_value)
				+ ft_strlen(exit_status) - 1));
	if (!tmp)
		return (-1);
	ft_strlcpy(tmp, *token_value, *i + 1);
	ft_strlcat(tmp + *i, exit_status, ft_strlen(tmp)
		+ ft_strlen(exit_status) + 1);
	ft_strlcat(tmp + *i + ft_strlen(exit_status), *token_value + *i + 2,
		ft_strlen(*token_value) + ft_strlen(exit_status) - 1);
	free(*token_value);
	*token_value = tmp;
	return (0);
}

int	ft_check_expand_token(char **token_value, size_t *i,
		char type, char ***g_env)
{
	int		split_pos;
	char	*key;
	char	*value;

	split_pos = ft_get_split_pos(*token_value, *i, type);
	key = ft_substr(*token_value, *i + 1, split_pos);
	if (!key)
		return (-1);
	value = mini_getenv(key, g_env);
	if (value)
	{
		if (ft_expand_token(key, value, token_value, i))
			return (-1);
	}
	else
	{
		if (split_pos)
		{
			ft_memmove(*token_value + *i, *token_value + *i
				+ split_pos + 1, ft_strlen(*token_value) - *i - split_pos);
			(*i)--;
		}
	}
	free(key);
	return (0);
}

int	ft_expand_token(char *key, char *value, char **token_value, size_t *i)
{
	char	*expand_token;
	int		len_key;

	len_key = ft_strlen(key);
	expand_token = (char *)malloc(sizeof(char)
			* (ft_strlen(*token_value) - len_key + ft_strlen(value)));
	if (!expand_token)
	{
		free(key);
		return (-1);
	}
	ft_strlcpy(expand_token, *token_value, *i + 1);
	ft_strlcat(expand_token, value, ft_strlen(expand_token)
		+ ft_strlen(value) + 1);
	ft_strlcat(expand_token, *token_value + len_key + *i + 1,
		(ft_strlen(*token_value) - len_key + ft_strlen(value)));
	free(*token_value);
	*token_value = expand_token;
	*i += ft_strlen(value) - 1;
	return (0);
}
