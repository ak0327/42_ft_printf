/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_printf_format.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 22:06:48 by takira            #+#    #+#             */
/*   Updated: 2022/11/15 22:17:48 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	get_flag(char *fmt, t_printf_info *info)
{
	const char		*flags = "-+ #0";

	while (fmt[info->fmt_idx] && ft_strchr(flags, fmt[info->fmt_idx]) != NULL)
	{
		if (fmt[info->fmt_idx] == '-')
			info->flag_left = true;
		if (fmt[info->fmt_idx] == '+')
			info->flag_sign = true;
		if (fmt[info->fmt_idx] == ' ')
			info->flag_space = true;
		if (fmt[info->fmt_idx] == '#')
			info->flag_prefix = true;
		if (fmt[info->fmt_idx] == '0')
			info->flag_zero_pad = true;
		info->fmt_idx++;
	}
}

int	get_width(char *fmt, t_printf_info *info, va_list *p)
{
	int	input_arg;

	if (fmt[info->fmt_idx] == '*' || ft_isdigit(fmt[info->fmt_idx]))
	{
		if (fmt[info->fmt_idx] == '*')
		{
			input_arg = va_arg(*p, int);
			if (input_arg >= 0)
				info->w_size = input_arg;
			else
			{
				info->w_size = -input_arg;
				info->flag_left = true;
				info->flag_zero_pad = false;
			}
			info->fmt_idx++;
			if (info->flag_zero_pad && ft_isdigit(fmt[info->fmt_idx]))
				return (FAIL);
		}
		while (ft_isdigit(fmt[info->fmt_idx]))
			info->w_size = info->w_size * 10 + fmt[info->fmt_idx++] - '0';
		if (fmt[info->fmt_idx] == '*')
			return (FAIL);
	}
	return (PASS);
}

static void	update_prec_params(t_printf_info *info)
{
	if (info->p_size < 0)
	{
		info->prec_dot = false;
		info->p_size = 0;
	}
	if (info->p_size)
		info->prec_dot_only = false;
}

int	get_prec(char *fmt, t_printf_info *info, va_list *p)
{
	if (fmt[info->fmt_idx] == '.')
	{
		info->prec_dot = true;
		info->prec_dot_only = true;
		info->fmt_idx += 1;
		if (fmt[info->fmt_idx] == '*')
		{
			info->p_size = va_arg(*p, int);
			info->prec_dot_only = false;
			info->fmt_idx += 1;
			if (ft_isdigit(fmt[info->fmt_idx]))
				return (FAIL);
		}
		while (ft_isdigit(fmt[info->fmt_idx]))
			info->p_size = info->p_size * 10 + fmt[info->fmt_idx++] - '0';
		update_prec_params(info);
		if (fmt[info->fmt_idx] == '*')
			return (FAIL);
	}
	return (PASS);
}
