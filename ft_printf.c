/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:52:04 by takira            #+#    #+#             */
/*   Updated: 2022/11/13 15:37:19 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	init_print_info(t_printf_info *info)
{
	info->flag_left = false;
	info->flag_sign = false;
	info->flag_space = false;
	info->flag_prefix = false;
	info->flag_zero_pad = false;
	info->prec_dot = false;
	info->prec_dot_only = false;
	info->is_pointer = false;
	info->width_size = 0;
	info->prec_size = 0;
	info->num_base = 10;
	info->num_capitals = 0;
	info->num_padlen = 0;
	info->num_preclen = 0;
	info->num_head_chr = "";
}

static int	pass_to_each_printfunc(const char c, t_printf_info info, va_list *p)
{
	if (c == 'c')
		return (print_c(va_arg(*p, int), info));
	if (c == 's')
		return (print_s(va_arg(*p, char *), info));
	if (c == 'p')
		return (print_hex(va_arg(*p, uintptr_t), &info, false));
	if (c == 'd' || c == 'i')
		return (print_signed(va_arg(*p, long), &info));
	if (c == 'u')
		return (print_unsigned(va_arg(*p, unsigned int), info));
	if (c == 'x')
		return (print_hex(va_arg(*p, unsigned int), &info, false));
	if (c == 'X')
		return (print_hex(va_arg(*p, unsigned int), &info, true));
	if (c == '%')
		return (print_percent(info));
	return (-1);
}

static int	print_fmt(char *fmt, size_t *i, t_printf_info *info, va_list *ptr)
{
	init_print_info(info);
	get_flag((char *)fmt, i, info);
	if (get_width((char *) fmt, i, info, ptr) == FAIL)
		return (-1);
	if (get_prec((char *) fmt, i, info, ptr) == FAIL)
		return (-1);
	if (valid_info4fmt(fmt[*i], info) == FAIL)
		return (-1);
	return (pass_to_each_printfunc(fmt[*i], *info, ptr));
}

int	ft_printf(const char *fmt, ...)
{
	size_t			i;
	va_list			ptr;
	t_printf_info	info;
	int				print_bytes;
	int				sum_print_bytes;

	va_start(ptr, fmt);
	sum_print_bytes = 0;
	i = 0;
	while (fmt[i])
	{
		if (fmt[i] != '%')
		{
			sum_print_bytes += ft_putchar_fd(fmt[i++], 1);
			continue ;
		}
		i++;
		print_bytes = print_fmt((char *)fmt, &i, &info, &ptr);
		if (print_bytes < 0)
			return (-1);
		sum_print_bytes += print_bytes;
		i++;
	}
	va_end(ptr);
	return (sum_print_bytes);
}
