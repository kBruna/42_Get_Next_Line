/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buehara <buehara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 14:38:37 by buehara           #+#    #+#             */
/*   Updated: 2025/08/31 20:34:20 by buehara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdio.h>

t_link *ft_new_node(t_link *prev)
{
	t_link	*node;

	node = malloc(sizeof(t_link));
	if (!node)
		return (NULL);
	node->content = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!node->content)
	{
		free(node);
		return (NULL);
	}
	node->prev = prev;
	node->next = NULL;
	return (node);
}

int ft_content_len(t_link *buffer, int *count)
{
	int		index;
	int		new_line;
	char	*content;

	index = 0;
	new_line = 0;
	content = buffer->content;
	while (content && content[index] != '\n' && content[index] != '\0')
	{
		index++;
		(*count)++;
		if (!content[index])
			new_line = 1;
	}
	return (new_line);
}

int	ft_read(int fd, t_link *buffer, int *count)
{
	int		read_size;
	int		check;
	t_link	*prev;

	prev = NULL;
	while (fd >= 0)
	{
		buffer = ft_new_node(prev);
		read_size = read(fd, buffer->content, BUFFER_SIZE);
		if (read_size == 0)
			return (0);
		if (read_size < 0)
		{
			//CLEAN FUNCTION
			return (0);
		}
		buffer->content[read_size] = '\0';
		check = ft_content_len(buffer, count);
		if (!check)
			break ;
		if (prev)
			prev->next = buffer;
		prev = buffer;
	}
	return (*count);
}

void	ft_get_free(t_link **buffer)
{
	t_link	*temp;

	temp = (*buffer)->prev;
	while ((*buffer)->prev != NULL)
	{
		free((*buffer)->content);
		free((*buffer));
		(*buffer) = temp;
		temp = (*buffer)->prev;
	}
}

char	*get_next_line(int fd)
{
//	char			*str;
	int				check;
	int				read_size;
//	int				count; //TEMP
//	int				index; //TEMP
	static t_link	*buffer;
	char			*p;

	if (fd >= 0)
	{
		read_size = 0;
//		str = NULL;
		if (!buffer)
			check = ft_read(fd, buffer, &read_size);
		if (!check)
			return (NULL);
//		str = malloc(read_size + 1);
//		while (buffer->prev != NULL)
//			buffer = buffer->prev;
//		p = buffer->content;
//		while (read_size > count)
//		{
//			str[count] = p[index];
//			count++;
//			index++;
//			if (p[index] == '\0')
//			{
//				buffer = buffer->next;
//				p = buffer->content;
//				index = 0;
//			}
//		}
//		str[count] = '\n';
//		count++;
//		str[count] = '\0';
		p = buffer->content;
		ft_get_free(&(buffer->prev));
		return (p);
	}
	return (NULL);
}

#include <fcntl.h>
int main(int argc, char **argv)
{
    int fd;
    int count;

    char    *gnl_return;

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
                printf("%s", gnl_return);
                free(gnl_return);
                count--;
            }
        }
        else
        {
            gnl_return = get_next_line(fd);
            printf("%s", gnl_return);
            free(gnl_return);
        }
    }
    return (0);
}
