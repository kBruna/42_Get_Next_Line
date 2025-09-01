/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buehara <buehara@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 14:15:56 by buehara           #+#    #+#             */
/*   Updated: 2025/09/01 14:50:10 by buehara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_link	*ft_new_node(t_link *prev)
{
	t_link	*node;

	node = malloc(sizeof(t_link));
	if (!node)
		return (NULL);
	node->content = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!node->content)
		return (NULL);
	node->prev = prev;
	node->next = NULL;
	return (node);
}

char	*get_next_line(int fd)
{
	t_link	*node;
	t_link	*prev;
	int		size_read;
	int		ctrl;
	char	*p;

	if (fd < 0)
		return (NULL);
	prev = NULL;
	node = ft_new_node(prev);
	size_read = read(fd, node->content, BUFFER_SIZE);
	node->content[size_read] = '\0';
	ctrl = 0;
	p = malloc(256);
	while (ctrl < size_read)
	{
		p[ctrl] = node->content[ctrl];
		ctrl++;
	}
	p[ctrl] = '\0';
	free(node->content);
	free(node);
	return (p);
}

#include <fcntl.h>
#include <stdio.h>
int	main(int argc, char **argv)
{
	int		fd;
	char	*line;

	if (argc > 1)
	{
		fd = open(argv[1], O_RDONLY);
		line = get_next_line(fd);
		printf("%s", line);
		free(line);
	}
	return (0);
}
