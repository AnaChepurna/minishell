/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achepurn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 21:49:28 by achepurn          #+#    #+#             */
/*   Updated: 2018/03/21 21:49:29 by achepurn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_pwd(void)
{
	char	*pwd;
	char	buf[512];
	char	*home;
	char	*res;
	size_t	len;

	if (ft_strequ(get_var(g_env, "PROMPT_PWD="), "on"))
	{
		pwd = getcwd(buf, 512);
		home = get_var(g_env, "HOME=");
		len = ft_strlen(home);
		if (ft_strnequ(pwd, home, len))
		{
			if ((res = ft_strnew(ft_strlen(pwd) - len + 1)))
			{
				res[0] = '~';
				ft_strcpy(res + 1, pwd + len);
			}
		}
		else
			res = ft_strdup(pwd);
		return (res);
	}
	return (NULL);
}

void	print_prompt(void)
{
	char	*pwd;
	char	*color;

	color = get_color();
	pwd = get_pwd();
	ft_putstr(color);
	ft_putstr("♥" RESET " ");
	if (pwd)
	{
		ft_putstr(":");
		ft_putstr(pwd);
		free(pwd);
	}
	ft_putstr("> ");
}

void	print_error(char *arg, char *msg)
{
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(msg, 2);
	g_status = 1;
}

void	print_arg(char *str)
{
	char *ptr;

	if ((ptr = ft_strstr(str, "$?")))
	{
		while (str < ptr)
			ft_putchar(*(str++));
		ft_putnbr(g_status);
		ft_putstr(str + 2);
	}
	else
		ft_putstr(str);
}

int		echo(char **args)
{
	int		n;

	if (!args)
		ft_putstr("\n");
	else
	{
		n = ft_strequ(*args, "-n");
		if (n)
			args++;
		while (*args)
		{
			print_arg(*args);
			if (*(args + 1))
				ft_putstr(" ");
			args++;
		}
		if (!n)
			ft_putstr("\n");
	}
	return (1);
}
