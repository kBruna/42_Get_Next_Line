/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buehara <buehara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 11:38:49 by buehara           #+#    #+#             */
/*   Updated: 2025/09/06 20:53:07 by buehara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

typedef struct s_link
{
	char			*content;
	struct s_link	*prev;
	struct s_link	*next;
}				t_link;

int		ft_gnl_strlen(t_link *node, int *size);

char	*get_next_line(int fd);
char	*ft_gnl(int fd, t_link *prev, t_link **node, int *error);
char	*ft_realloc(t_link **node);
char	*ft_gnl_strcpy(t_link *node, int size);

void	ft_free(t_link **buffer);

t_link	*ft_node(int fd, t_link **prev, int *find, int *error);
t_link	*ft_new_node(t_link *prev, char *content);

#endif
