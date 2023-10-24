/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchan <wchan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 17:19:16 by wchan             #+#    #+#             */
/*   Updated: 2023/03/24 15:20:36 by wchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	n;

	if (count == SIZE_MAX || size == SIZE_MAX)
		return (NULL);
	else
		n = count * size;
	ptr = malloc(n);
	if (!ptr)
		return (NULL);
	return (ft_memset(ptr, '\0', n));
}
