/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buehara <buehara@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 16:13:19 by buehara           #+#    #+#             */
/*   Updated: 2025/08/21 20:16:54 by buehara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdio.h>

t_link	*ft_get_lstnew(t_link *prev)
{
	int	ctrl;
	t_link	*head;

	head = (t_link *)malloc(sizeof(t_link));
	if (!head)
		return (NULL);
	head->content = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!head->content)
	{
		free(head);
		return (NULL);
	}
	ctrl = 0;
	while (BUFFER_SIZE >= ctrl)
	{
		head->content[ctrl] = '\0';
		ctrl++;
	}
	head->prev = prev;
	head->next = NULL;
	return (head);
}

void	ft_get_free(t_link *head)
{
//	t_link	*temp;

	if (head == NULL)
		return ;
//	temp = head;
//	while (*head != NULL)
//	{
//		temp = head->prev;
		free(head->content);
		free(head);
//		if (!temp)
//			break ;
//		head = temp;
//	}
}

void	*ft_get_lstfill(t_link *head, int fd, unsigned int *read_size)
{
	t_link	*prev;

	prev = NULL;
	while (fd >= 0)
	{
		head = ft_get_lstnew(prev);
		if (!head)
		{
			ft_get_free(head);
			return (NULL);
		}
		if (prev)
			prev->next = head;
		prev = head;
		*read_size = read(fd, head->content, BUFFER_SIZE);
		head->content[*read_size] = '\0';
		if (*read_size < BUFFER_SIZE)
			break ;
		head = head->next;
	}
	while (head && head->prev != NULL)
		head = head->prev;
	return (head);
}

int	ft_get_enter(t_link *list)
{
	int		size;
	char	*p;
	int		ctrl;

	p = (char *)list->content;
	size = 0;
	ctrl = 0;
	while (*p && p[ctrl] != '\0' && p[ctrl] != '\n')
	{
		size++;
		ctrl++;
		if (p[ctrl] == '\0')
		{
			list = list->next;
			p = list->content;
			if (!p)
				return (size);
			ctrl = 0;
		}
	}
	return (size);
}

void	ft_realloc_node(char *content)
{
	int	ctrl;
	int	index;

	ctrl = 0;
	index = 0;
	while (content[ctrl] != '\n' && content[ctrl] != '\0')
		ctrl++;
	if (content[ctrl] == '\n')
	{
		if (content[ctrl + 1] != '\n' && content[ctrl + 1] != '\0')
		{
			ctrl++;
			while (content[ctrl] != '\0')
			{
				content[index] = content[ctrl];
				ctrl++;
				index++;
			}
		}
		content[index] = '\0';
	}
}

char	*ft_get_fillstr(t_link *list, int size, char *str)
{
	char	*p;
	int		ctrl;
	int		index;

	p = list->content;
	ctrl = 0;
	index = 0;
	while (p && size > 0)
	{
		str[index] = p[ctrl];
		ctrl++;
		index++;
		size--;
		if (p[ctrl] == '\0')
		{
			if (list->next)
			{
				*list = *(list->next);
				p = list->content;
				ctrl = 0;
			}
		}
	}
	str[index] = '\0';
	return (str);
}
	
char	*ft_get_str(t_link *list, int size)
{
	char	*str_return;

	str_return = malloc(sizeof(char) * (size + 1));
	if (!str_return)
		return (NULL);
	str_return = ft_get_fillstr(list, size, str_return);
	ft_realloc_node(list->content);
	if (list->content[0] == '\0')
		list = list->next;
	if(list->prev)
	{
		ft_get_free(list->prev);
		list->prev = NULL;
	}
	return (str_return);
}
	
char	*get_next_line(int fd)
{
	static t_link	*buffer;
	unsigned int	read_size;
	char			*str_return;
	int				len;

	read_size = 0;
	if (!buffer)
	{
		buffer = ft_get_lstfill(buffer, fd, &read_size);
		if (!buffer)
			return (NULL);
	}
	len = ft_get_enter(buffer);
	str_return = ft_get_str(buffer, len);
	if (buffer->next == NULL)
	{
		len = 0;
		while (*(buffer)->content != '\n' && *(buffer)->content != '\0' && len < 2)
			len++;
	}
	if (len <= 0)
		ft_get_free(buffer);
	return (str_return);
}

#include <stdio.h>
#include <fcntl.h>
int	main(int argc, char **argv)
{
	int	fd;
	int	count;

	char	*gnl_return;

	if(argc > 1)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd < 0)
		{
			printf("Error Opening File.\n");
			return (1);
		}
		if (argv[2])
		{
			count = atoi(argv[2]);
			while (count)
			{
				gnl_return = get_next_line(fd);
				printf("\n%s\n", gnl_return);
				free(gnl_return);
				count--;
			}
		}
		else
		{
			gnl_return = get_next_line(fd);
			printf("\n%s\n", gnl_return);
			free(gnl_return);
		}
	}
	return (0);
}
