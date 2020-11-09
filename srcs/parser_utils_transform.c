/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_transform.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 23:38:16 by larosale          #+#    #+#             */
/*   Updated: 2020/11/09 09:09:36 by gejeanet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static int	replace_env_token(t_token *token, char *src, char *dst)
{
	char	*tmp;

	if (!dst)
	{
		if (!(dst = ft_itoa(g_status)))
			return (errman(ERR_SYS, NULL));
	}
	if (!(tmp = ft_strsubst(token->text, src, dst)))
		return (errman(ERR_SYS, NULL));
	free(token->text);
	token->text = tmp;
	return (0);
}

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
