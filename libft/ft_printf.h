/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchan <wchan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 12:51:11 by wchan             #+#    #+#             */
/*   Updated: 2023/07/25 12:52:57 by wchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>

int	ft_printf(const char *format, ...);
int	ft_specifier(va_list ap, char c);
int	ft_print_char(char c);
int	ft_print_str(char *str);
int	ft_print_pointer(unsigned long ptr);
int	ft_print_int(long nbr);
int	ft_print_hex(unsigned long hex, char c);

#endif