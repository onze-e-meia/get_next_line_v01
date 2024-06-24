/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 16:53:04 by tforster          #+#    #+#             */
/*   Updated: 2024/06/23 19:50:25 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	main(int argc, char **argv)
{
	char		*gnl;
	int			fd;

	if (argc == 1)
		fd = 1;
	else
		fd = open(argv[1], O_RDONLY);
	if (fd < 1)
		return (0);
	// printf("00\n");
	gnl = get_next_line(fd);
	// printf("01\n");
	while (gnl)
	{
		// printf("<<<GNL START>>>\n");
		printf("===>>> %s", gnl);
		// printf("\n<<<GNL END>>>\n\n");
		if (gnl)
			free(gnl);
		gnl = get_next_line(fd);
	}
	if (fd > 1)
		close(fd);
	return (0);
}
