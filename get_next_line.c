/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buehara <buehara@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 16:13:19 by buehara           #+#    #+#             */
/*   Updated: 2025/08/15 20:35:37 by buehara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdio.h>

void    *ft_get_lstfill(t_link *head, int fd, unsigned int *read_size);

t_link	*ft_get_lstnew(t_link **head, t_link *prev)
{
	int	ctrl;

	*head = (t_link *)malloc(sizeof(t_link) * 1);
	if (!*head)
		return (NULL);
	(*head)->content = (char *)malloc(sizeof(char *) * BUFFER_SIZE + 1);
	if (!(*head)->content)
	{
		free(*head);
		return (NULL);
	}
	ctrl = 0;
	while (BUFFER_SIZE >= ctrl)
	{
		(*head)->content[ctrl] = '\0';
		ctrl++;
	}
	(*head)->prev = prev;
	(*head)->next = NULL;
	return (*head);
}

void	ft_get_free(t_link *head)
{
	t_link	*temp;

	temp = head;
	while (head != NULL)
	{
		temp = head->prev;
		free(head->content);
		free(head);
		head = temp;
	}
}

void	*ft_get_lstfill(t_link *head, int fd, unsigned int *read_size)
{
	t_link	*prev;

	prev = NULL;
	while (fd >= 0)
	{
		head = ft_get_lstnew(&head, prev);
		if (!head)
		{
			ft_get_free(head);
			return (NULL);
		}
		prev = head;
		*read_size = read(fd, head->content, BUFFER_SIZE);
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

	p = list->content;
	size = 0;
	ctrl = 0;
	while (p && p[ctrl] != '\0' && p[ctrl] != '\n')
	{
		size++;
		ctrl++;
		if (p[ctrl] == '\0')
		{
			list = list->next;
			p = list->content;
			ctrl = 0;
		}
	}
	return (size);
/*	str = (char *)malloc(sizeof(char *) * size + 1);
	if (!str)
		return (NULL);
	while (list && list->prev != NULL)
		list = list->prev;
	p = list->content;
	ctrl = 0;
	while (p && size > 0)
	{
		str[ctrl] = p[ctrl];
		ctrl++;
		size--;
		if (p[ctrl] == '\0')
		{
			list = list->next;
			p = list->content;
			ctrl = 0;
		}
	}
	return (str);*/
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
			list = list->next;
			ft_get_free(list->prev);
			p = list->content;
			ctrl = 0;
		}
	}
	str[ctrl] = '\0';
	return (str);
}
	
char	*ft_get_str(t_link *list, int size)
{
	char	*str_return;
//	int		ctrl;

	str_return = malloc(sizeof(char *) * size + 1);
	if (!str_return)
		return (NULL);
	str_return = ft_get_fillstr(list, size, str_return);
/*	p = list->content;
	ctrl = 0;
	while (p && size > 0)
	{
		*str_return = p[ctrl];
		ctrl++;
		str_return++;
		size--;
		if (p[ctrl] == '\0')
		{
			list = list->next;
			ft_get_free(list->prev);
			p = list->content;
			ctrl = 0;
		}
	}
	*str_return = '\0';*/
	return (str_return);
}
	
char	*get_next_line(int fd)
{
	static t_link	*buffer;
	unsigned int	read_size;
	char			*str_return;
	int				len;

	buffer = NULL;
	read_size = 0;
	if (!buffer)
	{
		buffer = ft_get_lstfill(buffer, fd, &read_size);
		if (!buffer)
			return (NULL);
	}
	len = ft_get_enter(buffer);
	str_return = ft_get_str(buffer, len);
	//free(buffer);
	return (str_return);
//	return (buffer->content);
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
			while (count--)
			{
				gnl_return = get_next_line(fd);
				printf("%s", gnl_return);
			}
		}
		else
		{
			gnl_return = get_next_line(fd);
			printf("%s", gnl_return);
		}
	}
//	free(gnl_return);
	return (0);
}
