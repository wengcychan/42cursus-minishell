/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchan <wchan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 09:50:23 by lidanzhang        #+#    #+#             */
/*   Updated: 2023/06/05 16:35:55 by wchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	process_sign(char **str)
{
	int	sign;

	sign = 1;
	if (**str == '-' || **str == '+')
	{
		if (**str == '-')
			sign = -1;
		(*str)++;
	}
	return (sign);
}

static long long	ft_atoll(char *str, int *err_flag, int *overflow_flag)
{
	long long	n;
	int			sign;

	n = 0;
	sign = process_sign(&str);
	*err_flag = 0;
	*overflow_flag = 0;
	while (*str >= '0' && *str <= '9')
	{
		if ((sign > 0 && n > (LLONG_MAX - (*str - '0')) / 10)
			|| (sign < 0 && - n < (-LLONG_MAX - 1 + (*str - '0')) / 10))
		{
			*overflow_flag = 1;
			ft_putstr_fd(" numeric argument required\n", 2);
			return (0);
		}
		n = n * 10 + *str - '0';
		str++;
	}
	if (*str != '\0')
	{
		*err_flag = 1;
		ft_putstr_fd(" numeric argument required\n", 2);
	}
	return (sign * n);
}

static void	exit_message(void)
{
	ft_putstr_fd(" too many arguments\n", 2);
	exit(1);
}

void	exit_buildin(char **argv, char **g_env)
{
	long long	exit_status;
	int			err_flag;
	int			overflow_flag;

	err_flag = 0;
	overflow_flag = 0;
	if (argv[1] != NULL && argv[2] != NULL)
		exit_message();
	else if (argv[1] != NULL)
	{
		exit_status = ft_atoll(argv[1], &err_flag, &overflow_flag);
		if (err_flag == 1 || overflow_flag == 1)
			g_exit_code = 255;
		else
		{
			if (exit_status < 0 && exit_status > -LLONG_MAX -1)
				g_exit_code = (256 + exit_status) % 256;
			else
				g_exit_code = exit_status % 256;
		}
	}
	mini_freestrarr(g_env);
	exit(g_exit_code);
}
