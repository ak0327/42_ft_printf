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

char	*convert_u2base(unsigned long u, int base, int capitals)
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
	ret = (char *) calloc(sizeof(char), len + 1);
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

void	set_params(unsigned long u, t_printf_info *info, size_t *padlen, size_t *perclen)
{
	size_t	len = 0;
	*padlen = 0;
	*perclen = 0;

	if (u == 0 && info->head_c && !info->is_pointer) // %p 0x0
		info->head_c = "";

	// [   00123]
	//       ^^^ numlen
	if (!info->dot_only && u == 0)
		len += 1;
	while (u > 0)
	{
		u /= info->base;
		len += 1;
	}

	// [   00123]
	//     ^^ perclen
	if ((size_t)info->perc > len)
	{
		*perclen = (size_t)info->perc - len;
		len += *perclen;
	}

	//  [   +00123]    [-00000123]
	//   ^^^ padlen      ^^^^^ perclen (.perc's 0とwidthの0は同時に存在しない)
	if ((size_t)info->width >= (len + ft_strlen(info->head_c)))
	{
		if (info->head_c)                         // [   +00123]  [0xFF]
			len += ft_strlen(info->head_c);    //     ^         ^^

		if (info->zero_pad)
			*perclen = (size_t)info->width - len;
		else
			*padlen = (size_t)info->width - len;
	}
}

int	print_num(unsigned long u, t_printf_info info)
{
	size_t		padlen;
	size_t		perclen;
	char		*numstr;
	int			ret_bytes;

	numstr = convert_u2base(u, info.base, info.capitals);
	if (!numstr)
		return (-1);

	ret_bytes = 0;
	set_params(u, &info, &padlen, &perclen);

	if (!info.left && padlen)  // [   -123], [  -0123]
		while (padlen--)
			ret_bytes += ft_putchar_fd(' ', 1);

	if (info.head_c)
		ret_bytes += ft_putstr_fd(info.head_c, 1);

	if (perclen) // [   00123]
		while (perclen--)
			ret_bytes += ft_putchar_fd('0', 1);

	if (!(info.dot_only && u == 0))
		ret_bytes += ft_putstr_fd(numstr, 1);

	if (info.left && padlen)
		while (padlen--)
			ret_bytes += ft_putchar_fd(' ', 1);

	free(numstr);
	return (ret_bytes);
}

int print_signed(long n, t_printf_info *info)
{
	unsigned long long	u;

	if (n >= 0)
	{
		u = n;
		if (info->sign)
			info->head_c = "+";
		if (info->space)
			info->head_c = " ";
	}
	else
	{
		u = -n;
		info->head_c = "-";
	}
	return (print_num(u, *info));
}

int print_unsigned(unsigned int u, t_printf_info *info)
{
	return (print_num((unsigned long)u, *info));
}

int print_hexadecimal(unsigned long u, t_printf_info *info, bool isupper)
{
	if (isupper)
		info->capitals = 16;

	if (info->prefix)
	{
		if (info->capitals)
			info->head_c = "0X";
		else
			info->head_c = "0x";
	}
	return (print_num(u, *info));
}

//void	print_signed(va_list *ptr, t_printf_info *info)
//{
//	long			n;
//	unsigned long	u;
//
//	if (info->is_signed)
//	{
//		n = va_arg(*ptr, long);
//		if (n >= 0)
//		{
//			u = n;
//			info->head_c = "+";
//		}
//		else
//		{
//			u = -n;
//			info->head_c = "-";
//		}
//	}
//	else
//		u = va_arg(*ptr, unsigned long);
//	print_num(u, *info);
//}




//
//char	*ret_u(unsigned long num, t_printf_info info)
//{
//	char	*ret;
//	char	*numstr;
//	size_t	numlen;
//	size_t	size;
//	size_t	idx;
//
//	utoa = ft_utoa(num);
//	if (!utoa)
//		return (NULL);
//	numlen = maxsize(ft_strlen(utoa), (size_t)info.perc);
//	if (num == 0 && info.dot)
//		numlen = 0;
//	size = maxsize(numlen, info.width);
//	ret = (char *)ft_calloc(sizeof(char), size + 1);
//	if (!ret)
//		return (NULL);
//
//	if ((size > numlen) && !info.zero_pad) // space
//		ft_memset(ret, ' ', size);
//	else if ((size > numlen) && info.zero_pad) // zero pad (zero & leftはNG)
//		ft_memset(ret, '0', size - numlen);
//
//	if (numlen == 0 && info.perc)
//		ft_memset(&ret[!info.left * (size - info.perc)], '0', info.perc);
//
//	idx = !info.left * (size - numlen);
//	if ((numlen > ft_strlen(utoa))) // perc zero, num=0で0をput
//	{
//		ft_memset(&ret[idx], '0', numlen - ft_strlen(utoa));
//		idx += numlen - ft_strlen(utoa);
//	}
//
//	if (numlen)
//		ft_memcpy(&ret[idx], utoa, ft_strlen(utoa));
//	free(utoa);
//	return (ret);
//}

//void	set_sign_flag(long *num, t_printf_info *info)
//{
//	if (*num < 0)
//	{
//		info->minus = 1;
//		info->decimal_sign = '-';
//		info->sign_exist = true;
//		info->show_sign = true;
//		*num = -*num;
//		return ;
//	}
//	if (info->space)
//	{
//		info->decimal_sign = ' ';
//		info->sign_exist = true;
//		info->show_sign = true;
//		return ;
//	}
//	if (info->sign)
//	{
//		info->decimal_sign = '+';
//		info->sign_exist = true;
//		info->show_sign = true;
//		return ;
//	}
//}

/*
//	printf("#DEBUG[ret_dec info.perc:%u]", info.perc);
char	*ret_dec(long num, t_printf_info info) // info.zero && info.left = NG //TODO perce->iotlen
{
	char *ret;
	char *itoa;
	size_t numlen;
	size_t size;
	size_t idx;

	set_sign_flag(&num, &info);
//	printf("#DEBUG[ret_dec decsign:%c, num:%lld]", info.decimal_sign, num);

	itoa = ft_itoa(num);
//	printf("#DEBUG[ret_dec itoa:%s, perc:%d]", itoa, info.perc);
	if (!itoa)
		return (NULL);
	numlen = maxsize(ft_strlen(itoa) + (size_t)info.show_sign, (size_t)info.perc);
	if (num == 0 && info.dot && !info.perc)
		numlen = 0;
	if (info.show_sign && (numlen == (size_t)info.perc) )
		numlen++;
	size = maxsize(numlen, (size_t)info.width);

//	printf("#DEBUG[ret_dec numlen:%zu, size:%zu]", numlen, size);

	ret = (char *) ft_calloc(sizeof(char), size + 1);
	if (!ret)
		return (NULL);

	// space
	if ((size > numlen) && !info.zero_pad) // space
		ft_memset(ret, ' ', size);

	// zero pad
	if ((size > numlen) && info.zero_pad) // space & zeropadはなし（0 perc), zeropadはret[0]~
	{
		if (info.show_sign)
		{
			ft_memset(&ret[0], info.decimal_sign, 1);
			ft_memset(&ret[1], '0', size - 1 - numlen);
			info.show_sign = false;
		}
		else
			ft_memset(ret, '0', size - numlen);
	}

	// perc
	if (numlen == 0 && info.perc) // 0のみ、0埋め
	{
		if (info.show_sign)
		{
			ft_memset(&ret[!info.left * (size - info.perc)], info.decimal_sign, 1);
			ft_memset(&ret[!info.left * (size - info.perc) + 1], '0', info.perc);
			info.show_sign = false;
		}
		else
			ft_memset(&ret[!info.left * (size - info.perc)], '0', info.perc);
	}

	// 符号 + 0埋め
	idx = !info.left * (size - numlen);
	if ((numlen > ft_strlen(itoa))) // perc zero, num=0で0をput
	{
		if (info.show_sign)
		{
			ft_memset(&ret[idx], info.decimal_sign, 1);
			ft_memset(&ret[idx + 1], '0', numlen - ft_strlen(itoa));
			info.show_sign = false;
		}
		else
			ft_memset(&ret[idx], '0', numlen - ft_strlen(itoa));
		idx += numlen - ft_strlen(itoa);
	}
	if (numlen && info.show_sign)
	{
		ft_memcpy(&ret[idx], itoa,  1);
		ft_memcpy(&ret[idx + 1], itoa, ft_strlen(itoa));
	}
	else if (numlen)
		ft_memcpy(&ret[idx], itoa, ft_strlen(itoa));

	free(itoa);
	return (ret);
}
*/


/*
	if (num < 0)
		info.put_minus = false;

	itoa = ft_itoa(num);
	if (!itoa)
		return (NULL);
	numlen = maxsize(ft_strlen(itoa), (size_t)info.perc);
	if (num == 0 && info.dot)
		numlen = 0;
	size = maxsize(numlen, info.width);
	ret = (char *)ft_calloc(sizeof(char), size + 1);
	if (!ret)
		return (NULL);

	if ((size > numlen) && !info.zero_pad) // space
		ft_memset(ret, ' ', size);
	else if ((size > numlen) && info.zero_pad && num >= 0) // zero pad (zero & leftはNG)
		ft_memset(ret, '0', size);
	else if ((size > numlen) && info.zero_pad && num < 0)
	{
		ft_memset(ret, '-', 1);
		ft_memset(&ret[1], '0', info.width - numlen);
	}



	if (info.dot && info.perc == 0)
		info.is_null = true;
	if (info.dot)
		numlen = minsize(info.perc, ft_strlen(itoa));
	else
		numlen = ft_strlen(itoa);

	if ((info.sign || info.space) && num >= 0)
		numlen++;
	size = maxsize(info.width, numlen);
	ret = (char *)ft_calloc(sizeof(char), size + 1);
	if (!ret)
		return (NULL);
	idx = 0;
	if ((unsigned)info.width > numlen)
	{
		if (info.zero_pad && !info.perc && info.put_minus)
			ft_memset(&ret[0], '0', info.width - numlen);
		else if (info.zero_pad && !info.perc && !info.put_minus)
		{
			ft_memset(&ret[0], '-', 1);
			ft_memset(&ret[1], '0', info.width - numlen);
			info.put_minus = true;
		}
		else
			ft_memset(&ret[idx], ' ', size);
//			ft_memset(&ret[idx], ' ', info.width - numlen);
		if (!info.left)
			idx += info.width - numlen;
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
	if ((unsigned)info.perc > ft_strlen(itoa))
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
*/