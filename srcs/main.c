#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#include <string.h>

# define SH_FG_RED "\033[31m"
# define SH_FG_GREEN "\033[32m"
# define SH_FG_RESET "\033[39m"
# define SH_FG_CYAN "\033[36m"


/*
	./push_swap 8 5 4 7 | ./checher 8 5 4 7
*/

void	test1_left(int *pipefd, char **argv)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		execve("/home/balamosh/school21/42_push_swap/push_swap", argv, NULL);
	}
	else
		waitpid(pid, NULL, 0);
}

void	test1_right(int *pipefd, char **argv)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		execve("/home/balamosh/school21/42_push_swap/checker", argv, NULL);
	}
	else
	{
		close(pipefd[0]);
		close(pipefd[1]);
		waitpid(pid, NULL, 0);
	}
}

void	test1()
{
	int		pipefd[2];
	char	*argv[6] = {"push_swap", "8", "5", "4", "7", NULL};

	pipe(pipefd);
	test1_left(pipefd, argv);
	test1_right(pipefd, argv);
}

/*
	./checker 8 5 4 7 < cat ans.txt | wc -l
*/

void	dup_check(int fd, int oldfd)
{
	if (fd != 0 && fd != 1 && fd != 2)
		dup2(fd, oldfd);
}

void	close_check(int fd)
{
	if (fd != 0 && fd != 1 && fd != 2)
		close(fd);
}

void	test2_checker(int in, int out, char **argv)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		dup_check(in, STDIN_FILENO);
		dup_check(out, STDOUT_FILENO);
		close_check(in);
		close_check(out);
		execve("/home/balamosh/school21/42_push_swap/checker", argv, NULL);
	}
	else
	{
		close_check(in);
		close_check(out);
		waitpid(pid, NULL, 0);
	}
}

void	test2_cat(int in, int out, char **argv)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		dup_check(in, STDIN_FILENO);
		dup_check(out, STDOUT_FILENO);
		close_check(in);
		close_check(out);
		execve("/usr/bin/cat", argv, NULL);
	}
	else
	{
		close_check(in);
		close_check(out);
		waitpid(pid, NULL, 0);
	}
}

void	test2_wc(int in, int out, char **argv)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		dup_check(in, STDIN_FILENO);
		dup_check(out, STDOUT_FILENO);
		close_check(in);
		close_check(out);
		execve("/usr/bin/wc", argv, NULL);
	}
	else
	{
		close_check(in);
		close_check(out);
		waitpid(pid, NULL, 0);
	}
}


void	test2()
{
	int		pipefd_1[2];
	int		pipefd_2[2];
	char	*argv_checker[] = {"checker", "8", "5", "4", "7", NULL};
	char	*argv_cat[] = {"cat", "ans.txt", NULL};
	char	*argv_wc[] = {"wc", "-l", NULL};

	pipe(pipefd_1);
	pipe(pipefd_2);
	test2_cat(0, pipefd_1[1], argv_cat);
	test2_checker(pipefd_1[0], pipefd_2[1], argv_checker);
	test2_wc(pipefd_2[0], 1, argv_wc);
}

char	*get_prompt(void)
{
	char	*prompt;
	char	*username;
	char	*home;
	char	cwd[100];
	int		cwd_start;
	int		n;

	username = getenv("USER");
	home = getenv("HOME");
	getcwd(cwd, 100);
	cwd_start = 0;
	if (strncmp(cwd, home, strlen(home)) == 0)
	{
		cwd_start = strlen(home) - 1;
		cwd[cwd_start] = '~';
	}
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
	strcpy(prompt + n, cwd + cwd_start);
	n += strlen(cwd + cwd_start  );
	strcpy(prompt + n, SH_FG_RESET);
	n += strlen(SH_FG_RESET);
	strcpy(prompt + n, "$ ");
	return (prompt);
}

int	main(void)
{
	char	*line;
	char	*prompt;

	test2();
	return (0);
	prompt = get_prompt();
	while (1)
	{
		//rl_replace_line("", 0);
		//rl_redisplay();
		line = readline(prompt);
		if (line && strlen(line))
			add_history(line);
		if (!(line && line[0] != 'q'))
			break ;
	}
	return (0);
}
