// ADD HEADER

#include "minishell.h"

char	**g_env = NULL;
char	**g_env_local = NULL;

char    **lexer(char *input)
{
	char	**result;
	char	**temp;

	temp = malloc(sizeof(char *));
	*temp = ft_strdup(input);
	if (!ft_strncmp(input, "tok", 3) || !ft_strncmp(input, "parse", 5))
		return (temp);
	else
		result = ft_split(input, ' ');
	return (result);
}

t_input	*read_input(void)
{
	char	*input;
	char	*temp;
	char	*temp2;
	int		gnl_res;
	t_input	*in;

	if ((gnl_res = get_next_line(0, &input)) < 0)
		return (errman(ERR_SYS) ? NULL : NULL);
	while (input[ft_strlen(input) - 1] == '\\' || check_quotes(input))	// Handling multiline input
	{
		print_prompt2();
		if (input[ft_strlen(input) - 1] == '\\')
			input[ft_strlen(input) - 1] = '\0';
		if ((gnl_res = get_next_line(0, &temp)) < 0 ||
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

int		shell_loop(void)
{
	t_input	*in;
	t_token	*token;
	t_token	*null_t;
	t_node	*cmd;

	while (1)
	{
		// Print the prompt
		print_prompt();
		in = read_input();
		null_t = null_token();
		// Added for lexer testing
		if (!ft_strncmp(in->buffer, "lexer", 5))
		{
			test_tokenize(in);
			continue ;
		}
		// Added for parser testing
		if (!ft_strncmp(in->buffer, "parser", 6))
		{
			test_parser(in);
			continue ;
		}
		while ((token = tokenize_input(in)) &&
			ft_memcmp(token, null_t, sizeof(t_token)))
		{
			cmd = parse_simplecom(token);
			run_simplecom(cmd, in->gnl_res);
			delete_tree(cmd);
		}
	}
	return (0);
}

/*
** changed main() args because we need an "env" arg
** Also, we need "ac" and "av" args because shell must be able to start
** a script given as an argument (TODO)
*/

int		main(int argc, char **argv, char **env)
{
	// Copy env to global g_env. So, we can now add/remove/change env entries
	g_env = env_init(env);
	// Restart shell on Ctrl-C
	signal(SIGINT, signal_handler);
	signal(SIGTERM, SIG_IGN);
	if (argc == 1)
		shell_loop();
	else if (argc >= 2)
	{
		// Need implement the script execution (TODO)
		// We execute ONLY first script! (it's name is in av[1])
		// and pass all other args av[2], av[3] and so on (if present) to him
		(void)argv;
		return (0);
	}
	env_free(g_env);
	env_free(g_env_local);
	return (0);
}
