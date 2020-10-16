/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 01:36:22 by larosale          #+#    #+#             */
/*   Updated: 2020/10/15 01:24:57 by larosale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# define EOL			(-1)
# define ERRCHAR		( 0)
# define INIT_SRC_POS	(-2)

/*
** A structure of type "t_input" contains the input buffer, together with its
** length ("size") and the current cursor position in the buffer ("pos").
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
** its text.
*/

typedef struct			s_token
{
	t_input				*in;
	int					len;
	char				*text;
}						t_token;

/*
** A structure of type "t_tokbuf" contains information about token buffer,
** used while tokenizing input: the buffer, its size and current position in
** buffer.
*/


typedef struct			s_tokbuf
{
	char				*buffer;
	int					size;
	int					pos;
}						t_tokbuf;

/*
** Functions to manipulate the input string
*/

char					next_c(t_input *in);
void					unget_c(t_input *in);
char					peek_c(t_input *in);
void					skip_white(t_input *in);

/*
** Functions to tokenize the input string
*/

t_token					*null_token(void);
t_token					*create_token(char *str);
void					delete_token(t_token *token);
t_token					*tokenize_input(t_input *in);

// TESTING

void					test_tokenize(char *input);

#endif
