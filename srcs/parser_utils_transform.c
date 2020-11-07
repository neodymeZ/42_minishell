/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_transform.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 23:38:16 by larosale          #+#    #+#             */
/*   Updated: 2020/11/07 14:48:51 by gejeanet         ###   ########.fr       */
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
		if (!(tmp = ft_strjoin(token->text, read->text)))
			errman(ERR_SYS, NULL);
		free(token->text);
		token->text = tmp;
		delete_token(read);
	}
	if (!(tmp = ft_strjoin(token->text, read->text)))
		errman(ERR_SYS, NULL);
	free(token->text);
	token->text = tmp;
	delete_token(read);
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
		env_name[0] = '$';
		while (*++tmp && (ft_isalnum(*tmp) || *tmp == '_'))
			env_name[i++] = *tmp;
		env_value = env_get_var(&env_name[1]);
		if (env_name[1])
		{
			if (!(tmp = ft_strsubst(token->text, env_name, env_value)))
				errman(ERR_SYS, NULL);
			free(token->text);
			token->text = tmp;
		}
		if (ft_strchr(token->text, '$'))
			subst_env(token);
	}
	return (0);
}
