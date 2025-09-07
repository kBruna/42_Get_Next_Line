/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buehara <buehara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 18:08:51 by buehara           #+#    #+#             */
/*   Updated: 2025/09/06 19:14:23 by buehara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_link	*ft_new_node(t_link *prev, char *content)
{
	t_link	*node;

	node = malloc(sizeof(t_link));
	if (!node)
		return (NULL);
	node->content = content;
	node->prev = prev;
	node->next = NULL;
	return (node);
}

int	ft_gnl_strlen(t_link *node, int *size)
{
	char	*cpy;
	int		find;
	int		index;

	cpy = node->content;
	find = 0;
	index = 0;
	while (cpy && cpy[index] != '\n' && cpy[index] != '\0')
	{
		(*size)++;
		index++;
	}
	if (cpy[index] == '\n')
	{
		(*size)++;
		find = 1;
	}
	return (find);
}

char	*ft_gnl_strcpy(t_link *node, int size)
{
	char	*org;
	char	*cpy;
	int		ctrl;
	int		index;

	while (node->prev != NULL)
		node = node->prev;
	org = node->content;
	ctrl = 0;
	index = 0;
	cpy = malloc(sizeof(char) * size + 1);
	while (org && org[ctrl] != '\0' && index < size)
	{
		cpy[index] = org[ctrl];
		ctrl++;
		index++;
		if (node->next && org[ctrl] == '\0')
		{
			node = node->next;
			org = node->content;
			ctrl = 0;
		}
	}
	cpy[index] = '\0';
	return (cpy);
}

void	ft_free(t_link **buffer)
{
	t_link	*node;

	node = *buffer;
	*buffer = (*buffer)->prev;
	while (node != NULL)
	{
		free(node->content);
		free(node);
		if (!*buffer)
			return ;
		node = *buffer;
		*buffer = (*buffer)->prev;
	}
}

char	*ft_realloc(t_link **node)
{
	char	*temp;
	char	*cpy;
	int		ctrl;
	int		index;

	ctrl = 0;
	temp = (*node)->content;
	while (temp && temp[ctrl] != '\n' && temp[ctrl] != '\0')
		ctrl++;
	if (temp[ctrl] == '\n')
		ctrl++;
	if (temp[ctrl] == '\0')
		return (NULL);
	cpy = malloc(sizeof(char) * BUFFER_SIZE + 2);
	index = 0;
	while (temp && temp[ctrl] != '\0')
	{
		cpy[index] = temp[ctrl];
		ctrl++;
		index++;
	}
	cpy[index] = '\0';
	return (cpy);
}
