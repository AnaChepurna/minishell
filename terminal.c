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
	int		width;
	int		len;

	prompt = prompt < 0 ? 0 : prompt;
	i = 0;
	content = ft_strnew(BUFF_SIZE + 1);
	while (1)
	{
		ft_memset(c, '\0', 5);
		read(0, c, 4);
		if (ft_strequ(c, "\n"))
			break ;
		if (!handle_back_forward(c, &i, content, prompt)
			&& !handle_controls(c, &i, &content, prompt))
			input_str(c, &i, &content, prompt);
	}
	*str = content;
	carriage_down(ft_wstrlen(content), i, prompt);
	return (1);
}

int			check_quotes(char *str)
{
	int		res;
	char	c;

	if (!str)
		return (0);
	res = 1;
	c = 0;
	while (*str)
	{
		if (*str == '\'' || *str == '"')
		{
			if (!c)
			{
				c = *str;
				res = 0;
			}
			else if (c == *str)
			{
				c = 0;
				res = 1;
			}
		}
		str++;
	}
	return (res);
}

int		get_term_input(char **str)
{
	char	*content;
	char	*input;
	char	*buf;
	int		n;

	init_term();
	content = NULL;
	input = NULL;
	n = 0;
	//while (!check_quotes(content))
	//{
		//if(n++)
		//	ft_putstr("quote> ");
		get_term_line(&input, 0);
		//buf = content;
		//content = ft_strjoin(content, input);
		/*if (buf)
			free(buf);
		if (input)
			free(input);
	}*/
	*str = input;
	reset_term();
	return (1);
}

int		main(int argc, char const *argv[], char **env)
{
	char *str;

	g_env = NULL;
	g_env = ft_arrtolst(env);

	get_term_input(&str);
	ft_putendl("--------------------------");
	ft_putendl(str);
	free(str);

	ft_lstdel(&g_env, &ft_memclr);
	return 0;
}

//
