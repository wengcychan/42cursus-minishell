/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchan <wchan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 21:51:43 by lidanzhang        #+#    #+#             */
/*   Updated: 2023/06/05 16:35:55 by wchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd(char **argv, char ***g_env)
{
	int		pos;
	char	**tmp;
	int		i;

	(void)argv;
	i = 0;
	pos = find_env_key("PWD", g_env);
	if (pos == -1)
		return (1);
	tmp = ft_split((*g_env)[pos], '=');
	if (!tmp)
	{
		g_exit_code = 2;
		ft_putstr_fd("malloc failed\n", 2);
		return (2);
	}
	if (!tmp[0] || !tmp[1])
	{
		ft_free_split(tmp);
		return (3);
	}
	printf("%s\n", tmp[1]);
	ft_free_split(tmp);
	g_exit_code = 0;
	return (1);
}
