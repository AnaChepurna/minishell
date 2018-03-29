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

void	init_parser(char **dst, char **content, int *i)
{
	if (*content)
		free(*content);
	*content = ft_strnew(BUFF_SIZE + 1);
	if (dst)
	{
		if (*dst)
			free(*dst);
		*dst = ft_strdup("");
	}
	*i = 0;
	g_stop = 0;
}

int		get_term_line(char **str, int prompt)
{
	char  	c[5];
	char	*content;
	int 	i;

	content = NULL;
	init_parser(NULL, &content, &i);
	while (1)
	{
		ft_memset(c, '\0', 5);
		read(0, c, 4);
		if (g_stop)
			init_parser(str, &content, &i);
		if (ft_strequ(c, "\n"))
			break ;
		if (i == 0 && ft_strequ(c, ""))
			return (eot(content, i, prompt));
		if (ft_strequ(c, "\t"))
			autocomplete(&i, &content, prompt);
		else if (!handle_back_forward(c, &i, content, prompt)
			&& !handle_controls(c, &i, &content, prompt) && *c != '')
			input_str(c, &i, &content, prompt);
	}
	replace(str, ft_strjoin(*str, content));
	carriage_down(ft_wstrlen(content), i, prompt);
	return (1);
}

int		get_term_input(char **str)
{
	char	*input;

	init_term();
	g_stop = 0;
	input = ft_strdup("");
	signal(SIGINT, sigint_handler);
	get_term_line(&input, print_prompt());
	while (!check_quotes(input))
	{
		replace(&input, ft_strjoin(input, "\n"));
		ft_putstr("quote> ");
		get_term_line(&input, 7);
	}
	reset_term();
	*str = input;
	return (1);
}
