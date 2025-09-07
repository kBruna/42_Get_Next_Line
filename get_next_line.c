/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buehara <buehara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 14:15:56 by buehara           #+#    #+#             */
/*   Updated: 2025/09/06 21:04:35 by buehara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_link	*ft_node(int fd, t_link **prev, int *find, int *error)
{
	t_link	*node;
	int		size_read;
	char	*content;

	content = malloc(sizeof(char) * BUFFER_SIZE + 2);
	if (!content)
		return (NULL);
	size_read = read(fd, content, BUFFER_SIZE);
	if (size_read < 0)
		*error = 1;
	if (size_read <= 0)
	{
		free(content);
		return (NULL);
	}
	if (size_read < BUFFER_SIZE)
		*find = 1;
	content[size_read] = '\0';
	node = ft_new_node(*prev, content);
	if (*prev)
		(*prev)->next = node;
	*prev = node;
	return (node);
}

char	*ft_gnl(int fd, t_link *prev, t_link **node, int *error)
{
	char	*line;
	int		find;
	int		size;

	line = NULL;
	size = 0;
	find = 0;
	if (*node)
	{
		find += ft_gnl_strlen(*node, &size);
		if (find)
			line = ft_gnl_strcpy(*node, size);
		prev = *node;
	}
	while (!line)
	{
		if (!line)
			*node = ft_node(fd, &prev, &find, error);
		if (!(*node) && prev)
		{
			find = 1;
			free(*node);
			*node = prev;
			(*node)->next = NULL;
		}
		else if (!(*node))
			return (NULL);
		find += ft_gnl_strlen(*node, &size);
		if (find)
			line = ft_gnl_strcpy(*node, size);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	t_link		*node;
	t_link		*prev;
	char		*line;
	static char	*rest;
	int			error;

	error = 0;
	if (fd < 0 || BUFFER_SIZE == 0)
		return (NULL);
	prev = NULL;
	node = NULL;
	if (rest)
		node = ft_new_node(NULL, rest);
	line = ft_gnl(fd, prev, &node, &error);
	if (!line || error)
		return (NULL);
	rest = ft_realloc(&node);
	if (node)
		ft_free(&node);
	return (line);
}

// #include <fcntl.h>
// #include <stdio.h>
// int	main(int argc, char **argv)
// {
// 	int		fd;
// 	int		count;
// 	char	*line;

// 	if (argc > 1)
// 	{
// 		fd = open(argv[1], O_RDONLY);
// 		if (!argv[2])
// 			count = 1;
// 		else
// 			count = atoi(argv[2]);
// 		while (count > 0)
// 		{
// 			line = get_next_line(fd);
// 			printf("%s", line);
// 			free(line);
// 			count--;
// 		}
// 	}
// 	return (0);
// }
