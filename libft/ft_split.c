/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchan <wchan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 16:46:55 by wchan             #+#    #+#             */
/*   Updated: 2023/06/05 16:41:40 by wchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_free(char **res, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		free(res[i]);
		i++;
	}
	return (NULL);
}

static char	**ft_get_word(char **res, char const **s, char c, size_t i)
{
	size_t	char_count;

	char_count = 0;
	while (**s == c)
		(*s)++;
	while (**s != c && **s != '\0')
	{
		char_count++;
		(*s)++;
	}
	*s = *s - char_count;
	res[i] = (char *)malloc(sizeof(char) * (char_count + 1));
	if (!res[i])
		return (ft_free(res, i));
	ft_strlcpy(res[i], *s, char_count + 1);
	*s = *s + char_count;
	return (res);
}

static	size_t	ft_word_count(char const *s, char c)
{
	size_t	word_count;
	int		word_start;

	word_count = 0;
	word_start = 0;
	while (*s)
	{
		if (*s == c)
			word_start = 0;
		else if (word_start == 0 && *s != c)
		{
			word_count++;
			word_start = 1;
		}
		s++;
	}
	return (word_count);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	size_t	i;
	size_t	word_count;

	if (!s)
		return (NULL);
	word_count = ft_word_count(s, c);
	res = (char **)malloc(sizeof(char *) * (word_count + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (i < word_count)
	{
		res = ft_get_word(res, &s, c, i);
		if (!res)
		{
			free(res);
			return (NULL);
		}
		i++;
	}
	res[i] = NULL;
	return (res);
}
