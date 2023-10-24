/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchan <wchan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 17:34:01 by wchan             #+#    #+#             */
/*   Updated: 2023/03/24 15:22:18 by wchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*res;
	size_t	n;

	n = ft_strlen(s1);
	res = (char *)malloc(sizeof(char) * (n + 1));
	if (!res)
		return (NULL);
	ft_strlcpy(res, s1, n + 1);
	return (res);
}
