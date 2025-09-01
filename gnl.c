/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buehara <buehara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 15:50:04 by buehara           #+#    #+#             */
/*   Updated: 2025/08/28 19:47:10 by buehara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdio.h>

t_link	*ft_new_node(t_link *prev)
{
	t_link	*node;
	int		ctrl;

	ctrl = 0;
	node = malloc(sizeof(t_link));
	if (!node)
		return (NULL);
	node->content = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!node->content)
	{
		free(node);
		return (NULL);
	}
	while (ctrl <= BUFFER_SIZE)
	{
		node->content[ctrl] = '\0';
		ctrl++;
	}
	node->prev = prev;
	node->next = NULL;
	return (node);
}

void	ft_get_clean(t_link *buffer)
{
	t_link	*temp;
	t_link	*next;

	if (!buffer)
		return ;
	temp = NULL;
	if (buffer->next)
		next = buffer->next;
	while (buffer != NULL)
	{
		if (buffer->prev != NULL)
		{
			temp = buffer->prev;
		}
		free(buffer->content);
		free(buffer);
		if (temp == buffer || temp == NULL)
			break ;
		buffer = temp;
	}
	if (next)
		next->prev = NULL;
}

void	ft_read(int fd, t_link **buffer)
{
	int	read_size;
	t_link	*prev;

	prev = NULL;
	read_size = 1;
	while (read_size > 0)
	{
		*buffer = ft_new_node(prev);
		if (!*buffer)
		{
			ft_get_clean(*buffer);
			return ;
		}
		read_size = read(fd, (*buffer)->content, BUFFER_SIZE);
		if (read_size <= 0)
			break;
		(*buffer)->content[read_size] = '\0';
		if (read_size < BUFFER_SIZE)
			break ;
		if (prev)
			prev->next = *buffer;
		prev = *buffer;
	}
	while ((*buffer)->prev != NULL)
		*buffer = (*buffer)->prev;
}

t_link	*ft_get_enter(t_link *buffer, char *str)
{
	int		str_ctrl;
	int		buf_ctrl;
	char	*p;

	str_ctrl = 0;
	buf_ctrl = 0;
	p = buffer->content;
	while (buffer && p[buf_ctrl] != '\n')
	{
		str[str_ctrl] = p[buf_ctrl];
		str_ctrl++;
		buf_ctrl++;
		if (buffer && p[buf_ctrl] == '\0')
		{
			if (buffer->next == NULL)
				break;
			buffer = buffer->next;
			p = buffer->content;
			buf_ctrl = 0;
		}
	}
	str[str_ctrl] = '\0';
	return (buffer);
}

int		ft_get_count(t_link *buffer)
{
	int		ctrl;
	int		index;
	t_link	*current;

	ctrl = 0;
	index = 0;
	current = buffer;
	while (current && current->content[index] != '\n')
	{
		ctrl++;
		index++;
		if (current->next && current->content[index] == '\0')
		{
			current = current->next;
			index = 0;
		}
	}
	return (ctrl);
}

char	*ft_new_str(char *s)
{
	char	*temp;
	char	*new_content;
	int		index;

	temp = s;
	new_content = malloc(sizeof(char) * BUFFER_SIZE);
	if (!new_content)
		return (NULL);
	index = 0;
	while (temp && temp[index] != '\0')
	{
		new_content[index] = temp[index];
		index++;
	}
	new_content[index] = '\0';
	return (new_content);
}

t_link	*ft_realloc(t_link *buffer)
{
	char	*temp;
	char	*new_str;

	temp = buffer->content;
	while (temp && *temp != '\n' && *temp != '\0')
		temp++;
	if (*temp == '\0')
	{
		buffer = buffer->next;
		ft_get_clean(buffer->prev);
		return (buffer);
	}
	temp++;
	new_str = ft_new_str(temp);
	free(buffer->content);
	buffer->content = new_str;
	return (buffer);
}

char	*get_next_line(int fd)
{
	static t_link	*buffer;
	t_link			*head;
	char			*temp;
	int				ctrl;

	ctrl = 0;
	if (!buffer)
		ft_read(fd, &buffer);
	if (!buffer)
		return (NULL);
	head = buffer;
	ctrl = ft_get_count(buffer);
	temp = malloc(sizeof(char) * ctrl + 1);
	if (!temp)
	{
		while (buffer->next != NULL)
			buffer = buffer->next;
		ft_get_clean(buffer);
		return (NULL);
	}
	buffer = ft_get_enter(head, temp);
	buffer = ft_realloc(buffer);
	if (buffer->prev)
		ft_get_clean(buffer->prev);
	return (temp);
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

