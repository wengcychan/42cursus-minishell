/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchan <wchan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 18:13:05 by wchan             #+#    #+#             */
/*   Updated: 2023/10/24 15:38:43 by wchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strndup(const char *s1, size_t n)
{
	char	*res;
	size_t	s1_len;

	if (!s1)
		return (NULL);
	s1_len = ft_strlen(s1);
	if (s1_len < n)
		n = s1_len;
	res = (char *)malloc(sizeof(char) * (n + 1));
	if (!res)
		return (NULL);
	ft_strlcpy(res, s1, n + 1);
	return (res);
}

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	i;
	size_t	j;

	if (!haystack || !needle)
		return (NULL);
	if (!(*needle))
		return ((char *)haystack);
	i = 0;
	while (haystack[i])
	{
		j = 0;
		while (needle[j])
		{
			if (haystack[i + j] != needle[j])
				break ;
			j++;
			if (!needle[j])
				return ((char *)(haystack + i));
		}
		i++;
	}
	return (NULL);
}

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

char	*ft_strtok(char *str, const char *delim)
{
	static char	*next_token = NULL;
	char		*current_token;
	const char	*d;

	if (str != NULL)
		next_token = str;
	else if (next_token == NULL)
		return (NULL);
	current_token = next_token;
	while (*next_token != '\0')
	{
		d = delim;
		if (check_and_increment(d, &next_token))
			return (current_token);
		next_token++;
	}
	if (current_token != next_token)
		next_token = NULL;
	return (current_token);
}

int	check_and_increment(const char *d, char **next_token)
{
	while (*d != '\0')
	{
		if (**next_token == *d)
		{
			**next_token = '\0';
			(*next_token)++;
			return (1);
		}
		d++;
	}
	return (0);
}
