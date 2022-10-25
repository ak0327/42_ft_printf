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
#include <stdio.h>
/* If `long' and `int' is effectively the same type we don't have to
   handle `long separately.  */
//#if INT_MAX == LONG_MAX
//# define is_long_num	0
//#else
//# define is_long_num	is_long
//#endif

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

int	get_hex_digit(unsigned long long n)
{
	int	ret;

	ret = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n /= 16;
		ret++;
	}
	return (ret);
}

char	*dec2hex(unsigned int decnum, bool isupper)
{
	char			*hex;
	const char		*hex_symbol = "0123456789abcdef0123456789ABCDEF";
	size_t			hex_digit;
	int 			capitals;

	if (isupper)
		capitals = 16;
	else
		capitals = 0;
	hex_digit = get_hex_digit(decnum);
	hex = (char *)ft_calloc(hex_digit + 1, sizeof(char));
	if (hex == NULL)
		return (NULL);
	hex[hex_digit] = '\0';
	while (hex_digit > 0)
	{
		hex[hex_digit - 1] = hex_symbol[decnum % 16 + capitals];
		decnum /= 16;
		hex_digit--;
	}
	return (hex);
}

char	*dec2lx(long n)
{
	unsigned long	decnum;
	char			*lhex;
	const char		*hex_symbol = "0123456789abcdef";
	size_t			hex_digit;

	decnum = (unsigned long)n;
	hex_digit = get_hex_digit(n);
	lhex = (char *)ft_calloc(hex_digit + 1, sizeof(char));
	if (lhex == NULL)
		return (NULL);
	lhex[hex_digit] = '\0';
	while (hex_digit > 0)
	{
		lhex[hex_digit - 1] = hex_symbol[decnum % 16];
		decnum /= 16;
		hex_digit--;
	}
	return (lhex);
}

char	*address2lx(long amp_p) // &pが入ってくる
{
	const size_t	size = sizeof(amp_p);
	char			*hex;
	char			*lhex;

	hex = dec2lx(amp_p);
	if (!hex)
		return (NULL);
	lhex = (char *)ft_calloc(size + 3, sizeof(char));
	if (!lhex)
		return (NULL);
	ft_memcpy(&lhex[0], "0x", 2);
	ft_memcpy(&lhex[2], hex, size+1); // TODO +1? size=8byte
	lhex[size + 3] = '\0';
	free(hex);
	return (lhex);
}

char	*ret_c(const char chr, t_printf_info info)
{
	char	*ret;
	size_t	size;
//	printf("#DEBUG[ret_c chr:%c]", chr);
	if (info.sign || info.space || info.prefix || info.perc || info.zero_pad)
		return (NULL);
	size = maxsize(info.width, 1);
//	printf("#DEBUG[ret_c] size:%zu ", size);
	ret = (char *)ft_calloc(sizeof(char), size + 1);
	if (!ret)
		return (NULL);
//	printf("#DEBUG[ret_c size:%zu]", size);
	ft_memset(&ret[0], ' ', size);
	if (info.left)
		ret[0] = chr;
	else
		ret[size-1] = chr;
//	printf("#DEBUG[ret_c ret:%s]", ret);
	return (ret);
}

char	*ret_s(char *str, t_printf_info info)
{
	char	*ret;
	size_t	size;

	if (info.sign || info.space || info.prefix || info.zero_pad) // !str; str=NULL
		return (NULL);
	if (!str)
		str = "(null)";
	size = maxsize(info.width, ft_strlen(str));
//	printf("#DEBUG[info.width:%u]", info.width);
//	printf("#DEBUG[size:%zu]", size);
	ret = (char *) ft_calloc(sizeof(char), size + 1);
	if (!ret)
		return (NULL);
	ft_memset(&ret[0], ' ', size);
//	printf("#DEBUG[ret(' '):%s, len:%zu]", ret, ft_strlen(ret));
	if (info.left)
		ft_memcpy(&ret[0], str, ft_strlen(str));
	else
		ft_memcpy(&ret[size - ft_strlen(str)], str, ft_strlen(str));
	return (&ret[0]);
}

char	*ret_p(const long amp_p, t_printf_info info)
{
	char	*ret;
	char	*address;
	size_t	size;

	if (info.sign || info.space || info.prefix || info.perc || info.zero_pad)
		return (NULL);
	address = address2lx(amp_p);
	if (!address)
		return (NULL);
	size = maxsize(info.width, ft_strlen(address));
	ret = (char *) ft_calloc(sizeof(char), size + 1);
	if (!ret)
	{
		free(address);
		return (NULL);
	}
	ft_memset(ret, ' ', size);
	if (info.left)
		ft_memcpy(&ret[0], address, size);
	else
		ft_memcpy(&ret[size - ft_strlen(address)], address, size);
	free(address);
	return (ret);
}

//
//char	*ret_dec(const signed int num, t_printf_info info)
//{
//	char	*ret;
//	char	*itoa;
//	size_t	size;
//	size_t	itoa_len;
//	size_t	idx;
//
////	printf("#DEBUG[ret_dec info.perc:%u]", info.perc);
//	if ((info.sign && info.space) || info.prefix)
//		return (NULL);
//	itoa = ft_itoa(num);
//	if (!itoa)
//		return (NULL);
//	itoa_len = maxsize(info.perc, ft_strlen(itoa));
//	if ((info.sign || info.space) && num >= 0)
//		itoa_len++;
//	size = maxsize(info.width, itoa_len);
//	ret = (char *)ft_calloc(sizeof(char), size + 1);
//	if (!ret)
//		return (NULL);
//	idx = 0;
//	if (info.width > itoa_len)
//	{
//		if (info.zero_pad && !info.perc)
//			ft_memset(&ret[idx], '0', info.width - itoa_len);
//		else
//			ft_memset(&ret[idx], ' ', info.width - itoa_len);
//		idx += info.width - itoa_len;
//	}
//	if (info.sign && num >= 0)
//	{
//		ft_memset(&ret[idx], '+', 1);
//		idx++;
//	}
//	if (info.space && num >= 0)
//	{
//		ft_memset(&ret[idx], ' ', 1);
//		idx++;
//	}
////	printf("#DEBUG[ret_dec idx:%zu, perc:%u]", idx, info.perc);
//	if (info.perc > ft_strlen(itoa))
//	{
//		ft_memset(&ret[idx], '0', info.perc - ft_strlen(itoa));
//		idx += info.perc - ft_strlen(itoa);
//	}
//	ft_memcpy(&ret[idx], itoa, ft_strlen(itoa));
//	free(itoa);
//	return (ret);
//}

char	*ret_dec(const signed int num, t_printf_info info)
{
	char	*ret;
	char	*itoa;
	size_t	size;
	size_t	itoa_len;
	size_t	idx;

	if (num < 0)
		info.put_minus = false;

//	printf("#DEBUG[ret_dec info.perc:%u]", info.perc);
	if ((info.sign && info.space) || info.prefix)
		return (NULL);
	itoa = ft_itoa(num);
	if (!itoa)
		return (NULL);
	itoa_len = maxsize(info.perc, ft_strlen(itoa));
	if ((info.sign || info.space) && num >= 0)
		itoa_len++;
	size = maxsize(info.width, itoa_len);
	ret = (char *)ft_calloc(sizeof(char), size + 1);
	if (!ret)
		return (NULL);
	idx = 0;
	if (info.width > itoa_len)
	{
		if (info.zero_pad && !info.perc && info.put_minus)
			ft_memset(&ret[0], '0', info.width - itoa_len);
		else if (info.zero_pad && !info.perc && !info.put_minus)
		{
			ft_memset(&ret[0], '-', 1);
			ft_memset(&ret[1], '0', info.width - itoa_len);
			info.put_minus = true;
		}
		else
			ft_memset(&ret[idx], ' ', info.width - itoa_len);
		idx += info.width - itoa_len;
	}
	if (info.sign && num >= 0)
	{
		ft_memset(&ret[idx], '+', 1);
		idx++;
	}
	if (info.space && num >= 0)
	{
		ft_memset(&ret[idx], ' ', 1);
		idx++;
	}
//	printf("#DEBUG[ret_dec idx:%zu, perc:%u]", idx, info.perc);
	if (info.perc > ft_strlen(itoa))
	{
		if (info.put_minus)
			ft_memset(&ret[idx], '0', info.perc - ft_strlen(itoa));
		else
		{
			ft_memset(&ret[idx], '-', 1);
			ft_memset(&ret[idx + 1], '0', info.perc - ft_strlen(itoa) + 1);
			info.put_minus = true;
			idx++;
		}
		idx += info.perc - ft_strlen(itoa);
	}
	if (num < 0 && info.put_minus)
		ft_memcpy(&ret[idx+1], &itoa[1], ft_strlen(itoa) - 1);
	else
		ft_memcpy(&ret[idx], itoa, ft_strlen(itoa));
	free(itoa);
	return (ret);
}


char	*ret_u(const unsigned int num, t_printf_info info)
{
	char	*ret;
	char	*uitoa;
	size_t	size;
	size_t	uitoa_len;
	size_t	idx;

//	printf("#DEBUG[ret_u num:%u]", num);
	if (info.sign && info.space)
		return (NULL);
	uitoa = ft_uitoa(num);
//	printf("#DEBUG[ret_u uitoa:%s]", uitoa);
	if (!uitoa)
		return (NULL);
	uitoa_len = maxsize(info.perc, ft_strlen(uitoa));
	size = maxsize(info.width, uitoa_len);
	ret = (char *)ft_calloc(sizeof(char), size + 1);
	if (!ret)
		return (NULL);
	idx = 0;
	if (info.width > uitoa_len)
	{
		if (info.zero_pad && !info.perc)
			ft_memset(&ret[idx], '0', info.width - uitoa_len);
		else
			ft_memset(&ret[idx], ' ', info.width - uitoa_len);
		idx += info.width - uitoa_len;
	}
	if (info.perc > ft_strlen(uitoa))
	{
		ft_memset(&ret[idx], '0', info.perc - ft_strlen(uitoa));
		idx += info.perc - ft_strlen(uitoa);
	}
	ft_memcpy(&ret[idx], uitoa, ft_strlen(uitoa));
	free(uitoa);
//	printf("#DEBUG[ret_u: %s]", ret);
	return (ret);
}

char	*ret_hex(const unsigned int num, t_printf_info info, bool isupper)
{
	char			*ret;
	char			*hex;
	size_t			size;
	size_t			hex_len;
	size_t			idx;

	if (info.sign || info.space)
		return (NULL);
	hex = dec2hex(num, isupper);
	if (!hex)
		return (NULL);
	hex_len = info.prefix * 2 + maxsize(info.perc,ft_strlen(hex));
	size = maxsize(info.width, hex_len);
	ret = (char *) ft_calloc(sizeof(char), size + 1);
	if (!ret)
	{
		free(hex);
		return (NULL);
	}
	idx = 0;
	if (info.width > hex_len)
	{
		if (info.zero_pad && !info.perc)
			ft_memset(&ret[idx], '0', info.width - hex_len);
		else
			ft_memset(&ret[idx], ' ', info.width - hex_len);
		idx += info.width - hex_len;
	}
	if (info.prefix)
	{
		if (isupper)
			ft_memcpy(&ret[idx], "0X", 2);
		else
			ft_memcpy(&ret[idx], "0x", 2);
		idx += 2;
	}
	if (info.perc > ft_strlen(hex))
	{
		ft_memset(&ret[idx], '0', info.perc - ft_strlen(hex));
		idx += info.perc - ft_strlen(hex);
	}
	ft_memcpy(&ret[idx], hex, ft_strlen(hex));
	free(hex);
//	printf("ret_xX: %s ", ret);
	return (ret);
}


char	*ret_put_fmt(va_list *ptr, const char c, t_printf_info info)
{
	if (c == 'c')
		return (ret_c(va_arg(*ptr, unsigned int), info));
	else if (c == 's')
		return (ret_s(va_arg(*ptr, char*), info));
	else if (c == 'p')
		return (ret_p(va_arg(*ptr, long), info));
	else if (c == 'd' || c == 'i')
		return (ret_dec(va_arg(*ptr, signed int), info));
	else if (c == 'u')
		return (ret_u(va_arg(*ptr, unsigned int), info));
	else if (c == 'x')
		return (ret_hex(va_arg(*ptr, unsigned int), info, false));
	else if (c == 'X')
		return (ret_hex(va_arg(*ptr, unsigned int), info, true));
	return (NULL);
}

static void	init_print_info(t_printf_info *info)
{
	// flag
	info->left = 0;
	info->sign = 0;
	info->space = 0;
	info->prefix = 0;

	// width
	info->width = 0;
	info->zero_pad = 0;

	// perc
	info->perc = 0;

	info->put_minus = true;
}

int ft_printf(const char *fmt, ...)
{
	va_list 		ptr;
//	size_t			len = ft_strlen(fmt);
//	size_t			cnt;
	size_t			bytes;
	const char		*types = "cspdiuxX";
	const char		*flags = "-+ #";
	t_printf_info	info;
	char			*fmt_str;

	va_start(ptr, fmt);
	bytes = 0;
	//	cnt = count_types_in_fmt(fmt); // typeのcheckに使う？

	while (*fmt != '\0')
	{
		if (*fmt != '%' )
		{
			bytes += ft_putchar_fd(*fmt, 1);
			fmt++;
			continue ;
		}
		fmt++; // next of %
		if (*fmt == '%') // %%
		{
			bytes += ft_putchar_fd(*fmt, 1);
			fmt++;
			continue ;
		}
		init_print_info(&info);

		// flg check : [-+ #] //
		while (ft_strchr(flags, *fmt) != NULL)
		{
			if (*fmt == '-')
				info.left = 1;
			if (*fmt == '+')
				info.sign = 1;
			if (*fmt == ' ')
				info.space = 1;
			if (*fmt == '#')
				info.prefix = 1;
			fmt++;
		}
		// width : [* or num]
		if (*fmt == '*' || ft_isdigit(*fmt))
		{
			if (*fmt == '*') // *の場合引数はint
			{
				info.width = va_arg(ptr, int);
				fmt++;
				if (ft_isdigit(*fmt))
					return (-1); // [* num]
			}
//			printf("#DEBUG[before while info.width:%u]", info.width);
			while (ft_isdigit(*fmt))
			{
//				printf("#DEBUG[while *fmt:%c]", *fmt);
				if (info.width == 0 && *fmt == '0')
					info.zero_pad = 1;
				else
					info.width = info.width * 10 + *fmt - '0';
				fmt++;
			}
//			printf("#DEBUG[after while info.width:%u]", info.width);
			if (*fmt == '*')
				return (-1); // [num *]
		}
		// perc
		if (*fmt == '.') //. only -> next
		{
			fmt++; // next of .
			if (*fmt == '*') // *の場合引数はint
			{
				info.perc = va_arg(ptr, int);
				fmt++;
				if (ft_isdigit(*fmt))
					return (-1); // [* num]
			}
			while (ft_isdigit(*fmt))
			{
				info.perc = info.perc * 10 + *fmt - '0';
				fmt++;
			}
//			printf("#DEBUG[ft_printf info.perc:%u]", info.perc);
			if (*fmt == '*')
				return (-1); // [num *]
		}
		if (ft_strchr(types, *fmt) == NULL)
			return (-1);
		// type & put
		fmt_str = ret_put_fmt(&ptr, *fmt, info);
		if (!fmt_str)
			return (-1);
//		printf("#DEBUG[ft_printf fmt_str:%s]", fmt_str);
		ft_putstr_fd(fmt_str, 1);
		bytes += ft_strlen(fmt_str);
		free(fmt_str);
		fmt++;
	}
	va_end(ptr);
	return ((int)bytes);
}
