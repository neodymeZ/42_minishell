// ADD HEADER

#include "minishell.h"

/*
** Global variables' definition.
*/

char	**g_env = NULL;
char	**g_env_local = NULL;
t_token	*g_null_token = NULL;

/*
** Reads input string using GNL and creates the structure of type "t_input"
** to hold the string, its length, current reading position and other params.
** Returns the structure on success, or NULL on error.
*/

t_input	*read_input(void)
{
	char	*input;
	char	*temp;
	char	*temp2;
	int		gnl_res;
	t_input	*in;

	if ((gnl_res = gnl_wrapper(0, &input)) < 0)
		return (errman(ERR_SYS) ? NULL : NULL);
	while (input[ft_strlen(input) - 1] == '\\' || check_quotes(input))	// Handling multiline input
	{
		print_prompt2();
		if (input[ft_strlen(input) - 1] == '\\')
			input[ft_strlen(input) - 1] = '\0';
		if ((gnl_res = gnl_wrapper(0, &temp)) < 0 ||
			!(temp2 = ft_strjoin(input, temp)))
			return (errman(ERR_SYS) ? NULL : NULL);
		free(input);
		free(temp);
		input = temp2;
	}
	in = create_input(input);
	in->gnl_res = gnl_res;
	free(input);
	return (in);
}

/*
** Starts main minishell loop of reading input, parsing and executing it.
*/

int		shell_loop(void)
{
	t_input	*in;
	t_token	*token;
	t_node	*cmd;

	while (1)
	{
		print_prompt();
		in = read_input();
		g_null_token = null_token();
		// Added for lexer testing. Remove before submitting
		if (!ft_strncmp(in->buffer, "lexer", 5))
		{
			test_tokenize(in);
			continue ;
		}
		// Added for parser testing. Remove before submitting
		if (!ft_strncmp(in->buffer, "parser", 6))
		{
			test_parser(in);
			continue ;
		}
		//replace by
//		cmd = parse_input(in);
//		run_cmd(cmd);
//		delete_tree(cmd);
		while ((token = tokenize_input(in)) &&
			ft_memcmp(token, g_null_token, sizeof(t_token)))
		{
			// check the parse_input function return value
			cmd = parse_temp(token);
			run_simplecom(cmd, in->gnl_res);
			delete_tree(cmd);
		}
	}
	return (0);
}

int		main(int argc, char **argv, char **env)
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
	if (argc == 1)
		shell_loop();
	else if (argc >= 2)
	{
		// Need implement the script execution (TODO)
		// We execute ONLY first script! (it's name is in av[1])
		// and pass all other args av[2], av[3] and so on (if present) to him
		printf("%s\n", search_path(argv[1]));
	}
	env_free(g_env);
	env_free(g_env_local);
	return (0);
}
