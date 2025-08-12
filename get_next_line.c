/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buehara <buehara@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 16:13:19 by buehara           #+#    #+#             */
/*   Updated: 2025/08/12 18:24:06 by buehara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char	*buffer;
	int		read_size;

	read_size = read(fd, buffer, BUFFER_SIZE);
}

#include <fcntl.h>
int	main(int argc, char *argv)
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
			count = argv[2];
			for (n; n > 0; n--)
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
