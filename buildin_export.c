/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lidzhang <lidzhang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 21:52:12 by lidanzhang        #+#    #+#             */
/*   Updated: 2023/06/07 14:49:12 by lidzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_export_input(char *var, char ***g_env)
{
	unsigned long	i;
	char			**tmp;

	i = -1;
	tmp = ft_split(var, '=');
	if (ft_atoi(tmp[0]))
		return (invalid_var(tmp, 1));
	else
	{
		while (++i < strlen(tmp[0]))
		{
			if (ft_isalnum(tmp[0][i]) == 0
				&& ft_isalpha(tmp[0][i]) == 0)
				return (invalid_var(tmp, 1));
		}
		set_env_var(tmp[0], tmp[1], g_env);
	}
	ft_free_split(tmp);
	return (0);
}

int	is_valid_varname(char **argv, char ***g_env)
{
	int				j;

	j = 0;
	while (argv[++j])
	{
		if (argv[j][0] == '=')
			return (invalid_var(argv, 0));
		if (check_export_input(argv[j], g_env) != 0)
			return (check_export_input(argv[j], g_env));
		g_exit_code = 0;
	}
	return (0);
}

int	invalid_var(char **tmp_split, int free_flag)
{
	g_exit_code = 1;
	if (free_flag == 1)
		ft_free_split(tmp_split);
	return (1);
}

int	export_builtin(char **argv, char ***g_env)
{
	int		i;
	char	**tmp;

	if (!argv[1])
	{
		i = -1;
		while ((*g_env)[++i])
		{
			tmp = ft_split((*g_env)[i], '=');
			if (tmp[1] == NULL)
				printf("declare -x %s\n", tmp[0]);
			else
				printf("declare -x %s=\"%s\"\n", tmp[0], tmp[1]);
			ft_free_split(tmp);
		}
		return (1);
	}
	if (is_valid_varname(argv, g_env) == 1)
	{
		error_message("export");
		return (is_valid_varname(argv, g_env));
	}
	return (1);
}
