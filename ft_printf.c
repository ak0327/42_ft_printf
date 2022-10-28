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
/* If `long' and `int' is effectively the same type we don't have to
   handle `long separately.  */

size_t	maxsize(size_t a, size_t b)
{
	if (a >= b)
		return (a);
	return (b);
}

size_t	minsize(size_t a, size_t b)
{
	if (a <= b)
		return (a);
	return (b);
}

size_t	count_types_in_fmt(const char *fmt)
{
	size_t		cnt;
	size_t		i;
	const char	*types = "cspdiuxX%";

	cnt = 0;
	i = 0;
	while (fmt[i] != '\0')
	{
		while (fmt[i] != '\0' && fmt[i] != '%')
			i++;
		if (fmt[i] != '\0' && ft_strchr(types, fmt[i + 1]))
		{
			cnt++;
			i++;
		}
		i++;
	}
	return (cnt);
}

int	print_fmt(va_list *ptr, const char c, t_printf_info info)
{
	if (c == 'c')
		return (print_c(va_arg(*ptr, int), info));
	if (c == 's')
		return (print_s(va_arg(*ptr, char*), info));
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

static void	init_print_info(t_printf_info *info)
{
	info->left = false;
	info->sign = false;
	info->space = false;
	info->prefix = false;
	info->width = 0;
	info->zero_pad = false;
	info->dot = false;
	info->dot_only = false;
	info->perc = 0;
	info->base = 10;
	info->capitals = 0;
	info->digits = "0123456789abcdef0123456789ABCDEF";
	info->head_chr = "";
	info->is_pointer = false;
	info->size = 0;
	info->strlen = 0;
	info->padlen = 0;
	info->perclen = 0;
}

static bool	is_valid_c(t_printf_info info)
{
	if (info.sign || info.space || info.zero_pad)
		return (false);
	if (info.dot && !info.dot_only) // OK: %.c, NG: %.0c
		return (false);
	return (true);
}

static bool	is_valid_s(t_printf_info info)
{
	if (info.sign || info.space || info.zero_pad || info.prefix)
		return (false);
	return (true);
}

static bool	is_valid_p(t_printf_info *info)
{
	info->base = 16;
	info->is_pointer = true;
	if (info->sign || info->space || info->zero_pad || info->prefix)
		return (false);
	if (info->dot && !info->dot_only) // OK: %.p, NG: %.0p
		return (false);
	info->prefix = true;
	return (true);
}

static bool	is_valid_d(t_printf_info *info)
{
	if (info->perc < 0) // 先に決める
	{
		info->dot = false;
		info->perc = 0;
	}
	if (info->zero_pad && info->dot)
		info->zero_pad = false;
	if ((info->sign && info->space) || info->prefix || (info->zero_pad && info->left))
		return (false);
	return (true);
}

static bool	is_valid_u(t_printf_info *info)
{
	if (info->zero_pad && info->dot)
		info->zero_pad = false;
	if (info->sign || info->space || info->prefix)
		return (false);
	return (true);
}

static bool	is_valid_hex(t_printf_info *info)
{
	info->base = 16;
	if (info->zero_pad && info->dot)
		info->zero_pad = false;
	if (info->sign || info->space)
		return (false);
	return (true);
}

static bool is_valid(const char c, t_printf_info *info)
{
	if (c == 'c')
		return (is_valid_c(*info));
	if (c == 's')
		return (is_valid_s(*info));
	if (c == 'p')
		return (is_valid_p(info));
	if (c == 'd' || c == 'i')
		return (is_valid_d(info));
	if (c == 'u')
		return (is_valid_u(info));
	if (c == 'x' || c == 'X')
		return (is_valid_hex(info));
	if (c == '%')
		return (true);
	return (false);
}

int ft_printf(const char *fmt, ...)
{
	va_list 		ptr;
	size_t			bytes;
	const char		*flags = "-+ #";
	t_printf_info	info;
	int				input;
	int 			ret_val;

	va_start(ptr, fmt);
	bytes = 0;
	while (*fmt != '\0')
	{
		if (*fmt != '%' )
		{
			ft_putchar_fd(*fmt, 1);
			bytes++;
			fmt++;
			continue ;
		}
		fmt++; // next of %
		init_print_info(&info);
		// flg check : [-+ #] //
		while (ft_strchr(flags, *fmt) != NULL)
		{
			if (*fmt == '-')
				info.left = true;
			if (*fmt == '+')
				info.sign = true;
			if (*fmt == ' ')
				info.space = true;
			if (*fmt == '#')
				info.prefix = true;
			fmt++;
		}
		// width : [* or num]
		if (*fmt == '*' || ft_isdigit(*fmt))
		{
			while (*fmt == '0')
			{
				info.zero_pad = true;
				fmt++;
			}
			if (*fmt == '*') // *の場合引数はint
			{
				input = va_arg(ptr, int);
				if (input < 0)
				{
					info.left = true;
					input = -input;
					info.zero_pad = false; // input < 0 で zeropad無視
				}
				info.width = input;
				fmt++;
				if (info.zero_pad && ft_isdigit(*fmt))
					return (-1); // [* num]
			}
			while (ft_isdigit(*fmt))
			{
				info.width = info.width * 10 + *fmt - '0';
				fmt++;
			}
			if (*fmt == '*')
				return (-1); // [num *]
		}
		// perc
		if (*fmt == '.') //. only -> next
		{
			info.dot = true;
			info.dot_only = true;
			fmt++; // next of .
			if (*fmt == '*') // *の場合引数はint, - の場合left
			{
				info.perc = va_arg(ptr, int);
				if (info.perc < 0)
					info.perc = -1;
				info.dot_only = false;
				fmt++;
				if (ft_isdigit(*fmt))
					return (-1); // [* num]
			}
			while (ft_isdigit(*fmt))
			{
				info.perc = info.perc * 10 + *fmt - '0';
				fmt++;
			}
			if (info.perc)
				info.dot_only = false;
			if (*fmt == '*')
				return (-1); // [num *]
		}
		if (!is_valid(*fmt, &info))
			return (-1);

		ret_val = print_fmt(&ptr, *fmt, info);
		if (ret_val < 0)
			return (-1);
		bytes += ret_val;
		fmt++;
	}
	va_end(ptr);
	return ((int)bytes);
}
