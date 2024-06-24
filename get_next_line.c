/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 16:56:49 by tforster          #+#    #+#             */
/*   Updated: 2024/06/24 19:34:55 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char *read_file(int fd, int re, int s0, char *line, char *buffer, int alloc);

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
	// printf("TEST src[%d]\n", src[i]);
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
	t_line		n_line;
	int	re;
	int	alloc;
	int	len;

	if (fd < 0 || read(fd, buffer, 0))
		return (clear_buffer(buffer));
	re = 1;

	n_line.alloc = ALLOC;

	alloc = ALLOC;
	if (BUFFER_SIZE > ALLOC)
		alloc = BUFFER_SIZE;
	line = malloc(sizeof(char) * re * alloc + 1);
	if (!line)
		return (NULL);

	int	i = 0;
	while (i < alloc)
		line[i++] = '\0';


	if (check_eol(buffer, 1, &len) >= 0 && len > 0)
		cpy_from_buffer(buffer, line);
	if (check_eol(buffer, 1, &len))
		return  (cpy_to_buffer(line, buffer, len));

	return (read_file(fd, 0, len, line, buffer, alloc));
}

static char *read_file(int fd, int re, int s0, char *line, char *buffer, int alloc)
{
	ssize_t	n_byte;
	ssize_t	start;
	int	len;

	len = 0;
	re++;
	start = BUFFER_SIZE * (re - 1) + s0;
	printf("RE[%d] S0[%d] BUFFER [%zu] ALLOC [%d]\n", re, s0, BUFFER_SIZE + start, alloc);
	if ((start + BUFFER_SIZE) >= alloc)
	{
		char	*re_line;

		alloc = re * ALLOC + 1;
		re_line = malloc(sizeof(char) * (re + 1) * alloc + 1);
		printf("ALLOC [%d]\n", (re + 1) * alloc + 1);

		cpy_from_buffer(line, re_line);
		free(line);
		line = re_line;
	}

	n_byte = read(fd, line + start, BUFFER_SIZE);
	line[n_byte + start] = '\0';
	// int flag = check_eol(line + start, n_byte, &len);
	// printf("RE[%d] START[%zd] N_BYTES[%zd] EOL[%d] SIZE[%d]\n", re, start, n_byte, flag, len);
	if (n_byte > 0 && check_eol(line + start, n_byte, &len))
		return (cpy_to_buffer(line, buffer, start + len));
	else if (n_byte == 0 && check_eol(line, n_byte, &len))
	{
		// printf("===>>>FINAL\n");
		clear_buffer(buffer);
		return (line);
	}
	else if (len > 0)
	{
		// printf("===>>>THEIS ONE [%d]\n", len);
		return (read_file(fd, re, s0, line, buffer, alloc));
	}
	free(line);
	return (NULL);
}
