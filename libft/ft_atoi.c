/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchan <wchan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 11:21:08 by wchan             #+#    #+#             */
/*   Updated: 2023/03/24 15:21:04 by wchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	long		res;
	int			sign;
	const char	*ptr;

	res = 0;
	sign = 1;
	ptr = str;
	while (*ptr == 32 || (*ptr >= 9 && *ptr <= 13))
		ptr++;
	if (*ptr == '-')
		sign *= -1;
	if (*ptr == '-' || *ptr == '+')
		ptr++;
	while (*ptr >= '0' && *ptr <= '9')
	{
		res = res * 10 + *ptr - '0';
		if (sign * res > 2147483647)
			return (-1);
		else if (sign * res < -2147483648)
			return (0);
		ptr++;
	}
	return ((int) res * sign);
}
