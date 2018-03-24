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

int		main(int argc, char const *argv[])
{
	char  	c[5];
	char	*content;
	int 	i;

	init_term();
	i = 0;
	content = NULL;
	while (1)
	{
		ft_memset(c, '\0', 5);
		read(0, c, 4);
		if (ft_strequ(c, "\n"))
			break ;
		if (!handle_back_forward(c, &i, ft_strlen(content))
			&& !handle_controls(c, &i, &content))
			input_str(c, &i, &content);
	}
	ft_putendl("\n-------");
	ft_putendl(content);
	reset_term(); 
	return 0;
}