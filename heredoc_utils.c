/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchan <wchan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 14:45:44 by wchan             #+#    #+#             */
/*   Updated: 2023/06/02 14:45:58 by wchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_itoa_array_uint(unsigned int n, char res[])
{
	unsigned long	nbr;
	int				len;

	if (n == 0)
	{
		res[0] = '0';
		res[1] = '\0';
		return ;
	}
	nbr = n;
	len = 0;
	while (n)
	{
		n /= 10;
		len++;
	}
	res[len] = '\0';
	while (nbr)
	{
		len--;
		res[len] = nbr % 10 + '0';
		nbr /= 10;
	}
}
