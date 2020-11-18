/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 01:36:22 by larosale          #+#    #+#             */
/*   Updated: 2020/11/18 19:41:18 by larosale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# define EOL			(-1)
# define NO_EOL			(0)
# define ERRCHAR		( 0)
# define INIT_INPUT_POS	(-2)
# define CONCAT			(1)
# define NO_CONCAT		(0)

/*
** Enum of type "t_token_types" defines types of tokens filled as a result
** of lexical analysis of the input string.
** The types are:
** - STR - plain string;
** - STRDQ - string in double quotes;
** - STRSQ - string in single quotes;
** - PIPE - pipe;
** - REDIR_IN - input redirection;
** - REDIR_OUT - output redirection;
** - REDIR_APP - output redirection (append mode);
** - SEMIC - semicolon;
*/

typedef enum			e_token_types
{
	STR,
	STRDQ,
	STRSQ,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APP,
	SEMIC
}						t_token_types;

/*
** A structure of type "t_input" contains the input buffer, together with its
** length ("size") and the current cursor position in the buffer ("pos"). It
** also stores the result of get_next_line function while reading input.
*/

typedef struct			s_input
{
	char				*buffer;
	int					size;
	int					pos;
}						t_input;

/*
** A structure of type "t_token" contains the token information - the input
** string structure of "t_input" type, together with token length ("len") and
** its text. It also defines the token type, as well as the concatenate flag
** ("concat"), used to concatenate quoted strings not separated by whitespace.
*/

typedef struct			s_token
{
	t_input				*in;
	int					len;
	char				*text;
	t_token_types		type;
	int					concat;
}						t_token;

/*
** A structure of type "t_tokbuf" contains information about token buffer,
** used while tokenizing input: the buffer, its size and current position in
** buffer. It also contains type of the token and concatenate flag (to be
** copied to the token).
*/

typedef struct			s_tokbuf
{
	char				*buffer;
	int					size;
	int					pos;
	t_token_types		type;
	int					concat;
}						t_tokbuf;

/*
** Functions to manipulate the input string
*/

char					next_c(t_input *in);
void					unget_c(t_input *in);
char					peek_c(t_input *in);
t_input					*create_input(char *buffer);
void					delete_input(t_input *input);

/*
** Functions to tokenize the input string
*/

t_token					*null_token(void);
t_token					*create_token(t_tokbuf *buffer, t_input *in);
void					delete_token(t_token *token);
t_token					*tokenize_input(t_input *in);

/*
** Functions to manipulate with token buffer
*/

t_tokbuf				*create_buffer(void);
int						add_to_buffer(char c, t_tokbuf *buffer);
void					delete_buffer(t_tokbuf *buffer);

// TESTING

void					test_tokenize(t_input *in);

#endif
