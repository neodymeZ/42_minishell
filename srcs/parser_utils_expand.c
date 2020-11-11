/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_expand.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 23:55:44 by larosale          #+#    #+#             */
/*   Updated: 2020/11/11 00:01:13 by larosale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Concatenates tokens (quoted strings, not separated by whitespace).
** Returns 0 on success, or calls errman on error.
*/

int		concat_tokens(t_token *token, t_input *in)
{
	t_token	*read;
	char	*tmp;

	tmp = NULL;
	while ((read = tokenize_input(in)) && read->concat)
	{
		subst_env(read);
		if (!(tmp = ft_strjoin(token->text, read->text)))
			errman(ERR_SYS, NULL);
		free(token->text);
		token->text = tmp;
		delete_token(read);
	}
	subst_env(read);
	if (!(tmp = ft_strjoin(token->text, read->text)))
		errman(ERR_SYS, NULL);
	free(token->text);
	token->text = tmp;
	delete_token(read);
	return (0);
}

/*
** Helper function for "subst_env" function.
** Replaces text string "src" to "dst" in a given token.
** Returns 0 on success, or calls errman on error.
*/

static int	replace_env_token(t_token *token, char *src, char *dst)
{
	char	*tmp;

	if (!dst)
	{
		if (!(dst = ft_itoa(g_status)))
			errman(ERR_SYS, NULL);
	}
	if (!(tmp = ft_strsubst(token->text, src, dst)))
		errman(ERR_SYS, NULL);
	free(token->text);
	token->text = tmp;
	return (0);
}

/*
** Substitutes environment variable reference (starting with $) to the env
** variable value.
** If a substitution was made, the function recursively calls itself for
** further token processing.
** Returns 0 on success.
*/

int		subst_env(t_token *token)
{
	char	*tmp;
	char	env_name[256];
	char	*env_value;
	int		i;

	i = 1;
	ft_memset(env_name, 0, 256);
	if ((token->type == STR || token->type == STRDQ) &&
		(tmp = ft_strchr(token->text, '$')))
	{
		if (*(tmp + 1) == '?')
		{
			replace_env_token(token, "$?", NULL);
			return (subst_env(token));
		}
		else if (*(tmp + 1) && (ft_isalnum(*(tmp + 1)) || *(tmp + 1) == '_'))
		{
			env_name[0] = '$';
			while (*++tmp && (ft_isalnum(*tmp) || *tmp == '_'))
				env_name[i++] = *tmp;
			env_value = env_get_var(&env_name[1]);
			replace_env_token(token, env_name, env_value);
			return (subst_env(token));
		}
	}
	return (0);
}
