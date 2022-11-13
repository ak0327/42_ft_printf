/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 10:37:09 by takira            #+#    #+#             */
/*   Updated: 2022/11/13 15:35:06 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr_fd(char *s, int fd)
{
	ssize_t	ret;

	ret = 0;
	if (s == NULL)
		return (0);
	while (*s)
	{
		ret += ft_putchar_fd(*s++, fd);
		if (ret > INT_MAX)
			return (-1);
	}
	return ((int)ret);
}
