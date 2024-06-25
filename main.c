/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 16:53:04 by tforster          #+#    #+#             */
/*   Updated: 2024/06/25 12:07:44 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	main(int argc, char **argv)
{
	char		*gnl;
	int			fd;

	int		i = 0;
	int		bytes = 0;
	char	buffer [7];

	// printf(">>> BYTES [%d]\n STR: [%s]", bytes, buffer);
	// printf(">>> END\n\n");
	// while (i <= 12)
	// {
	// 	fd = open("test.txt", O_RDONLY);
	// 	bytes = read(fd, buffer, i);
	// 	printf("BYTES [%d]\n STR: [%s]", bytes, buffer);
	// 	printf("END 00\n");
	// 	int		j = 0;
	// 	while (j <= 12)
	// 	{
	// 		printf("> CHAR %d[%c][%d] ", j, buffer[j], buffer[j]);
	// 		if (buffer[j] == '\0')
	// 			printf(" TRUE AT j = [%d]", j);
	// 		j++;
	// 		printf("\n");
	// 	}
	// 	printf("END 01\n\n");

	// 	close(fd);
	// 	i++;
	// }

	if (argc == 1)
		fd = 1;
	else
		fd = open(argv[1], O_RDONLY);
	if (fd < 1)
		return (0);
	gnl = get_next_line(fd);
	while (gnl)
	{
		printf("%s", gnl);
		if (gnl)
			free(gnl);
		gnl = get_next_line(fd);
	}
	if (fd > 1)
		close(fd);
	return (0);
}
