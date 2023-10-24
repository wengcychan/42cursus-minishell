/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchan <wchan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 16:33:02 by wchan             #+#    #+#             */
/*   Updated: 2023/03/24 15:22:58 by wchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*front;
	size_t	i;

	if (!s1 || !set)
		return (NULL);
	front = (char *)s1;
	while (*front && ft_strchr(set, *front))
		front++;
	i = ft_strlen(front);
	while (i && ft_strchr(set, front[i]))
		i--;
	return (ft_substr(front, 0, i + 1));
}
