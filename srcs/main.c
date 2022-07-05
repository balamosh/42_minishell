#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>

#include <string.h>

# define SH_FG_RED "\033[31m"
# define SH_FG_GREEN "\033[32m"
# define SH_FG_RESET "\033[39m"
# define SH_FG_CYAN "\033[36m"

char	*get_prompt(void)
{
	char	*prompt;
	char	*username;
	char	cwd[100];
	int		n;

	username = getenv("USER");
	getcwd(cwd, 100);
	n = 0;
	n += strlen(SH_FG_GREEN);
	n += strlen(username);
	n += strlen(SH_FG_RESET);
	++n;
	n += strlen(SH_FG_CYAN);
	n += strlen(cwd);
	n += strlen(SH_FG_RESET);
	n += 2;
	prompt = (char *) malloc((n + 1) * sizeof(char));
	n = 0;
	strcpy(prompt + n, SH_FG_GREEN);
	n += strlen(SH_FG_GREEN);
	strcpy(prompt + n, username);
	n += strlen(username);
	strcpy(prompt + n, SH_FG_RESET);
	n += strlen(SH_FG_RESET);
	strcpy(prompt + n, ":");
	++n;
	strcpy(prompt + n, SH_FG_CYAN);
	n += strlen(SH_FG_CYAN);
	strcpy(prompt + n, cwd);
	n += strlen(cwd);
	strcpy(prompt + n, SH_FG_RESET);
	n += strlen(SH_FG_RESET);
	strcpy(prompt + n, "$ ");
	return (prompt);
}

int	main(void)
{
	char	*line;
	char	*prompt;

	prompt = get_prompt();
	while (1)
	{
		// rl_replace_line("", 0);
		// rl_redisplay();
		line = readline(prompt);
		if (line && strlen(line))
			add_history(line);
		if (!(line))
			break ;
	}
	return (0);
}
