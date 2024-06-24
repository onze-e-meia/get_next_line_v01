/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 16:56:49 by tforster          #+#    #+#             */
/*   Updated: 2024/06/23 21:49:52 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char *read_file(int fd, int re, int s0, char *line, char *buffer);

static void	clear_buffer(char *buffer)
{
	while (*buffer)
		*(buffer++) = '\0';
}

static int	check_eol(char *buffer, int *len)
{
	*len = 0;
	while (*buffer)
	{
		(*len)++;
		if (*buffer++ == '\n')
			return (1);
	}
	return (0);
}
static char *cpy_to_buffer(char *src, char *dest, int len)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i + len];
		i++;
	}
	src[len] = '\0';
	dest[i] = '\0';
	return (src);
}

static char *cpy_from_buffer(char *src, char *dest)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

// static char	*check_malloc(int n_read, char *line, char *re_line)
// {
// 	if (n_read > 1000)
// 	{
// 		int			re;
// 		int			alloc;
// 		re = n_read / 1000;
// 		alloc = 1000;
// 		line = malloc(sizeof(char) * re * alloc + 1);
// 		ft_cpyline(line, re_line);
// 	}
// 	return (re_line);
// }


char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;
	int	re;
	int	alloc;
	int	len;

	if (fd < 0)
		clear_buffer(buffer);
	re = 1;
	alloc = 1000;
	if (BUFFER_SIZE > 1000)
		alloc = BUFFER_SIZE;
	line = malloc(sizeof(char) * re * alloc + 1);
	if (!line)
		return (NULL);
	if (check_eol(buffer, &len) >= 0 && len > 0)
	{
		cpy_from_buffer(buffer, line);
		if (check_eol(buffer, &len))
			return (cpy_to_buffer(line, buffer, len));
	}
	return(read_file(fd, 0, len, line, buffer));
}

static char *read_file(int fd, int re, int s0, char *line, char *buffer)
{
	ssize_t	n_byte;
	ssize_t	start;
	int	len;

	re++;
	start = BUFFER_SIZE * (re - 1) + s0;
	n_byte = read(fd, line + start, BUFFER_SIZE);
	line[n_byte + start] = '\0';
	if (check_eol(line + start, &len))
		return (cpy_to_buffer(line, buffer, start + len));
	else if (len > 0)
		return (read_file(fd, re, s0, line, buffer));
	free(line);
	return (NULL);
}
