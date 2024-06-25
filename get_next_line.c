/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 16:56:49 by tforster          #+#    #+#             */
/*   Updated: 2024/06/25 16:29:56 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_file(int fd, int re, int s0, t_line *line, char *buffer);

static char	*clear_buffer(char *buffer)
{
	while (*buffer)
		*(buffer++) = '\0';
	return (NULL);
}

static int	check_eol(char *str, ssize_t n_byte, int *eol_i)
{
	*eol_i = 0;
	while (str[*eol_i])
	{
		if (str[(*eol_i)++] == '\n')
			return (1);
	}
	return (n_byte == 0 && *eol_i > 0);
}

static char	*cpy_line(char *src, char *dest, int eol_i)
{
	int	i;

	i = 0;
	while (src[i + eol_i])
	{
		dest[i] = src[i + eol_i];
		i++;
	}
	if (eol_i > 0)
		src[eol_i] = '\0';
	dest[i] = '\0';
	return (src);
}

static void	check_malloc(int start, t_line *line)
{
	char	*re_line;

	if ((start + BUFFER_SIZE) >= line->size)
	{
		line->size = 2 * line->size + 1;
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
	int			i;

	if (fd < 0 || read(fd, buffer, 0))
		return (clear_buffer(buffer));
	line.size = ALLOC;
	if (BUFFER_SIZE >= line.size)
		line.size = BUFFER_SIZE + 1;
	line.str = malloc(sizeof(char) * line.size);
	if (!line.str)
		return (NULL);
	i = 0;
	while (i < line.size)
		line.str[i++] = '\0';
	if (check_eol(buffer, 1, &s0) >= 0 && s0 > 0)
		cpy_line(buffer, line.str, 0);
	if (check_eol(buffer, 1, &s0))
		return (cpy_line(line.str, buffer, s0));
	return (read_file(fd, 0, s0, &line, buffer));
}

static char	*read_file(int fd, int re, int s0, t_line *line, char *buffer)
{
	ssize_t	n_byte;
	ssize_t	start;
	int	eol_i;

	eol_i = 0;
	re++;
	start = BUFFER_SIZE * (re - 1) + s0;
	check_malloc(start, line);
	n_byte = read(fd, line->str + start, BUFFER_SIZE);
	if (n_byte > 0)
		line->str[n_byte + start] = '\0';
	if (n_byte > 0 && check_eol(line->str + start, n_byte, &eol_i))
		return (cpy_line(line->str, buffer, start + eol_i));
	else if (n_byte == 0 && check_eol(line->str, n_byte, &eol_i))
	{
		clear_buffer(buffer);
		return (line->str);
	}
	else if (eol_i > 0)
		return (read_file(fd, re, s0, line, buffer));
	free(line->str);
	return (NULL);
}
