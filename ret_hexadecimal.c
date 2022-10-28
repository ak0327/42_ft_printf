/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ret_hexadecimal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 16:41:08 by takira            #+#    #+#             */
/*   Updated: 2022/10/27 16:41:09 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

//static int	get_hex_digit(unsigned long long n)
//{
//	int	ret;
//
//	ret = 0;
//	if (n == 0)
//		return (1);
//	while (n > 0)
//	{
//		n /= 16;
//		ret++;
//	}
//	return (ret);
//}
//
//static char	*dec2hex(unsigned int decnum, bool isupper)
//{
//	char			*hex;
//	const char		*hex_symbol = "0123456789abcdef0123456789ABCDEF";
//	size_t			hex_digit;
//	int 			capitals;
//
//	if (isupper)
//		capitals = 16;
//	else
//		capitals = 0;
//	hex_digit = get_hex_digit(decnum);
//	hex = (char *)ft_calloc(hex_digit + 1, sizeof(char));
//	if (hex == NULL)
//		return (NULL);
//	hex[hex_digit] = '\0';
//	while (hex_digit > 0)
//	{
//		hex[hex_digit - 1] = hex_symbol[decnum % 16 + capitals];
//		decnum /= 16;
//		hex_digit--;
//	}
//	return (hex);
//}
//
//static char	*dec2lx(long n)
//{
//	unsigned long	decnum;
//	char			*lhex;
//	const char		*hex_symbol = "0123456789abcdef";
//	size_t			hex_digit;
//
//	decnum = (unsigned long)n;
//	hex_digit = get_hex_digit(n);
//	lhex = (char *)ft_calloc(hex_digit + 1, sizeof(char));
//	if (lhex == NULL)
//		return (NULL);
//	lhex[hex_digit] = '\0';
//	while (hex_digit > 0)
//	{
//		lhex[hex_digit - 1] = hex_symbol[decnum % 16];
//		decnum /= 16;
//		hex_digit--;
//	}
//	return (lhex);
//}
//
//static char	*address2lx(long amp_p) // &pが入ってくる
//{
//	const size_t	size = sizeof(&amp_p);
//	char			*hex;
//	char			*lhex;
//
//	hex = dec2lx(amp_p);
//	if (!hex)
//		return (NULL);
//	lhex = (char *)ft_calloc(size + 3, sizeof(char));
//	if (!lhex)
//		return (NULL);
//	ft_memcpy(&lhex[0], "0x", 2);
//	ft_memcpy(&lhex[2], hex, size+1); // TODO +1? size=8byte
//	lhex[size + 3] = '\0';
//	free(hex);
//	return (lhex);
//}
//
//char	*ret_p(long amp_p, t_printf_info info)
//{
//	char	*ret;
//	char	*address;
//	size_t	size;
//
//
//	address = address2lx(amp_p);
//	if (!address)
//		return (NULL);
////	size = maxsize(info.width, ft_strlen(address));
//	size = sizeof(amp_p);
//	ret = (char *) ft_calloc(sizeof(char), size + 1);
//	if (!ret)
//	{
//		free(address);
//		return (NULL);
//	}
//	ft_memset(ret, ' ', size);
//	if (info.left)
//		ft_memcpy(&ret[0], address, ft_strlen(address));
//	else
//		ft_memcpy(&ret[size - ft_strlen(address)], address, ft_strlen(address));
//	free(address);
//	return (ret);
//}

//char	*ret_hex(unsigned int num, t_printf_info info, bool isupper)
//{
//	char			*ret;
//	char			*hex;
//	size_t			size;
//	size_t			hex_len;
//	size_t			idx;
//
//	if (info.dot && info.perc == 0 && num == 0)
//		info.is_null = true;
//	hex = dec2hex(num, isupper);
//	if (!hex)
//		return (NULL);
//	hex_len = info.prefix * 2 + maxsize(info.perc,ft_strlen(hex));
//	size = maxsize(info.width, hex_len);
//	if (info.is_null)
//		info.perc++;
////		size--; // hexlen >= 1, size >= 0
//	ret = (char *) ft_calloc(sizeof(char), size + 1);
//	if (!ret)
//	{
//		free(hex);
//		return (NULL);
//	}
//	idx = 0;
//	if ((unsigned)info.width > hex_len)
//	{
//		if (info.zero_pad && !info.perc && !info.left)
//			ft_memset(&ret[idx], '0', size);
//		else
//			ft_memset(&ret[idx], ' ', size);
//		if (!info.left)
//			idx += info.width - hex_len;
//	}
//	if (info.prefix && !info.is_null && num > 0)
//	{
//		if (isupper)
//			ft_memcpy(&ret[idx], "0X", 2);
//		else
//			ft_memcpy(&ret[idx], "0x", 2);
//		idx += 2;
//	}
//	if (((unsigned)info.perc > ft_strlen(hex)))
//	{
//		ft_memset(&ret[idx], '0', info.perc - ft_strlen(hex));
//		idx += info.perc - ft_strlen(hex);
//	}
//	if (!info.is_null)
//		ft_memcpy(&ret[idx], hex, ft_strlen(hex));
//	free(hex);
//	return (ret);
//}
