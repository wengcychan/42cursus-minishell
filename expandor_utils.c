/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expandor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchan <wchan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 14:09:07 by wchan             #+#    #+#             */
/*   Updated: 2023/05/31 14:16:54 by wchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_get_split_pos(char *token_value, size_t cur_pos, char type)
{
	int				i;
	t_token_check	check;
	int				len;

	len = ft_strlen(token_value) - cur_pos;
	token_value = token_value + cur_pos + 1;
	check.single_quote_open = false;
	i = 0;
	while (i < len)
	{
		if (type == 'c' && token_value[i] == '\'' && !check.single_quote_open)
			check.single_quote_open = true;
		if (type == 'c' && token_value[i] == '\'' && check.single_quote_open)
			return (i);
		if (type == 'h' && (token_value[i] == '\'' || token_value[i] == '\n'))
			return (i);
		if (token_value[i] == ' ' || token_value[i] == '\"'
			|| token_value[i] == '$' || token_value[i] == '\0')
			return (i);
		i++;
	}
	return (i);
}
