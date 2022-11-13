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
	ret = (char *)malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	ret[len] = '\0';
	while (len--)
	{
		ret[len] = digits[u % base + capitals];
		u /= base;
	}
	return (ret);
}

static void	set_preclen_and_padlen(unsigned long u, t_printf_info *info)
{
	size_t	len;

	len = 0;
	if (!info->prec_dot_only && u == 0)
		len += 1;
	while (u > 0)
	{
		u /= info->num_base;
		len += 1;
	}
	if ((size_t)info->prec_size > len)
	{
		info->num_preclen = (size_t)info->prec_size - len;
		len += info->num_preclen;
	}
	if ((size_t)info->width_size >= (len + ft_strlen(info->num_head_chr)))
	{
		if (info->num_head_chr)
			len += ft_strlen(info->num_head_chr);
		if (info->flag_zero_pad)
			info->num_preclen = (size_t)info->width_size - len;
		else
			info->num_padlen = (size_t)info->width_size - len;
	}
}

int	print_unsigned(unsigned long u, t_printf_info info)
{
	char		*numstr;
	int			ret_bytes;

	numstr = convert_u2base(u, info.num_base, info.num_capitals);
	if (!numstr)
		return (-1);
	ret_bytes = 0;
	set_preclen_and_padlen(u, &info);
	if (!info.flag_left && info.num_padlen)
		while (info.num_padlen--)
			ret_bytes += ft_putchar_fd(' ', 1);
	if (info.num_head_chr)
		ret_bytes += ft_putstr_fd(info.num_head_chr, 1);
	if (info.num_preclen)
		while (info.num_preclen--)
			ret_bytes += ft_putchar_fd('0', 1);
	if (!(info.prec_dot_only && u == 0))
		ret_bytes += ft_putstr_fd(numstr, 1);
	if (info.flag_left && info.num_padlen)
		while (info.num_padlen--)
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
		if (info->flag_sign)
			info->num_head_chr = "+";
		if (info->flag_space)
			info->num_head_chr = " ";
	}
	else
	{
		u = -n;
		info->num_head_chr = "-";
	}
	return (print_unsigned(u, *info));
}

int	print_hex(unsigned long u, t_printf_info *info, bool isupper)
{
	info->num_base = 16;
	if (isupper)
		info->num_capitals = 16;
	if (info->flag_prefix)
	{
		if (info->num_capitals)
			info->num_head_chr = "0X";
		else
			info->num_head_chr = "0x";
	}
	if (!info->is_pointer && u == 0)
		info->num_head_chr = "";
	return (print_unsigned(u, *info));
}
