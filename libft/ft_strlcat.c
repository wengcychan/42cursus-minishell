/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchan <wchan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 16:17:27 by wchan             #+#    #+#             */
/*   Updated: 2023/06/05 16:45:11 by wchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	src_len;
	size_t	dst_len;
	size_t	src_copy_len;

	src_len = ft_strlen(src);
	src_copy_len = src_len;
	if (!dstsize)
		return (src_len);
	dst_len = ft_strlen(dst);
	if (dstsize <= dst_len)
		return (dstsize + src_len);
	dstsize -= dst_len + 1;
	if (!dstsize)
		return (dst_len + src_len);
	if (src_len > dstsize)
		src_copy_len = dstsize;
	ft_memcpy(dst + dst_len, src, src_copy_len);
	dst[dst_len + src_copy_len] = '\0';
	return (dst_len + src_len);
}
