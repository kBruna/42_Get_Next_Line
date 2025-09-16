/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buehara <buehara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 15:06:18 by buehara           #+#    #+#             */
/*   Updated: 2025/09/16 13:39:44 by buehara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

t_link	*ft_fill_nodes(int fd, char **tail)
{
	t_link	*node;
	t_link	*prev;
	int		find;
	int		ctrl;

	find = 0;
	prev = NULL;
	node = NULL;
	while (!find)
	{
		*tail = ft_rest(*tail, fd, node, &find);
		if (!*tail)
			return (NULL);
		node = ft_new_node(*tail, prev);
		free(*tail);
		*tail = NULL;
		prev = node;
		ctrl = 0;
		while (node->content && node->content[ctrl] != '\n'
			&& node->content[ctrl] != '\0')
			ctrl++;
		if (node->content && node->content[ctrl] == '\n')
			break ;
	}
	return (node);
}

int	ft_gnl_strlen(t_link **buffer)
{
	int		len;
	int		ctrl;
	char	*str;
	t_link	*node;

	len = 0;
	ctrl = 0;
	node = *buffer;
	str = node->content;
	while (str && str[ctrl] != '\n' && str[ctrl] != '\0')
	{
		ctrl++;
		len++;
		if (node->next && str && str[ctrl] == '\0')
		{
			node = node->next;
			str = node->content;
			ctrl = 0;
		}
	}
	len++;
	return (len);
}

char	*get_next_line(int fd)
{
	static char		*tail[1024];
	t_link			*node;
	char			*line;
	int				len;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	node = ft_fill_nodes(fd, &tail[fd]);
	if (!node)
		return (NULL);
	if (node && node->prev)
		while (node->prev != NULL)
			node = node->prev;
	len = ft_gnl_strlen(&node);
	line = ft_gnl_strlcpy(node, len);
	if (node && node->next)
		while (node->next != NULL)
			node = node->next;
	tail[fd] = ft_gnl_realloc(node->content);
	ft_free(&node, &tail[fd]);
	return (line);
}
