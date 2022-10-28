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

int	print_fmt(va_list *ptr, const char c, t_printf_info info)
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

void	check_flag(char *fmt, size_t *i, t_printf_info *info)
{
	const char		*flags = "-+ #";

	while (ft_strchr(flags, fmt[*i]) != NULL)
	{
//		printf("#DEBUG[check flg fmt:%c]", *fmt);
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
	return ;
}

static bool	check_width(char *fmt, size_t *i, t_printf_info *info, va_list *ptr)
{
	if (fmt[*i] == '*' || ft_isdigit(fmt[*i]))
	{
//		printf("#DEBUG[check width fmt:%c]", fmt[*i]);
		while (fmt[*i] == '0')
		{
			info->zero_pad = true;
			*i += 1;
		}
		if (fmt[*i] == '*')
		{
			info->width = va_arg(*ptr, int);
			if (info->width < 0)
			{
				info->left = true;
				info->width = -info->width;
				info->zero_pad = false;
			}
			*i += 1;
			if (info->zero_pad && ft_isdigit(fmt[*i]))
				return (false);
		}
		while (ft_isdigit(fmt[*i]))
		{
			info->width = info->width * 10 + fmt[*i] - '0';
			*i += 1;
		}
		if (fmt[*i] == '*')
			return (false);
	}
//	printf("#DEBUG[check width:%d]", info->width);
	return (true);
}


static bool	check_perc(char *fmt, size_t *i, t_printf_info *info, va_list *ptr)
{
	if (fmt[*i] == '.')
	{
//		printf("#DEBUG[check perc fmt:%c]", *fmt);
		info->dot = true;
		info->dot_only = true;
		*i += 1;
		if (fmt[*i] == '*')
		{
			info->perc = va_arg(*ptr, int);
			if (info->perc < 0)
				info->perc = -1;
			info->dot_only = false;
			*i += 1;
			if (ft_isdigit(fmt[*i]))
				return (false);
		}
		while (ft_isdigit(fmt[*i]))
		{
			info->perc = info->perc * 10 + fmt[*i] - '0';
			*i += 1;
		}
		if (info->perc)
			info->dot_only = false;
		if (fmt[*i] == '*')
			return (false);
	}
//	printf("#DEBUG[check perc %d]", info->perc);
	return (true);
}



int ft_printf(const char *fmt, ...)
{
	va_list 		ptr;
	size_t			bytes;
	size_t			i;
	t_printf_info	info;
	int 			ret_val;

	i = 0;
	va_start(ptr, fmt);
	bytes = 0;
	while (fmt[i])
	{
		if (fmt[i] != '%' )
		{
			ft_putchar_fd(fmt[i], 1);
			bytes++;
			i++;
			continue ;
		}
		i++;
		init_print_info(&info);
		check_flag((char *)fmt,&i, &info);
		if (!check_width((char *)fmt, &i, &info, &ptr))
			return (-1);
		if (!check_perc((char *)fmt, &i, &info, &ptr))
			return (-1);
		if (!is_valid(fmt[i], &info))
			return (-1);
		ret_val = print_fmt(&ptr, fmt[i], info);
		if (ret_val < 0)
			return (-1);
		bytes += ret_val;
		i++;
	}
	va_end(ptr);
	return ((int)bytes);
}


/*  idx 追加前
 *

 void	check_flag(char *fmt, t_printf_info *info)
{
	const char		*flags = "-+ #";

	while (ft_strchr(flags, *fmt) != NULL)
	{
		printf("#DEBUG[check flg fmt:%c]", *fmt);
		if (*fmt == '-')
			info->left = true;
		if (*fmt == '+')
			info->sign = true;
		if (*fmt == ' ')
			info->space = true;
		if (*fmt == '#')
			info->prefix = true;
		*fmt += 1;
	}
	return ;
}

static bool	check_width(char *fmt, t_printf_info *info, va_list *ptr)
{
	if (*fmt == '*' || ft_isdigit(*fmt))
	{
		printf("#DEBUG[check width fmt:%c]", *fmt);
		while (*fmt == '0')
		{
			info->zero_pad = true;
			*fmt += 1;
		}
		if (*fmt == '*')
		{
			info->width = va_arg(*ptr, int);
			if (info->width < 0)
			{
				info->left = true;
				info->width = -info->width;
				info->zero_pad = false;
			}
			*fmt += 1;
			if (info->zero_pad && ft_isdigit(*fmt))
				return (false);
		}
		while (ft_isdigit(*fmt))
		{
			info->width = info->width * 10 + *fmt - '0';
			*fmt += 1;
		}
		if (*fmt == '*')
			return (false);
	}
	printf("#DEBUG[check width:%d]", info->width);
	return (true);
}


static bool	check_perc(char *fmt, t_printf_info *info, va_list *ptr)
{
	if (*fmt == '.')
	{
		printf("#DEBUG[check perc fmt:%c]", *fmt);
		info->dot = true;
		info->dot_only = true;
		*fmt += 1;
		if (*fmt == '*')
		{
			info->perc = va_arg(*ptr, int);
			if (info->perc < 0)
				info->perc = -1;
			info->dot_only = false;
			*fmt += 1;
			if (ft_isdigit(*fmt))
				return (false);
		}
		while (ft_isdigit(*fmt))
		{
			info->perc = info->perc * 10 + *fmt - '0';
			*fmt += 1;
		}
		if (info->perc)
			info->dot_only = false;
		if (*fmt == '*')
			return (false);
	}
	printf("#DEBUG[check perc %d]", info->perc);
	return (true);
}



int ft_printf(const char *fmt, ...)
{
	va_list 		ptr;
	size_t			bytes;
	t_printf_info	info;
	int 			ret_val;

	va_start(ptr, fmt);
	bytes = 0;
	while (*fmt != '\0')
	{
		if (*fmt != '%' )
		{
			ft_putchar_fd(*fmt, 1);
			bytes++;
			i++;
			continue ;
		}
		i++;
		init_print_info(&info);
		check_flag((char *)fmt, &info);
		if (!check_width((char *)fmt, &info, &ptr))
			return (-1);
		if (!check_perc((char *)fmt, &info, &ptr))
			return (-1);
		printf("[before valid]");
		if (!is_valid(*fmt, &info))
			return (-1);
		printf("[after valid]");
		ret_val = print_fmt(&ptr, *fmt, info);
		if (ret_val < 0)
			return (-1);
		bytes += ret_val;
		i++;
	}
	va_end(ptr);
	return ((int)bytes);
}


 *
 */