/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 16:56:49 by tforster          #+#    #+#             */
/*   Updated: 2024/06/21 18:35:07 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	*clear_buffer(char *buffer)
{
	while (*buffer)
		*(buffer++) = '\0';
}

static int	check_eol(char *buffer)
{
	int	len;

	len = 0;
	while (*buffer && *buffer++ != '\n')
		len++;
	return (len);
}

static char *ft_cpyline(char *src, char *dest)
{
	while (*src)
		*dest++ = *src++;
	*dest = '\0';
	return (dest);
}

static void	make_line(int fd, int n_read, char *line)
{
	int		n_byte;
	int		eol;
	char	*re_line;

	n_read = BUFFER_SIZE * (n_read - 1);
	if (n_read > 1000)
	{
		int			re;
		int			alloc;

		re = 1;
		alloc = 1000;
		line = malloc(sizeof(char) * re * alloc + 1);
		ft_cpyline(line, re_line);
	}
	n_byte = read(fd, line + n_read, BUFFER_SIZE);
	eol = check_eol(line);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE];
	char		*line;
	ssize_t		n_byte;
	int			n;

	if (fd < 0)
		clear_buffer(buffer);

	n = check_eol(buffer);
	if (n > 0)
		return (buffer);
	else
	{
		int	start;

		n = 1;
		start = BUFFER_SIZE * (n -1);
		n_byte = read(fd, line + start , BUFFER_SIZE);
		n = check_eol(buffer);
		if (n == 0)
		{




		}


	}




}
