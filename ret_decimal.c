/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ret_u.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 16:15:13 by takira            #+#    #+#             */
/*   Updated: 2022/10/27 16:15:16 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

static char	*convert_u2base(unsigned long u, int base, int capitals)
{
	size_t			len;
	unsigned long	num;
	char			*ret;
	const char		*digits = "0123456789abcdef0123456789ABCDEF";

	num = u;
	len = 0;
	if (u == 0)
		len++;
	while (num > 0)
	{
		num /= base;
		len += 1;
	}
	ret = (char *)ft_calloc(sizeof(char), len + 1);
	if (!ret)
		return (NULL);
	while (len)
	{
		len--;
		ret[len] = digits[u % base + capitals];
		u /= base;
	}
	return (ret);
}

static void	set_num_params(unsigned long u, t_printf_info *info)
{
	size_t	len;

	len = 0;
	if (!info->dot_only && u == 0)
		len += 1;
	while (u > 0)
	{
		u /= info->base;
		len += 1;
	}
	if ((size_t)info->perc > len)
	{
		info->perclen = (size_t)info->perc - len;
		len += info->perclen;
	}
	if ((size_t)info->width >= (len + ft_strlen(info->head_chr)))
	{
		if (info->head_chr)
			len += ft_strlen(info->head_chr);
		if (info->zero_pad)
			info->perclen = (size_t)info->width - len;
		else
			info->padlen = (size_t)info->width - len;
	}
}

int	print_unsigned(unsigned long u, t_printf_info info)
{
	char		*numstr;
	int			ret_bytes;

	numstr = convert_u2base(u, info.base, info.capitals);
	if (!numstr)
		return (-1);
	ret_bytes = 0;
	if (u == 0 && info.head_chr && !info.is_pointer)
		info.head_chr = "";
	set_num_params(u, &info);
	if (!info.left && info.padlen)
		while (info.padlen--)
			ret_bytes += ft_putchar_fd(' ', 1);
	if (info.head_chr)
		ret_bytes += ft_putstr_fd(info.head_chr, 1);
	if (info.perclen)
		while (info.perclen--)
			ret_bytes += ft_putchar_fd('0', 1);
	if (!(info.dot_only && u == 0))
		ret_bytes += ft_putstr_fd(numstr, 1);
	if (info.left && info.padlen)
		while (info.padlen--)
			ret_bytes += ft_putchar_fd(' ', 1);
	free(numstr);
	return (ret_bytes);
}

int	print_signed(long n, t_printf_info *info)
{
	unsigned long long	u;

	if (n >= 0)
	{
		u = n;
		if (info->sign)
			info->head_chr = "+";
		if (info->space)
			info->head_chr = " ";
	}
	else
	{
		u = -n;
		info->head_chr = "-";
	}
	return (print_unsigned(u, *info));
}

int	print_hexadecimal(unsigned long u, t_printf_info *info, bool isupper)
{
	if (isupper)
		info->capitals = 16;
	if (info->prefix)
	{
		if (info->capitals)
			info->head_chr = "0X";
		else
			info->head_chr = "0x";
	}
	return (print_unsigned(u, *info));
}
