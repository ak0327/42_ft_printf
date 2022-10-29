/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:52:04 by takira            #+#    #+#             */
/*   Updated: 2022/10/25 14:52:07 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	pass_print_fmt(va_list *ptr, const char c, t_printf_info info)
{
	if (c == 'c')
		return (print_c(va_arg(*ptr, int), info));
	if (c == 's')
		return (print_s(va_arg(*ptr, char *), info));
	if (c == 'p')
		return (print_hexadecimal(va_arg(*ptr, unsigned long), &info, false));
	if (c == 'd' || c == 'i')
		return (print_signed(va_arg(*ptr, long), &info));
	if (c == 'u')
		return (print_unsigned(va_arg(*ptr, unsigned int), info));
	if (c == 'x')
		return (print_hexadecimal(va_arg(*ptr, unsigned long), &info, false));
	if (c == 'X')
		return (print_hexadecimal(va_arg(*ptr, unsigned long), &info, true));
	if (c == '%')
		return (print_percent(info));
	return (-1);
}

static int	print_fmt(char *fmt, size_t *i, t_printf_info *info, va_list *ptr)
{
	init_print_info(info);
	input_flag((char *)fmt, i, info);
	if (!input_width((char *)fmt, i, info, ptr))
		return (-1);
	if (!input_perc((char *)fmt, i, info, ptr))
		return (-1);
	if (!is_flag_valid(fmt[*i], info))
		return (-1);
	return (pass_print_fmt(ptr, fmt[*i], *info));
}

int	ft_printf(const char *fmt, ...)
{
	int				print_bytes;
	int				sum_bytes;
	size_t			i;
	va_list			ptr;
	t_printf_info	info;

	i = 0;
	va_start(ptr, fmt);
	sum_bytes = 0;
	while (fmt[i])
	{
		if (fmt[i] != '%')
		{
			sum_bytes += ft_putchar_fd(fmt[i++], 1);
			continue ;
		}
		i++;
		print_bytes = print_fmt((char *)fmt, &i, &info, &ptr);
		if (print_bytes < 0)
			return (-1);
		sum_bytes += print_bytes;
		i++;
	}
	va_end(ptr);
	return (sum_bytes);
}
