/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchan <wchan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 13:49:03 by wchan             #+#    #+#             */
/*   Updated: 2023/07/25 13:49:27 by wchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*save;
	char		*line;
	char		*buf;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	line = read_buf(fd, save, buf);
	free(buf);
	if (!line || !line[0])
	{
		free(save);
		save = NULL;
		return (NULL);
	}
	save = extract_line_and_save(line, save);
	if (!save)
	{
		free(line);
		return (NULL);
	}
	return (line);
}
