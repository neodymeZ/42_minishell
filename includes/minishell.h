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

/*
** Global variables' declarations
*/

extern int	errno;
extern char	**g_env;
extern char	**g_env_local;

/*
** Builtin functions
*/

int			ft_cd(char **command);
int			ft_pwd(void);
void		ft_exit(void);
int			ft_env(void);
int			ft_echo(char **args);
int			ft_export(char **var);
int			ft_unset(char **var);
int			ft_env(void);

/*
** Input handling
*/

t_input		*read_input(void);
int			gnl_ctrl_d(int fd, char **line);

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
char		*search_path(char *arg);
void		print_prompt2(void);
int			check_quotes(char *input);

#endif
