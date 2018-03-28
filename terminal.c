#include "minishell.h"

static struct termios old, new;

void	init_term(void) 
{
	tcgetattr(0, &old);
	new = old;
	new.c_lflag &= ~ICANON;
	new.c_lflag &= ~ECHO;
	tcsetattr(0, TCSANOW, &new);
}

void	reset_term(void) 
{
	tcsetattr(0, TCSANOW, &old);
}

int		get_width(void)
{
	struct winsize w;

	ioctl(0, TIOCGWINSZ, &w);
	return (w.ws_col);
}

int		get_term_line(char **str, int prompt)
{
	char  	c[5];
	char	*content;
	int 	i;

	prompt = prompt < 0 ? 0 : prompt;
	i = ft_strlen(*str);
	content = *str;//ft_strnew(BUFF_SIZE + 1);
	while (1)
	{
		/*if (g_stop)
		{
			free(content);
			// *str = NULL;
			content = ft_strnew(BUFF_SIZE + 1);
			g_stop = 0;
			return (0);
		} */
		//ft_putnbr(g_stop);
		ft_memset(c, '\0', 5);
		read(0, c, 4);
		if (g_stop)
		{
			free(content);
			// *str = NULL;
			//ft_putendl("sigint2");
			content = ft_strnew(BUFF_SIZE + 1);
			i = 0;
			g_stop = 0;
			//return (get_term_line(str, prompt));
			//return (0);
		}
		if (ft_strequ(c, "\n"))
			break ;
		if (i == 0 && ft_strequ(c, ""))
			return (eot(content, i, prompt));
		if (ft_strequ(c, "\t"))
			autocomplete(&i, &content, prompt);
		else if (!handle_back_forward(c, &i, content, prompt)
			&& !handle_controls(c, &i, &content, prompt) && *c != '')
			input_str(c, &i, &content, prompt);
		//ft_putendl(content);
		/*if (g_stop)
		{
			//free(content);
			// *str = NULL;
			//content = ft_strnew(BUFF_SIZE + 1);
			g_stop = 0;
			ft_putendl("for next input");
			ft_putendl(content);
			ft_putendl(c);
			return (get_term_line(str, prompt));
			//return (0);
		} */
		//
	}
	//ft_putendl(content);
	/*if (g_stop)
		{
			//free(content);
			// *str = NULL;
			//content = ft_strnew(BUFF_SIZE + 1);
			g_stop = 0;
			ft_putendl("sigint3");
			return (get_term_line(str, prompt));
			//return (0);
		} */
	//if (!g_stop)
		//*str = content;
		carriage_down(ft_wstrlen(content), i, prompt);
	return (1);
}

int		get_term_input(char **str)
{
//	char	*content;
	char	*input;
//	char	*buf;
//	int		n;

	init_term();
	//content = NULL;

	g_stop = 0;
	input = ft_strnew(BUFF_SIZE + 1);
	signal(SIGINT, sigint_handler);

	//n = 0;
	//while (!check_quotes(content))
	//{
		//if(n++)
		//if (!g_stop)
	//g_stop = 0;
	//if (!g_stop)
			get_term_line(&input, print_prompt());

		//buf = content;
		//content = ft_strjoin(content, input);
		/*if (buf)
			free(buf);
		if (input)
			free(input);
	}*/
	/*if (!g_stop)
	{
		free(input);
		input = NULL;
	} */
	//ft_putnbr(g_stop);
	reset_term();
	/*if (g_stop)
	{
		free(input);
		// *str = ft_strdup("");
		return (0);
	} */
	//ft_putstr("input is ");
	//ft_putendl(input);
	*str = input;
	return (1);
}

/*int		main(int argc, char const *argv[], char **env)
{
	char *str;

	g_env = NULL;
	g_env = ft_arrtolst(env);
	g_command = NULL;

	while (1)
	{
		get_term_input(&str);
		if (ft_strequ(str, "exit"))
			break ;
		ft_putendl("--------------------------");
		memcommand_manager(ADD, str);
		ft_putendl((char *)g_command->content);
		free(str);
	}
	free(str);
	ft_lstdel(&g_env, &ft_memclr);
	ft_lstdel(&g_command, &ft_memclr);
	return 0;
} */

//
