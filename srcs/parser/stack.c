/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 13:37:09 by ale-goff          #+#    #+#             */
/*   Updated: 2018/11/28 19:21:59 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stack2.h>

int			pop(t_node **top)
{
	t_node	*tmp;
	int		content;

<<<<<<< HEAD
	content = 0;
=======
	content = 0; // could there ever be a problem where pop returns 0 it stack is empty?
>>>>>>> e1a9ca8133aeeaad86626e837420fc864ebf71f0
	tmp = *top;
	if (*top)
	{
		content = (*top)->content;
		*top = (*top)->next;
		free(tmp);
	}
	return (content);
}

void		push(t_node **top, int content)
{
	t_node *node;

	node = (t_node*)malloc(sizeof(t_node));
	node->content = content;
	node->next = *top;
	*top = node;
	return ;
}

int			is_empty(t_node *top)
{
	return (top == NULL);
}

int			peek(t_node *top)
{
	return ((top) ? top->content : 0);
}
