/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchan <wchan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 13:48:57 by wchan             #+#    #+#             */
/*   Updated: 2023/07/25 13:49:49 by wchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_buf(int fd, char *save, char *buf)
{
	int	read_size;

	while (1)
	{
		read_size = read(fd, buf, BUFFER_SIZE);
		if (read_size == -1)
			return (NULL);
		if (read_size == 0)
			break ;
		buf[read_size] = '\0';
		if (!save)
		{
			save = (char *)malloc(sizeof(char) * 1);
			if (!save)
				return (NULL);
			save[0] = '\0';
		}
		save = str_concat(save, buf);
		if (!save)
			return (NULL);
		if (find_char(save, '\n') != -1)
			break ;
	}
	return (save);
}

char	*str_concat(char *dst, char *src)
{
	char	*res;
	int		i;
	int		j;

	res = (char *)malloc(sizeof(char) * (find_char(dst, '\0')
				+ find_char(src, '\0') + 1));
	if (!res)
	{
		free(dst);
		return (NULL);
	}
	i = 0;
	j = 0;
	while (dst[i])
		res[j++] = dst[i++];
	i = 0;
	while (src[i])
		res[j++] = src[i++];
	res[j] = '\0';
	free(dst);
	return (res);
}

int	find_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	if (!c)
		return (i);
	return (-1);
}

char	*extract_line_and_save(char *line, char *save)
{
	int	count;
	int	i;
	int	j;

	count = 0;
	while (line[count] != '\n' && line[count])
		count++;
	if (!line[count])
		count--;
	save = (char *)malloc(sizeof(char) * (find_char(line, '\0') - count));
	if (!save)
		return (NULL);
	i = 0;
	j = count + 1;
	while (j < find_char(line, '\0') + 1)
		save[i++] = line[j++];
	line[count + 1] = '\0';
	return (save);
}
