/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchan <wchan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 17:11:56 by wchan             #+#    #+#             */
/*   Updated: 2023/06/05 16:43:20 by wchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_fill_array(char *res, long nbr, int len)
{
	res[len] = '\0';
	while (nbr)
	{
		len--;
		res[len] = nbr % 10 + '0';
		nbr /= 10;
	}
	if (len == 1 && !res[len])
		res[len - 1] = '0';
	else if (len == 1 && res[len])
		res[len - 1] = '-';
}

char	*ft_itoa(int n)
{
	char	*res;
	long	nbr;
	int		len;

	nbr = n;
	if (n > 0)
		len = 0;
	else
	{
		nbr = -nbr;
		len = 1;
	}
	while (n)
	{
		n /= 10;
		len++;
	}
	res = ft_calloc(len + 1, sizeof(char));
	if (!res)
		return (NULL);
	ft_fill_array(res, nbr, len);
	return (res);
}
