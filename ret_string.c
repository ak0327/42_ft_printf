/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ret_string.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 16:17:23 by takira            #+#    #+#             */
/*   Updated: 2022/10/27 16:17:28 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_c(char chr, t_printf_info info)
{
	int		ret_bytes;

	ret_bytes = 0;
	info.size = maxsize(info.width, 1);
	if (info.size == 1)
		return (ft_putchar_fd(chr, 1));
	if (info.left)
	{
		ret_bytes += ft_putchar_fd(chr, 1);
		info.size--;
	}
	while (info.size-- > !info.left)
		ret_bytes += ft_putchar_fd(' ', 1);
	if (!info.left)
		ret_bytes += ft_putchar_fd(chr, 1);
	return (ret_bytes);
}

int	print_s(char *str, t_printf_info info)
{
	int		ret_bytes;

	ret_bytes = 0;
	if (!str)
		str = "(null)";
	if (!info.dot)
		info.strlen = ft_strlen(str);
	else
		info.strlen = minsize(ft_strlen(str), info.perc);
	info.size = maxsize(info.width, info.strlen);
	if (info.size > info.strlen)
		info.padlen = info.size - info.strlen;
	if (info.left)
		while (info.strlen--)
			ret_bytes += ft_putchar_fd(*str++, 1);
	if (info.padlen)
		while (info.padlen--)
			ret_bytes += ft_putchar_fd(' ', 1);
	if (!info.left)
		while (info.strlen--)
			ret_bytes += ft_putchar_fd(*str++, 1);
	return (ret_bytes);
}

int	print_percent(t_printf_info info)
{
	int		ret_bytes;

	ret_bytes = 0;
	if ((info.left || !info.width) && info.zero_pad)
		info.zero_pad = 0;
	info.size = maxsize(info.width, 1);
	if (info.size == 1)
		return (ft_putchar_fd('%', 1));
	info.padlen = info.size - 1;
	if (info.left)
		ret_bytes += ft_putchar_fd('%', 1);
	if (info.zero_pad)
		while (info.padlen--)
			ret_bytes += ft_putchar_fd('0', 1);
	else
		while (info.padlen--)
			ret_bytes += ft_putchar_fd(' ', 1);
	if (!info.left)
		ret_bytes += ft_putchar_fd('%', 1);
	return (ret_bytes);
}
