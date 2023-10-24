/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchan <wchan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 16:13:47 by wchan             #+#    #+#             */
/*   Updated: 2023/06/05 16:36:35 by wchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	char	command_history[MAX_HISTORY][MAX_INPUT];
	int		command_count;
	char	**g_env;

	g_exit_code = 0;
	g_env = NULL;
	if (argc > 1)
	{
		write(2, "Invalid Input\n", 15);
		exit(1);
	}
	init_env(argc, argv, envp, &g_env);
	line = NULL;
	command_count = 0;
	ft_minishell(line, &g_env, command_history, command_count);
	mini_freestrarr(g_env);
	return (0);
}

void	ft_minishell(char *line, char ***g_env,
		char command_history[MAX_HISTORY][MAX_INPUT], int command_count)
{
	while (1)
	{
		init_signal();
		line = readline(print_prompt());
		if (line == NULL)
		{
			free(line);
			break ;
		}
		if (ft_strlen(line) == 0)
		{
			free(line);
			line = NULL;
			continue ;
		}
		if (ft_strlen(line) > 0)
		{
			ft_strcpy(command_history[command_count], line);
			command_count++;
			add_history(line);
		}
		ft_execute_minishell(line, g_env);
		free(line);
	}
}

void	ft_execute_minishell(char *line, char ***g_env)
{
	t_list	*token_list;
	t_list	*command_table;
	t_count	count;

	token_list = NULL;
	command_table = NULL;
	count.heredoc = 0;
	count.pipe = 0;
	if (ft_lexer(line, &token_list, &count, g_env))
		return ;
	if (ft_parser(token_list, &command_table, count))
		return ;
	if (ft_executor(command_table, count, g_env))
	{
		g_exit_code = 1;
		ft_lstiter(command_table, &ft_free_command_table);
		ft_lstclear(&command_table, &ft_del_list);
		return ;
	}
	ft_lstiter(command_table, &ft_free_command_table);
	ft_lstclear(&command_table, &ft_del_list);
}
