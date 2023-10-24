/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchan <wchan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 13:47:11 by wchan             #+#    #+#             */
/*   Updated: 2023/06/05 16:44:35 by wchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	int		i;

	if (!dst && !src)
		return (NULL);
	if (src + len >= dst && dst > src)
	{
		i = len - 1;
		while (i >= 0)
		{
			((char *)dst)[i] = ((const char *)src)[i];
			i--;
		}
	}
	else
		dst = ft_memcpy(dst, src, len);
	return (dst);
}
