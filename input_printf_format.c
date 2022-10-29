/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_printf_format.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 22:06:48 by takira            #+#    #+#             */
/*   Updated: 2022/10/28 22:06:50 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	input_flag(char *fmt, size_t *i, t_printf_info *info)
{
	const char		*flags = "-+ #";

	while (ft_strchr(flags, fmt[*i]) != NULL)
	{
		if (fmt[*i] == '-')
			info->left = true;
		if (fmt[*i] == '+')
			info->sign = true;
		if (fmt[*i] == ' ')
			info->space = true;
		if (fmt[*i] == '#')
			info->prefix = true;
		*i += 1;
	}
}

static void	set_width(int arg, t_printf_info *info)
{
	int	input;

	input = arg;
	if (input >= 0)
		info->width = input;
	else
	{
		info->width = -input;
		info->left = true;
		info->zero_pad = false;
	}
}

bool	input_width(char *fmt, size_t *i, t_printf_info *info, va_list *ptr)
{
	if (fmt[*i] == '*' || ft_isdigit(fmt[*i]))
	{
		while (fmt[*i] == '0')
		{
			info->zero_pad = true;
			*i += 1;
		}
		if (fmt[*i] == '*')
		{
			set_width(va_arg(*ptr, int), info);
			*i += 1;
			if (info->zero_pad && ft_isdigit(fmt[*i]))
				return (false);
		}
		while (ft_isdigit(fmt[*i]))
			info->width = info->width * 10 + fmt[(*i)++] - '0';
		if (fmt[*i] == '*')
			return (false);
	}
	return (true);
}

static void	check_prec(t_printf_info *info)
{
	if (info->prec < 0)
	{
		info->dot = false;
		info->prec = 0;
	}
	if (info->prec)
		info->dot_only = false;
}

bool	input_prec(char *fmt, size_t *i, t_printf_info *info, va_list *ptr)
{
	if (fmt[*i] == '.')
	{
		info->dot = true;
		info->dot_only = true;
		*i += 1;
		if (fmt[*i] == '*')
		{
			info->prec = va_arg(*ptr, int);
			info->dot_only = false;
			*i += 1;
			if (ft_isdigit(fmt[*i]))
				return (false);
		}
		while (ft_isdigit(fmt[*i]))
			info->prec = info->prec * 10 + fmt[(*i)++] - '0';
		check_prec(info);
		if (fmt[*i] == '*')
			return (false);
	}
	return (true);
}
