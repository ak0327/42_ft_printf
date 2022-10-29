/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_flg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 17:42:16 by takira            #+#    #+#             */
/*   Updated: 2022/10/28 17:42:18 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static bool	is_valid_strs(t_printf_info info, char type)
{
	if (type == 'c')
	{
		if (info.width > INT_MAX || info.prec > INT_MAX)
			return (false);
		if (info.sign || info.space || info.zero_pad)
			return (false);
		if (info.dot && !info.dot_only)
			return (false);
		return (true);
	}
	if (type == 's')
	{
		if (info.width > INT_MAX || info.prec > INT_MAX)
			return (false);
		if (info.sign || info.space || info.zero_pad || info.prefix)
			return (false);
		return (true);
	}
	return (false);
}

static bool	is_valid_num(t_printf_info *info, char type)
{
	if (type == 'd')
	{
		if (info->width > INT_MAX || info->prec > INT_MAX)
			return (false);
		if (info->zero_pad && info->dot)
			info->zero_pad = false;
		if ((info->sign && info->space) || info->prefix)
			return (false);
		if (info->zero_pad && info->left)
			return (false);
		return (true);
	}
	if (type == 'u')
	{
		if (info->width > INT_MAX || info->prec > INT_MAX)
			return (false);
		if (info->zero_pad && info->dot)
			info->zero_pad = false;
		if (info->sign || info->space || info->prefix)
			return (false);
		return (true);
	}
	return (false);
}

static bool	is_valid_hex(t_printf_info *info, char type)
{
	info->base = 16;
	if (type == 'x')
	{
		if (info->width > INT_MAX || info->prec > INT_MAX)
			return (false);
		if (info->zero_pad && info->dot)
			info->zero_pad = false;
		if (info->sign || info->space)
			return (false);
		return (true);
	}
	if (type == 'p')
	{
		if (info->width > INT_MAX || info->prec > INT_MAX)
			return (false);
		info->is_pointer = true;
		if (info->sign || info->space || info->zero_pad || info->prefix)
			return (false);
		if (info->dot && !info->dot_only)
			return (false);
		info->prefix = true;
		return (true);
	}
	return (false);
}

bool	is_flag_valid(char c, t_printf_info *info)
{
	if (c == 'c')
		return (is_valid_strs(*info, 'c'));
	if (c == 's')
		return (is_valid_strs(*info, 's'));
	if (c == 'd' || c == 'i')
		return (is_valid_num(info, 'd'));
	if (c == 'u')
		return (is_valid_num(info, 'u'));
	if (c == 'x' || c == 'X')
		return (is_valid_hex(info, 'x'));
	if (c == 'p')
		return (is_valid_hex(info, 'p'));
	if (c == '%')
		return (true);
	return (false);
}
