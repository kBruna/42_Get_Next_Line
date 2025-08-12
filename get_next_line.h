/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buehara <buehara@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 11:38:49 by buehara           #+#    #+#             */
/*   Updated: 2025/08/12 16:04:21 by buehara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define <stdlib.h>

# define BUFFER_SIZE 1024

typedef struct	s_link
{
	char	*content;
	s_link	*prev;
	s_link	*next;
}				t_link;

#endif
