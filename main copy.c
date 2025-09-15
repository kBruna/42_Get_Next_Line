/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buehara <buehara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 14:48:57 by buehara           #+#    #+#             */
/*   Updated: 2025/09/15 18:54:53 by buehara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include "get_next_line.h"

int	main(int argc, char **argv)
{
 	int		fd[1024];
 	int		count[1024];
 	char	*gnl;
	int		lines;
	int		file;
	int		index_fd;
	int		fd_max;

	index_fd = 0;
 	if (argc > 1)
 	{
		file = 1;
		lines = 2;
		while (argc <= file)
		{
			fd[index_fd] = open(argv[file], O_RDONLY);
			count[index_fd] = atoi(argv[lines]);
			index_fd++;
			lines += 2;
			argc -= 2;
		}
		count[index_fd] = 'NULL';
		fd_max = index_fd;
		index_fd = 0;
		while (fd_max)
		{
			index_fd = 0;
			while (count[index_fd])
			{
				if (count[index_fd])
				{
					gnl = get_next_line(fd[index_fd]);
					if (!gnl)
						fd_max--;
					printf("%s", gnl);
					if (gnl)
						free(gnl);
					count[index_fd]--;
				}
				else
				{
					close(fd[index_fd]);
					fd[index_fd] = '\0';
				}
				index_fd++;
			}
			if (index_fd == fd_max)
				break;
		}
 	}
 	return (0);
}