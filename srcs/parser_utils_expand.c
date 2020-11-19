/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_expand.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 23:55:44 by larosale          #+#    #+#             */
/*   Updated: 2020/11/19 02:52:26 by larosale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Helper function for the "concat_tokens" function.
** Appends one token ("read") to another ("token") if the CONCAT flag is set.
*/

static int	append_token(t_token *read, t_token *token)
{
	char *tmp;

	tmp = NULL;
	subst_env(read);
	if (!(tmp = ft_strjoin(token->text, read->text)))
	{
		errman(ERR_SYSCMD, NULL, NULL);
		delete_token(read);
		return (1);
	}
	free(token->text);
	token->text = tmp;
	delete_token(read);
	return (0);
}

/*
** Concatenates tokens (quoted strings, not separated by whitespace).
** Returns 0 on success, or 1 on error.
*/

int			concat_tokens(t_token *token, t_input *in)
{
	t_token	*read;

	while ((read = tokenize_input(in)) && read->concat)
	{
		if (append_token(read, token))
			return (1);
	}
	if (!read || append_token(read, token))
		return (1);
	return (0);
}

/*
** Helper function for "subst_env" function.
** Replaces text string "src" to "dst" in a given token.
** Returns 0 on success, or 1 on error.
*/

static int	replace_env_token(t_token *token, char *src, char *dst)
{
	char	*tmp;
	int		mem_alloc;

	mem_alloc = 0;
	if (!dst && !ft_strncmp(src, "$?", 2))
	{
		if (!(dst = ft_itoa(g_status)))
		{
			errman(ERR_SYSCMD, NULL, NULL);
			return (1);
		}
		mem_alloc = 1;
	}
	if (!(tmp = ft_strsubst(token->text, src, dst)))
	{
		errman(ERR_SYSCMD, NULL, NULL);
		mem_alloc ? free(dst) : 0;
		return (1);
	}
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

int			subst_env(t_token *token)
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
		if (*(tmp + 1) == '?' && !replace_env_token(token, "$?", NULL))
			return (subst_env(token));
		else if (*(tmp + 1) && (ft_isalnum(*(tmp + 1)) || *(tmp + 1) == '_'))
		{
			env_name[0] = '$';
			while (*++tmp && (ft_isalnum(*tmp) || *tmp == '_'))
				env_name[i++] = *tmp;
			env_value = env_get_var(&env_name[1]);
			if (!replace_env_token(token, env_name, env_value))
				return (subst_env(token));
		}
	}
	return (0);
}
