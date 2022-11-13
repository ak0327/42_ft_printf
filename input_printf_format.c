/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_printf_format.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 22:06:48 by takira            #+#    #+#             */
/*   Updated: 2022/11/13 15:36:58 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	get_flag(char *fmt, size_t *i, t_printf_info *info)
{
	const char		*flags = "-+ #0";

	while (fmt[*i] && ft_strchr(flags, fmt[*i]) != NULL)
	{
		if (fmt[*i] == '-')
			info->flag_left = true;
		if (fmt[*i] == '+')
			info->flag_sign = true;
		if (fmt[*i] == ' ')
			info->flag_space = true;
		if (fmt[*i] == '#')
			info->flag_prefix = true;
		if (fmt[*i] == '0')
			info->flag_zero_pad = true;
		*i += 1;
	}
}

int	get_width(char *fmt, size_t *i, t_printf_info *info, va_list *p)
{
	int	input_arg;

	if (fmt[*i] == '*' || ft_isdigit(fmt[*i]))
	{
		if (fmt[*i] == '*')
		{
			input_arg = va_arg(*p, int);
			if (input_arg >= 0)
				info->width_size = input_arg;
			else
			{
				info->width_size = -input_arg;
				info->flag_left = true;
				info->flag_zero_pad = false;
			}
			*i += 1;
			if (info->flag_zero_pad && ft_isdigit(fmt[*i]))
				return (FAIL);
		}
		while (ft_isdigit(fmt[*i]))
			info->width_size = info->width_size * 10 + fmt[(*i)++] - '0';
		if (fmt[*i] == '*')
			return (FAIL);
	}
	return (PASS);
}

static void	update_prec_params(t_printf_info *info)
{
	if (info->prec_size < 0)
	{
		info->prec_dot = false;
		info->prec_size = 0;
	}
	if (info->prec_size)
		info->prec_dot_only = false;
}

int	get_prec(char *fmt, size_t *i, t_printf_info *info, va_list *p)
{
	if (fmt[*i] == '.')
	{
		info->prec_dot = true;
		info->prec_dot_only = true;
		*i += 1;
		if (fmt[*i] == '*')
		{
			info->prec_size = va_arg(*p, int);
			info->prec_dot_only = false;
			*i += 1;
			if (ft_isdigit(fmt[*i]))
				return (FAIL);
		}
		while (ft_isdigit(fmt[*i]))
			info->prec_size = info->prec_size * 10 + fmt[(*i)++] - '0';
		update_prec_params(info);
		if (fmt[*i] == '*')
			return (FAIL);
	}
	return (PASS);
}
