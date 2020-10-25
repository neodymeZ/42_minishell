// ADD HEADER

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <stdio.h>
# include <signal.h>
# include "libft.h"
# include "errors.h"
# include "lexer.h"
# include "parser.h"
# include "executor.h"
# include "builtin.h"

/*
** Global variables' declarations
*/

extern int		errno;
extern char		**g_env;
extern char		**g_env_local;

/*
** Input handling
*/

t_input		*read_input(void);
int			gnl_wrapper(int fd, char **line);
int			check_quotes(char *input);

/*
** Signal handlers
*/

void   		signal_handler(int signo);

/*
** Environment handling
*/

char		**env_init(char **env);
void		env_free(char **env);
void		env_del_var(char *var, char **env);
void		env_set_var(char *var, char *value, char **env);
char		*env_get_var(char *var);

/*
** Utils
*/

void		print_prompt(void);
void		print_prompt2(void);

#endif
