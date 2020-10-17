/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 19:10:19 by larosale          #+#    #+#             */
/*   Updated: 2020/10/17 02:58:18 by gejeanet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	return (-1);
}

char	**lexer(char *input)
{
	char	**result;

	result = ft_split(input, ' ');
	return (result);
}

int		shell_loop(void)
{
	pid_t	child_pid;
	int		stat_loc;
	int		gnl_result;
	char	*input;
	char	**command;

	while (1)
	{
		// Print the prompt
		print_prompt();
		// Get the command with get_next_line and parse it with lexer function
		if ((gnl_result = get_next_line(0, &input)) < 0 || !(command = lexer(input)))
			return (errman(ERR_SYS));
		// Skip the fork for builtin functions
		if (!run_builtin(command, gnl_result))
			continue ;
		// Fork main process
		if ((child_pid = fork()) < 0)
			return (errman(ERR_SYS));
		else if (child_pid == 0)
		{
			// Do not ignore Ctrl-C in child process
			signal(SIGINT, SIG_DFL);
			// Execute command in child process
			if (execve(command[0], command, g_env) < 0)
				return (errman(ERR_SYS));
		}
		else
		{
			// Wait for child process in the parent (main) process
			if (waitpid(child_pid, &stat_loc, WUNTRACED) < 0)
				return (errman(ERR_SYS));
		}
		free(input);
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
	signal(SIGINT, signal_handler);
	signal(SIGTERM, SIG_IGN);
	if (ac == 1)
		shell_loop();
	else if (ac >= 2)
	{
		// Need implement the script execution (TODO)
		// We execute ONLY first script! (it's name is in av[1])
		// and pass all other args av[2], av[3] and so on (if present) to him
		(void)av;
		return (0);
	}
	env_free(g_env);
	env_free(g_env_local);
	return (0);
}
