/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchan <wchan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 14:23:08 by wchan             #+#    #+#             */
/*   Updated: 2023/06/05 16:45:54 by wchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*tmp;

	tmp = (char *)s;
	while (*tmp)
		tmp++;
	while (tmp != s)
	{
		if (*tmp == (char)c)
			return (tmp);
		tmp--;
	}
	if (*tmp == (char)c)
		return (tmp);
	return (NULL);
}
