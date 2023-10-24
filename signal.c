/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchan <wchan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 18:12:36 by wchan             #+#    #+#             */
/*   Updated: 2023/06/05 16:36:55 by wchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	rl_replace_line(const char *text, int clear_undo);

char	*print_prompt(void)
{
	return ("\033[1;33mminishell> \033[0m");
}

void	handle_sigint(int sig)
{
	(void)sig;
	if (g_exit_code != -1 && g_exit_code != -2)
	{
		rl_replace_line("", 0);
		ioctl(0, TIOCSTI, "\n");
		rl_on_new_line();
		g_exit_code = 1;
	}
	if (g_exit_code == -1)
	{
		ioctl(0, TIOCSTI, "\n");
		g_exit_code = sig + 128;
	}
	if (g_exit_code == -2)
	{
		write(1, "\n", 1);
		rl_redisplay();
		rl_on_new_line();
		g_exit_code = sig + 128;
	}
}

void	handle_sigquit(int sig)
{
	(void)sig;
	if (g_exit_code == -2)
	{
		rl_replace_line("", 1);
		rl_redisplay();
		write(1, "\n", 1);
		g_exit_code = sig + 128;
		init_signal();
	}
}

void	init_signal(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sa_int.sa_handler = handle_sigint;
	sa_int.sa_flags = SA_RESTART;
	sigemptyset(&sa_int.sa_mask);
	sigaction(SIGINT, &sa_int, NULL);
	sa_quit.sa_handler = SIG_IGN;
	sa_quit.sa_flags = SA_RESTART;
	sigemptyset(&sa_quit.sa_mask);
	sigaction(SIGQUIT, &sa_quit, NULL);
}

void	init_signal_child(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	g_exit_code = -2;
	sa_int.sa_handler = handle_sigint;
	sa_int.sa_flags = SA_RESTART;
	sigemptyset(&sa_int.sa_mask);
	sigaction(SIGINT, &sa_int, NULL);
	sa_quit.sa_handler = handle_sigquit;
	sa_quit.sa_flags = SA_RESTART;
	sigemptyset(&sa_quit.sa_mask);
	sigaction(SIGQUIT, &sa_quit, NULL);
}
