/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signalss.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eheike <eheike@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 18:07:29 by sdarci            #+#    #+#             */
/*   Updated: 2022/06/30 20:41:20 by eheike           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Реакция на нажатие Ctrl-"C", Ctrl-"Z" и Ctrl-"\" до раздвоения
void	ms_signal_handler(int sigtype)
{
	if (sigtype == SIGINT)
	{
		ft_putstr_fd("\nVi nazhali \"Ctrl+C\" -- введите команду", 1);
	}
	if (sigtype == SIGTSTP)
		ft_putstr_fd("\nVi nazhali \"Ctrl+Z\"", 1);
	if (sigtype == SIGQUIT)
	{
		ft_putchar_fd('\b', 1);
		ft_putchar_fd('\b', 1);
	}
	if (sigtype == SIGINT || sigtype == SIGTSTP)
	{
		ft_putstr("\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

//Реакция на нажатие Ctrl-"Z" и Ctrl-"\" после раздвоения
static void	ms_signal_only_text(int sigtype)
{
	if (sigtype == SIGTSTP)
		ft_putstr("\nVi nazhali \"Ctrl+Z\"", 1);
	if (sigtype == SIGQUIT)
	{
		ft_putstr_fd("Exit", 1);
		ft_putstr_fd("\nVi nazhali \"Ctrl+\\\"", 1);
	}
	if (sigtype == SIGINT || sigtype == SIGTSTP || sigtype == SIGQUIT)
		ft_putstr_fd("\n", 1);
}

//Реакция на нажатие Ctrl-"C" и Ctrl-"Z" в дочернем процессе
static void	ms_signal_ignore(int sigtype)
{
	(void)sigtype;
}

//Реакция на нажатие Ctrl-"C" в основном и Ctrl-"\" в дочернем процессе
static void	ms_signal_kill_or_exit(int sigtype)
{
	if (sigtype == SIGQUIT)
	{
		printf("EXIT \n");
		exit (131);
	}
	if (sigtype == SIGINT)
	{
		ft_putstr_fd("Kill", 1);
		ft_putstr_fd("\nVi nazhali \"Ctrl+C\"", 1);
		ft_putstr_fd("\n", 1);
	}
}

//Перехват сигналов (type 0 - ожидание, 1 - дочерний, 2 - основной после fork)
void	ms_signals_handler(t_shell *shell, int type, pid_t pid)
{
	int	test;
	int	status;

	status = 0;
	shell->kill_pid = pid;
	if (type == 1)
	{
		signal(SIGINT, ms_signal_ignore);
		signal(SIGTSTP, ms_signal_ignore);
		signal(SIGQUIT, ms_signal_kill_or_exit);
		kill(shell->kill_pid, SIGKILL);
	}
	if (type == 2)
	{
		signal(SIGINT, ms_signal_kill_or_exit);
		signal(SIGTSTP, ms_signal_only_text);
		signal(SIGQUIT, ms_signal_only_text);
	}
	waitpid(pid, &test, 0);
	if (WIFEXITED(test))
		g_lobal_status = 127;
}
