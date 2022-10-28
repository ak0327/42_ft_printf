/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 10:41:38 by takira            #+#    #+#             */
/*   Updated: 2022/10/20 15:16:33 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	get_num_digits(long long num)
{
	int	num_digits;

	num_digits = 0;
	if (num == 0)
		return (1);
	while (num > 0)
	{
		num_digits += 1;
		num /= 10;
	}
	return (num_digits);
}

static void	set_params(long long *num, size_t *len, size_t *is_neg)
{
	*len = 0;
	*is_neg = 0;
	if (*num < 0)
	{
		*len += 1;
		*num *= (-1);
		*is_neg = 1;
	}
	*len += get_num_digits(*num);
}

char	*ft_itoa(long long num)
{
	char		*ret;
	size_t		itoa_len;
	size_t		is_negative;

	set_params(&num, &itoa_len, &is_negative);
	ret = (char *) malloc(sizeof(char) * (itoa_len + 1));
	if (ret == NULL)
		return (NULL);
	if (is_negative == 1)
		ret[0] = '-';
	ret[itoa_len] = '\0';
	while (itoa_len > is_negative)
	{
		ret[itoa_len - 1] = (char)(num % 10 + '0');
		num /= 10;
		itoa_len--;
	}
	return (ret);
}

static size_t	get_u_num_digits(unsigned int num)
{
	size_t	num_digits;

	num_digits = 0;
	if (num == 0)
		return (1);
	while (num > 0)
	{
		num_digits += 1;
		num /= 10;
	}
	return (num_digits);
}

char	*ft_utoa(unsigned int n)
{
	char	*ret;
	size_t	utoa_len;

	utoa_len = get_u_num_digits(n);
	ret = (char *) malloc(sizeof(char) * (utoa_len + 1));
	if (ret == NULL)
		return (NULL);
	ret[utoa_len] = '\0';
	while (utoa_len > 0)
	{
		ret[utoa_len - 1] = (char)(n % 10 + '0');
		n /= 10;
		utoa_len--;
	}
	return (ret);
}
