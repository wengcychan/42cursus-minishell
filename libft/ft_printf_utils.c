/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchan <wchan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 12:51:11 by wchan             #+#    #+#             */
/*   Updated: 2023/07/25 12:51:20 by wchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_char(char c)
{
	return (write(1, &c, 1));
}

int	ft_print_str(char *str)
{
	int	len;
	int	i;

	if (!str)
		return (write(1, "(null)", 6));
	i = 0;
	len = 0;
	while (str[i])
	{
		len += ft_print_char(str[i]);
		i++;
	}
	return (len);
}

int	ft_print_pointer(unsigned long ptr)
{
	int	len;

	len = 0;
	len += write(1, "0x", 2);
	if (!ptr)
	{
		len += ft_print_char('0');
		return (len);
	}
	len += ft_print_hex(ptr, 'x');
	return (len);
}

int	ft_print_int(long nbr)
{
	long	n;
	int		len;

	n = nbr;
	len = 0;
	if (nbr < 0)
	{
		len += ft_print_char('-');
		n *= -1;
	}
	if (n >= 10)
	{
		len += ft_print_int(n / 10);
		len += ft_print_int(n % 10);
	}
	else
		len += ft_print_char(n + '0');
	return (len);
}

int	ft_print_hex(unsigned long hex, char c)
{
	int		len;

	len = 0;
	if (hex >= 16)
	{
		len += ft_print_hex(hex / 16, c);
		len += ft_print_hex(hex % 16, c);
	}
	else
	{
		if (hex < 10)
			len += ft_print_char(hex + '0');
		else
		{
			if (c == 'X')
				len += ft_print_char(hex - 10 + 'A');
			else
				len += ft_print_char(hex - 10 + 'a');
		}
	}
	return (len);
}
