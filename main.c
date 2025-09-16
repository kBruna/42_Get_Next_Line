/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buehara <buehara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 14:48:57 by buehara           #+#    #+#             */
/*   Updated: 2025/09/16 12:05:01 by buehara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include "get_next_line.h"
int	main(int argc, char **argv)
{
 	int		fd;
 	int		count;
 	char	*gnl;

 	count = 1;
 	if (argc > 1)
 	{
 		fd = open(argv[1], O_RDONLY);
 		if (argv[2])
 			count = atoi(argv[2]);
 		while (count)
 		{
 			gnl = get_next_line(fd);
 			printf("%s", gnl);
 			if (gnl)
 				free(gnl);
 			count--;
 		}
 		close(fd);
 	}
 	return (0);
}