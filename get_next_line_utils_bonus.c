/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buehara <buehara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 18:09:42 by buehara           #+#    #+#             */
/*   Updated: 2025/09/16 13:36:30 by buehara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	ft_free(t_link **buffer, char **rest)
{
	t_link	*node;

	if (*rest && *rest[0] == '\0')
	{
		free(*rest);
		*rest = NULL;
	}
	if (*buffer)
	{
		if ((*buffer)->next)
			while ((*buffer)->next != NULL)
				*buffer = (*buffer)->next;
		node = *buffer;
		*buffer = (*buffer)->prev;
		while (node != NULL)
		{
			if (node->content)
				free(node->content);
			free(node);
			if (!*buffer)
				return ;
			node = *buffer;
			*buffer = (*buffer)->prev;
		}
	}
}

char	*ft_gnl_strlcpy(t_link *node, int len)
{
	char	*temp;
	char	*line;
	int		new_len;
	int		ctrl;

	new_len = 0;
	ctrl = 0;
	line = malloc(sizeof(char) * len + 1);
	if (!line)
		return (NULL);
	temp = node->content;
	while (temp && temp[ctrl] != '\0' && new_len < len)
	{
		line[new_len] = temp[ctrl];
		new_len++;
		ctrl++;
		if (temp[ctrl] == '\0' && node->next)
		{
			node = node->next;
			temp = node->content;
			ctrl = 0;
		}
	}
	line[new_len] = '\0';
	return (line);
}

char	*ft_rest(char *rest, int fd, t_link *node, int *find)
{
	int	size_read;

	if (!rest)
	{
		rest = malloc(sizeof(char) * BUFFER_SIZE + 1);
		if (!rest)
			return (NULL);
		size_read = read(fd, rest, BUFFER_SIZE);
		if (size_read <= 0 && !node)
		{
			free(rest);
			return (NULL);
		}
		if (size_read >= 0)
			rest[size_read] = '\0';
		if (size_read < 0)
		{
			rest[0] = '\0';
			ft_free(&node, &rest);
			return (NULL);
		}
		if (size_read < BUFFER_SIZE)
			*find = 1;
	}
	return (rest);
}

t_link	*ft_new_node(char *str, t_link *prev)
{
	t_link	*node;
	int		ctrl;

	node = malloc(sizeof(t_link));
	if (!node)
		return (NULL);
	node->content = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!node->content)
		return (NULL);
	ctrl = 0;
	while (str && str[ctrl] != '\0')
	{
		node->content[ctrl] = str[ctrl];
		ctrl++;
	}
	node->content[ctrl] = '\0';
	node->prev = prev;
	node->next = NULL;
	if (prev)
		prev->next = node;
	return (node);
}

char	*ft_gnl_realloc(char *content)
{
	char	*rest;
	int		ctrl;
	int		new_len;

	ctrl = 0;
	rest = NULL;
	while (content && content[ctrl] != '\n' && content[ctrl] != '\0')
		ctrl++;
	if (content && content[ctrl] == '\n')
	{
		ctrl++;
		rest = malloc(sizeof(char) * BUFFER_SIZE + 2);
		if (!rest)
			return (NULL);
		new_len = 0;
		while (content && content[ctrl] != '\0')
		{
			rest[new_len] = content[ctrl];
			new_len++;
			ctrl++;
		}
		rest[new_len] = '\0';
	}
	return (rest);
}
