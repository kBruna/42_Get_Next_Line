/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buehara <buehara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 14:57:10 by buehara           #+#    #+#             */
/*   Updated: 2025/09/16 12:04:59 by buehara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_link
{
	char			*content;
	struct s_link	*prev;
	struct s_link	*next;
}				t_link;

int		ft_gnl_strlen(t_link **buffer);

char	*get_next_line(int fd);
char	*ft_gnl_strlcpy(t_link *node, int len);
char	*ft_rest(char *rest, int fd, t_link *node, int *find);
char	*ft_gnl_realloc(char *content);

void	ft_free(t_link **buffer, char *rest[]);

t_link	*ft_new_node(char *str, t_link *prev);
t_link	*ft_fill_nodes(int fd, char **tail);

#endif
