/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 10:36:10 by takira            #+#    #+#             */
/*   Updated: 2022/10/20 12:50:44 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*dst_cpy;
	unsigned const char	*src_cpy;

	dst_cpy = (unsigned char *)dst;
	src_cpy = (unsigned const char *)src;
	if (dst < src)
		return (ft_memcpy(dst, src, len));
	else if (dst > src)
	{
		while (len--)
			dst_cpy[len] = src_cpy[len];
	}
	return (dst);
}
