/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buehara <buehara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 14:48:57 by buehara           #+#    #+#             */
/*   Updated: 2025/09/16 13:26:55 by buehara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include "get_next_line.h"

#define RED 	"\033[0;31m"
#define BLUE 	"\033[0;34m"
#define GREEN 	"\033[0;32m"
#define YELLOW	"\033[0;33m"
#define RESETC 	"\033[0m"

int	main(int argc, char **argv)
{
 	int		fd[1024];
 	int		count[1024];
 	char	*gnl;
	int		lines;
	int		file;
	int		index_fd;
	int		fd_max;
	int		all_null;

	index_fd = 0;
 	if (argc > 1)
 	{
		file = 1;
		lines = 2;
		while (argc >= file)
		{
			fd[index_fd] = open(argv[file], O_RDONLY);
			count[index_fd] = atoi(argv[lines]);
			index_fd++;
			lines += 2;
			file += 2;
		}
		fd_max = index_fd;
		index_fd = 0;
		all_null = fd_max;
		while (all_null - 1)
		{
			if (count[index_fd])
			{
				gnl = get_next_line(fd[index_fd]);
				printf(GREEN "Arquivo fd[%d] | Linha [%d]:" RESETC " %s " YELLOW "( TEST \\n )" RESETC "\n",fd[index_fd], count[index_fd], gnl);
				if (gnl)
					free(gnl);
				count[index_fd]--;
				if (!count[index_fd])
					all_null--;
			}
			index_fd = (index_fd + 1) % fd_max;
		}
 	}
 	return (0);
}
