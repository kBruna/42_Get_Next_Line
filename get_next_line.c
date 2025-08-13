/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buehara <buehara@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 16:13:19 by buehara           #+#    #+#             */
/*   Updated: 2025/08/13 20:32:20 by buehara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_link	*ft_get_newlist(t_link *head, t_link *prev)
{
	int	ctrl;

	head = (t_link *)malloc(sizeof(t_link) * 1);
	if (!head)
		return (NULL);
	head->content = (char *)malloc(sizeof(char *) * BUFFER_SIZE + 1);
	if (!head->content)
		return (NULL);
	ctrl = 0;
	while (BUFFER_SIZE >= ctrl)
		head->content[ctrl++] = '\0';
	head->prev = prev;
	head->next = NULL;
	return (head);
}

void	ft_get_free(t_link *head)
{
	t_link	*temp;

	temp = head;
	while (head != NULL)
	{
		temp = head->next;
		free(head->content);
		free(head);
		head = temp;
	}
}
		
void	*ft_get_filllist(t_link *head, int fd, unsigned int *read_size)
{
	t_link	*temp;

	temp = NULL;
	while (fd >= 0)
	{
		head = ft_get_newlist(head, temp);
		if (!head)
		{
			ft_get_free(head);
			return (NULL);
		}
		temp = head;
		head = head->next;
		(*read_size) = read(fd, head->content, BUFFER_SIZE);
		if (*read_size < BUFFER_SIZE)
			break ;
	}
	while (head->prev != NULL)
		head = head->prev;
	return (head);
}

char	*get_next_line(int fd)
{
	t_link	*buffer;
	unsigned int		read_size;
	static unsigned int	index;
	//char	*check;

	index = 0;
	buffer = NULL;
	read_size = 0;
	buffer = ft_get_filllist(buffer, fd, &read_size);
	if (!buffer)
		return (NULL);
	//buffer = ft_get_newlist(buffer);
	//buffer = (t_link *)malloc(sizeof(t_link *) * BUFFER_SIZE + 1);
	//read_size = read(fd, buffer->content, BUFFER_SIZE);
	//buffer->content[BUFFER_SIZE] = '\0';
	return (buffer->content);
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
	return (0);
}
