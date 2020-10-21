// ADD HEADER

#include "minishell.h"

char	**g_env = NULL;
char	**g_env_local = NULL;

int		run_builtin(char **command, int gnl_result)
{
	// Ctrl-D handling
	if (!(*command) && gnl_result)
		return (0);
	else if ((!gnl_result && !(*command)) || !ft_strncmp(*command, "exit", 5))
		ft_exit();
	else if (!ft_strncmp(*command, "cd", 3))
	{
		if (ft_cd(command))
			return (errman(ERR_SYS));
		return (0);
	}
	// Added for testing lexer functionality
	else if (!ft_strncmp(*command, "tok", 3))
	{
		test_tokenize(*command);
		return (0);
	}
	else if (!ft_strncmp(*command, "pwd", 4))
	{
		if (ft_pwd())
			return (errman(ERR_SYS));
		ft_putchar_fd('\n', 1);
		return (0);
	}
	else if (!ft_strncmp(*command, "env", 4))
	{
		if (ft_env())
			return (errman(ERR_SYS));
		return (0);
	}
	else if (!ft_strncmp(*command, "echo", 5))
	{
		if (ft_echo(command))
			return (errman(ERR_SYS));
		return (0);
	}
	return (-1);
}

char    **lexer(char *input)
{
	char	**result;
	char	**temp;

	temp = malloc(sizeof(char *));
	*temp = ft_strdup(input);
	if (!ft_strncmp(input, "tok", 3))
		return (temp);
	else
		result = ft_split(input, ' ');
	return (result);
}

char	**read_input(int *gnl_result)
{
	char	*input;
	char	**result;
	char	*temp;
	char	*temp2;

	result = NULL;
	if ((*gnl_result = get_next_line(0, &input)) < 0)
		return (errman(ERR_SYS) ? NULL : NULL);
	while (input[ft_strlen(input) - 1] == '\\')	// Handling multiline input
	{
		print_prompt2();
		input[ft_strlen(input) - 1] = '\0';
		if ((*gnl_result = get_next_line(0, &temp)) < 0 ||
			!(temp2 = ft_strjoin(input, temp)))
			return (errman(ERR_SYS) ? NULL : NULL);
		free(input);
		free(temp);
		input = temp2;
	}
	if (!(result = lexer(input)))
		return (errman(ERR_SYS) ? NULL : NULL);
	free(input);
	return (result);
}
int		shell_loop(void)
{
	pid_t	child_pid;
	int		stat_loc;
	int		gnl_result;
	char	**command;

	while (1)
	{
		// Print the prompt
		print_prompt();
		command = read_input(&gnl_result);
		// Skip the fork for builtin functions
		if (!run_builtin(command, gnl_result))
			continue ;
		// Fork main process
		if ((child_pid = fork()) < 0)
			return (errman(ERR_SYS));
		else if (child_pid == 0)
		{
			// Do not ignore Ctrl-C in child process
			// Execute command in child process
			if (execve(command[0], command, g_env) < 0)
				return (errman(ERR_SYS));
		}
		else
		{
			signal(SIGINT, SIG_IGN);
			signal(SIGQUIT, SIG_IGN);
			signal(SIGTERM, SIG_IGN);
			// Wait for child process in the parent (main) process
			if (waitpid(child_pid, &stat_loc, WUNTRACED) < 0)
				return (errman(ERR_SYS));
		}
		free(command);
	}
	return (0);
}

/*
** changed main() args because we need an "env" arg
** Also, we need "ac" and "av" args because shell must be able to start
** a script given as an argument (TODO)
*/

int		main(int ac, char **av, char **env)
{
	// Copy env to global g_env. So, we can now add/remove/change env entries
	g_env = env_init(env);
	// Restart shell on Ctrl-C
	if (signal(SIGINT, signal_handler) == SIG_ERR)
		return (errman(ERR_SYS));
	if (signal(SIGQUIT, signal_handler) == SIG_ERR)
		return (errman(ERR_SYS));
	if (signal(SIGTERM, SIG_IGN) == SIG_ERR)
		return (errman(ERR_SYS));
	if (ac == 1)
		shell_loop();
	else if (ac >= 2)
	{
		// Need implement the script execution (TODO)
		// We execute ONLY first script! (it's name is in av[1])
		// and pass all other args av[2], av[3] and so on (if present) to him
//		(void)av;
		printf("%s\n", search_path(av[1]));
	}
	env_free(g_env);
	env_free(g_env_local);
	return (0);
}
