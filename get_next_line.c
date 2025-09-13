/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buehara <buehara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 15:06:18 by buehara           #+#    #+#             */
/*   Updated: 2025/09/12 21:01:08 by buehara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_link	*ft_fill_nodes(int fd, char **tail)
{
	t_link	*node;
	t_link	*prev;
	int		len;
	int		find;
	int		ctrl;

	len = 0;
	find = 0;
	prev = NULL;
	while (!find)
	{
		tail = ft_rest(tail, fd, node, &find);
		if (!tail)
			return (NULL);
		node = ft_new_node(tail, prev);
		free(*tail);
		*tail = NULL;
		prev = node;
		ctrl = 0;
		while (node->content && node->content[ctrl] != '\n' && node->content[ctrl] != '\0')
		{
			ctrl++;
			len++;
		}
		if (node->content && node->content[ctrl] == '\n')
			find = 1;
	}
	return (node);
}

char	*get_next_line(int fd)
{
	static char	*tail;
	char		*line;
	// char		*temp;
	// int			find;
	// int			ctrl;
	// int			len;
	t_link		*node;
	t_link		*prev;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	ft_fill_nodes(fd, &tail);
	// find = 0;
	// len = 0;
	// prev = NULL;
	// node = NULL;
	// while (!find)
	// {
	// 	tail = ft_rest(tail, fd, node, &find);
	// 	if (!tail)
	// 		return (NULL);
	// 	node = ft_new_node(tail, prev);
	// 	free(tail);
	// 	tail = NULL;
	// 	prev = node;
	// 	ctrl = 0;
	// 	temp = node->content;
	// 	while (temp && temp[ctrl] != '\n' && temp[ctrl] != '\0')
	// 	{
	// 		ctrl++;
	// 		len++;
	// 	}
	// 	if (temp && (temp[ctrl] == '\n' || find))
	// 	{
	// 		len++;
	// 		if (node->prev)
	// 			while (node->prev != NULL)
	// 				node = node->prev;
	// 		find = 1;
	// 		line = ft_gnl_strlcpy(node, len);
	// 		tail = ft_gnl_realloc(temp);
	// 	}
	// }
	// ft_free(&node, &tail);
	return (line);
}

// #include <unistd.h>
// #include <stdio.h>
// #include <fcntl.h>
// int	main(int argc, char **argv)
// {
// 	int		fd;
// 	int		count;
// 	char	*gnl;

// 	count = 1;
// 	if (argc > 1)
// 	{
// 		fd = open(argv[1], O_RDONLY);
// 		if (argv[2])
// 			count = atoi(argv[2]);
// 		while (count)
// 		{
// 			gnl = get_next_line(fd);
// 			printf("%s", gnl);
// 			if (gnl)
// 				free(gnl);
// 			count--;
// 		}
// 		close(fd);
// 	}
// 	return (0);
// }
