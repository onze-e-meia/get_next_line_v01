/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 16:56:49 by tforster          #+#    #+#             */
/*   Updated: 2024/06/24 21:14:25 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char *read_file(int fd, int re, int s0, t_line *line, char *buffer);

static char	*clear_buffer(char *buffer)
{
	while (*buffer)
		*(buffer++) = '\0';
	return (NULL);
}

static int	check_eol(char *str, ssize_t n_byte, int *len)
{
	*len = 0;
	while (*str)
	{
		(*len)++;
		if (*str++ == '\n')
			return (1);
	}
	if (*len > 0 && n_byte == 0)
		return (1);
	return (0);
}
static char *cpy_line(char *src, char *dest, int len)
{
	int	i;

	i = 0;
	while (src[i] && i < BUFFER_SIZE)
	{
		dest[i] = src[i + len];
		i++;
	}
	if (len > 0)
		src[len] = '\0';
	dest[i] = '\0';
	return (src);
}

static void check_malloc(int start, t_line *line)
{
	char	*re_line;

	if ((start + BUFFER_SIZE) >= line->size)
	{
		line->re++;
		line->size = line->re * line->alloc + 1;
		re_line = malloc(sizeof(char) * line->size);
		cpy_line(line->str, re_line, 0);
		free(line->str);
		line->str = re_line;
	}
}


char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	t_line		line;
	int			s0;

	if (fd < 0 || read(fd, buffer, 0))
		return (clear_buffer(buffer));
	line.re = 1;
	line.alloc = ALLOC;
	if (BUFFER_SIZE > line.alloc + 1)
		line.alloc = BUFFER_SIZE;
	line.size = line.alloc + 1;
	line.str = malloc(sizeof(char) * line.size);
	if (!line.str)
		return (NULL);
	int	i = 0;
	while (i < line.size)
		line.str[i++] = '\0';
	if (check_eol(buffer, 1, &s0) >= 0 && s0 > 0)
		cpy_line(buffer, line.str, 0);
	if (check_eol(buffer, 1, &s0))
		return  (cpy_line(line.str, buffer, s0));
	return (read_file(fd, 0, s0, &line, buffer));
}


static char *read_file(int fd, int re, int s0, t_line *line, char *buffer)
{
	ssize_t	n_byte;
	ssize_t	start;
	int	len;

	len = 0;
	re++;
	start = BUFFER_SIZE * (re - 1) + s0;
	check_malloc(start, line);
	n_byte = read(fd, line->str + start, BUFFER_SIZE);
	line->str[n_byte + start] = '\0';
	if (n_byte > 0 && check_eol(line->str + start, n_byte, &len))
		return (cpy_line(line->str, buffer, start + len));
	else if (n_byte == 0 && check_eol(line->str, n_byte, &len))
	{
		clear_buffer(buffer);
		return (line->str);
	}
	else if (len > 0)
		return (read_file(fd, re, s0, line, buffer));
	free(line->str);
	return (NULL);
}
