/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buehara <buehara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 11:38:49 by buehara           #+#    #+#             */
/*   Updated: 2025/09/12 20:40:41 by buehara          ###   ########.fr       */
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

// int	ft_gnl_strlen(char *content, int *ctrl, int *len);

char	*get_next_line(int fd);
char	*ft_gnl_strlcpy(t_link *node, int len);
char	*ft_rest(char *rest, int fd, t_link *node, int *find);
char	*ft_gnl_realloc(char *content);

void	ft_free(t_link **buffer, char **rest);

t_link	*ft_new_node(char *str, t_link *prev);

#endif
