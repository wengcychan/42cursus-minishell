/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchan <wchan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 12:51:11 by wchan             #+#    #+#             */
/*   Updated: 2023/07/25 12:51:59 by wchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	int		len;
	int		i;
	va_list	ap;

	len = 0;
	i = 0;
	va_start(ap, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			len += ft_specifier(ap, format[i]);
		}
		else
			len += ft_print_char(format[i]);
		i++;
	}
	va_end(ap);
	return (len);
}

int	ft_specifier(va_list ap, char c)
{
	int	len;

	len = 0;
	if (c == 'c')
		len += ft_print_char(va_arg(ap, int));
	else if (c == 's')
		len += ft_print_str(va_arg(ap, char *));
	else if (c == 'p')
		len += ft_print_pointer(va_arg(ap, unsigned long));
	else if (c == 'd' || c == 'i')
		len += ft_print_int(va_arg(ap, int));
	else if (c == 'u')
		len += ft_print_int(va_arg(ap, unsigned int));
	else if (c == 'x' || c == 'X')
		len += ft_print_hex(va_arg(ap, unsigned int), c);
	else if (c == '%')
		len += ft_print_char('%');
	return (len);
}
