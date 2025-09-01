/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buehara <buehara@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 14:15:56 by buehara           #+#    #+#             */
/*   Updated: 2025/09/01 17:44:20 by buehara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_link	*ft_new_node(t_link *prev)
{
	t_link	*node;

	node = malloc(sizeof(t_link));
	if (!node)
		return (NULL);
	node->content = malloc(sizeof(char) * BUFFER_SIZE + 2);
	if (!node->content)
		return (NULL);
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
		if (cpy[index] == '\n')
			find = 1;
	}
	return (find);
}

char	*ft_gnl_strcpy(t_link *node, int size)
{
	char	*org;
	char	*cpy;
	int		ctrl;

	org = node->content;
	ctrl = 0;
	cpy = malloc(sizeof(char) * size + 2);
	while (org && ctrl < size && cpy[ctrl] != '\0')
	{
		cpy[ctrl] = org[ctrl];
		ctrl++;
	}
	cpy[ctrl] = '\n';
	ctrl++;
	cpy[ctrl] = '\0';
	return (cpy);
}

void	ft_free(t_link **buffer)
{
	t_link	*node;

	node = *buffer;
	*buffer = (*buffer)->prev;
	while (node->prev != NULL)
	{
		free(node->content);
		free(node);
		if (!*buffer)
			return ;
		node = *buffer;
		*buffer = (*buffer)->prev;
	}
}

char	*get_next_line(int fd)
{
	static t_link	*node;
	t_link	*prev;
	int		size_read;
	int		size;
	int		find;
	char	*line;

	if (fd < 0)
		return (NULL);
	prev = NULL;
	line = NULL;
	size = 0;
	while (!line)
	{
		node = ft_new_node(prev);
		size_read = read(fd, node->content, BUFFER_SIZE);
		node->content[size_read] = '\0';
		find = ft_gnl_strlen(node, &size);
		if (find)
			line = ft_gnl_strcpy(node, size);
		if (prev)
			prev->next = node;
		else
			prev = node;
	}
//	free(node->content);
//	free(node);
	ft_free(&node);
	return (line);
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
