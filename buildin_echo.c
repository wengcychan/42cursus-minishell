/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchan <wchan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 22:29:09 by lidanzhang        #+#    #+#             */
/*   Updated: 2023/06/05 12:56:41 by wchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	echo_out(char **str, int pos)
{
	int		str_len;

	str_len = (int)ft_strlen(str[pos]);
	if (str[pos + 1])
		ft_printf("%s ", str[pos]);
	else
		ft_printf("%s", str[pos]);
}

int	echo_builtin(char **argv)
{
	int		i;
	int		n_flag;

	n_flag = 0;
	i = -1;
	if (!argv[0])
	{
		ft_printf("\n");
		return (1);
	}
	if (argv[0][0] == '-' && argv[0][1] == 'n' && argv[0][2] == '\0')
	{
		if (!argv[1])
			return (1);
		n_flag = 1;
		i = 0;
	}
	while (argv[++i])
		echo_out(argv, i);
	if (!n_flag)
		ft_printf("\n");
	return (1);
}
