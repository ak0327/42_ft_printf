/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ret_string.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 16:17:23 by takira            #+#    #+#             */
/*   Updated: 2022/10/27 16:17:28 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_c(char chr, t_printf_info info)
{
	size_t	size;
	int		ret_bytes;

	ret_bytes = 0;
	size = maxsize(info.width, 1);
	if (size == 1 || info.left)
	{
		ret_bytes += ft_putchar_fd(chr, 1);
		size--;
	}
	while (size > !info.left)
	{
		ret_bytes += ft_putchar_fd(' ', 1);
		size--;
	}
	if (size)
		ret_bytes += ft_putchar_fd(chr, 1);
	return (ret_bytes);
}

int	print_s(char *str, t_printf_info info)
{
	char	*putstr;
	size_t	size;
	size_t	strlen;
	int 	ret_bytes;

	ret_bytes = 0;
	if (!str)
		str = "(null)";
	if (!info.dot)
		strlen = ft_strlen(str);
	else
		strlen = minsize(ft_strlen(str), info.perc);
	size = maxsize(info.width, strlen);
	putstr = (char *) ft_calloc(sizeof(char), size + 1);
	if (!putstr)
		return (-1);
	if (size > strlen)
		ft_memset(&putstr[0], ' ', size);
	ft_memcpy(&putstr[!info.left * (size - strlen)], str, strlen);
	ret_bytes += ft_putstr_fd(putstr, 1);
	free(putstr);
	return (ret_bytes);
}

int	print_percent(t_printf_info info)
{
	char	*putstr;
	size_t	size;
	int 	ret_bytes;

	ret_bytes = 0;
	if ((info.left || !info.width) && info.zero_pad)
		info.zero_pad = 0;
	size = maxsize(info.width, 1);
	putstr = (char *)ft_calloc(sizeof(char), size + 1);
	if (!putstr)
		return (-1);
	if (info.zero_pad)
		ft_memset(&putstr[0], '0', size);
	else
		ft_memset(&putstr[0], ' ', size);
	putstr[!info.left * (size - 1)] = '%';
	ret_bytes += ft_putstr_fd(putstr, 1);
	free(putstr);
	return (ret_bytes);
}

//char	*ret_c(char chr, t_printf_info info)
//{
//	char	*ret;
//	size_t	size;
//
//	size = maxsize(info.width, 1);
//	ret = (char *)ft_calloc(sizeof(char), size + 1);
//	if (!ret)
//		return (NULL);
//	if (size > 1)
//		ft_memset(&ret[0], ' ', size);
//	ret[!info.left * (size - 1)] = chr;
//	return (ret);
//}
//
//char	*ret_s(char *str, t_printf_info info)
//{
//	char	*ret;
//	size_t	size;
//	size_t	strlen;
//
//	if (!str)
//		str = "(null)";
//	if (!info.dot)
//		strlen = ft_strlen(str);
//	else
//		strlen = minsize(ft_strlen(str), info.perc);
//	size = maxsize(info.width, strlen);
//	ret = (char *) ft_calloc(sizeof(char), size + 1);
//	if (!ret)
//		return (NULL);
//	if (size > strlen)
//		ft_memset(&ret[0], ' ', size);
//	ft_memcpy(&ret[!info.left * (size - strlen)], str, strlen);
//	return (ret);
//}
//
//char	*ret_percent(t_printf_info info)
//{
//	char	*ret;
//	size_t	size;
//
//	if ((info.left || !info.width) && info.zero_pad)
//		info.zero_pad = 0;
//	size = maxsize(info.width, 1);
//	ret = (char *)ft_calloc(sizeof(char), size + 1);
//	if (!ret)
//		return (NULL);
//	if (info.zero_pad)
//		ft_memset(&ret[0], '0', size);
//	else
//		ft_memset(&ret[0], ' ', size);
//	ret[!info.left * (size - 1)] = '%';
//	return (ret);
//}
