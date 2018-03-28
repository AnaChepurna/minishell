/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achepurn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 21:48:06 by achepurn          #+#    #+#             */
/*   Updated: 2018/03/21 21:48:08 by achepurn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int signo)
{
	if (signo == SIGINT)
	{
		ft_putstr("\n");
		print_prompt();
		g_ret_status = 130;
		g_stop = 1;
		signal(SIGINT, sigint_handler);
	}
}

void	sigint_fork_handler(int signo)
{
	if (signo == SIGINT)
	{
		ft_putstr("\n");
		g_ret_status = 130;
		signal(SIGINT, sigint_fork_handler);
	}
}
