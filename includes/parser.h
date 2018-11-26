/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 16:31:26 by tkobb             #+#    #+#             */
/*   Updated: 2018/11/20 18:15:49 by dmendelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <strings.h>
#include <string.h>
#include <libft.h>
#include "grammar.h"
#include "get_next_line.h"
#include <ft_printf.h>

# define IS_SPACE(x) (x == ' ' || x == '\t' || x == '\n')
# define IS_OP(x) (x == '&' || x == '|')
# define IS_SEMI(x) (x == ';')
# define WOW() printf("->%s\n", __func__)
# define REDIRECT_LEFT			1 //rename to heredoc?
# define REDIRECT_RIGHT			2 //rename to redirect?
# define REDIRECT_APPEND_RIGHT	3 //rename to redirect_append? 

# define SEEKING_END 1
# define END 2

# define STDIN 0
# define STDOUT 1
# define STDERR 2

typedef struct					s_redirect
{
	char						type;
	int							fd;
	char						*path;
	struct s_redirect			*next;
}								t_redirect;

# define T_CMD					1
# define T_PIPE					2
# define T_AND					3
# define T_OR					4
# define T_SEMI					5

# define T_ALPHANUM				6
# define T_QUOTE				7
# define T_BRACKET				8
# define T_PAREN				9
# define T_BACKTICK				10
# define T_SPACE				11
# define T_COMMENT				12

//Just to make it compile
#define	HEREDOC_DOC				13
#define HEREDOC_STR				14
#define IS_REDIRECT_LEFT		15
#define IS_REDIRECT_RIGHT		16

typedef struct			s_nodes
{
	char				*content;
	struct s_nodes		*next;
}						t_nodes;

typedef struct			s_list
{
	t_nodes				*head;
	t_nodes				*tail;
}						t_list;

/*typedef struct					s_list
{
	char						*content;
	struct s_list				*next;
}
t_list;
*/

typedef struct        	         s_assign
{
    char				*value;
    struct s_assign		*next;
}                                t_assign;

typedef struct					s_tree
{
	char						type;
	struct s_tree				*left;
	struct s_tree				*right;
	struct s_cmd				*data;
	struct s_tree				*parent;
}								t_tree;

typedef struct					s_cmd
{
	t_redirect					*redirects;
	t_assign					*assign;
	char						**argv;
	int							return_status;
}								t_cmd;

typedef struct					s_token
{
	int							type;
	int							status;
	char						*content;
}								t_token;


/*
** lexing
*/

int				is_alpha_numeric(char c);
int				is_and_operator(char c);
int				is_pipe_operator(char c);
int				is_quote(char c);
int				is_bracket(char c);
int				is_paren(char c);
char			*ft_strdup_range(const char *str, int begin, int end);
void			free_list(t_list *head);
void			print_list(t_list *lst);
t_nodes			*new_node(char *new_data);
t_list			*new_list(char *new_data);
void			append(t_list **head_ref, char *new_data);
char			*trip_join(const char *s1, const char c, const char *s2);
void			free_append(char **s, char *end);
int				skip_whitespace(const char *input, int p);
int			check_errors(char *content, char *s);
int				classify_token(char c);
void			init_token_info(t_token *info);
int				pull_quote_content(t_list **head, const char *input, int *p);
int				pull_operator(t_list **head, const char *input, int *p);
int				pull_token(t_list **head, const char *input, int *p);
int				skip_to_end_of_line(const char *input, int *p, t_list **head);
int				interpret_token(t_list **head, const char *input, int *p);
t_list			*interpret_input(const char *input, int *token_completion);
t_list			*split_args(char *input);
t_tree			*parse(char *input);
int				is_op(char *str);



/*
** grammar
*/

t_cmd			*init_command(void);
int				is_reserved_word(char *s);
int				is_valid_name_char(char c);
int				is_assignment_word(char *s);
void			push_back(t_assign **head, char *value);
int				pull_assignment(char *assignment, t_cmd **cmd);
int				is_redirection(char *s);
int				is_number(char *s);
char			determine_redirection_type(char *o);
t_redirect		*new_redirection(char *operator_, int fd);
int				pull_redirection(t_nodes **node, t_nodes *prev, t_cmd **cmd);
int				get_ptr_len(char **s);
void			free_2d(char **s);
int				append_word_argv(char *word, t_cmd **cmd);
t_cmd			*create_cmd(t_nodes **tokens);
void			print_assign_info(t_assign *s);
void			print_redirect_info(t_redirect *r);
void			print_command_info(t_cmd *cmd);


/*
** AST
*/

t_tree			*build_tree(t_nodes *tokens);
t_tree			*insert(t_tree **root, t_cmd *data, char type);
t_tree			*build_subtree(t_tree **current, t_tree **new_root);
int				compare_precedence(char a, char b);
void			print_tree(t_tree *tree);
void			print_operator_type(char type);
char			get_type(char *s);
t_tree			*new_leaf(t_tree *parent, char type, t_cmd *data);
t_tree			*init_tree(void); // didn't end up using this function. scrap later
#endif
