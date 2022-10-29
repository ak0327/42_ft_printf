/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_printf_info.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 19:20:48 by takira            #+#    #+#             */
/*   Updated: 2022/10/28 19:20:50 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	init_print_info(t_printf_info *info)
{
	info->left = false;
	info->sign = false;
	info->space = false;
	info->prefix = false;
	info->zero_pad = false;
	info->dot = false;
	info->dot_only = false;
	info->is_pointer = false;
	info->width = 0;
	info->prec = 0;
	info->base = 10;
	info->capitals = 0;
	info->printsize = 0;
	info->strlen = 0;
	info->padlen = 0;
	info->preclen = 0;
	info->digits = "0123456789abcdef0123456789ABCDEF";
	info->head_chr = "";
}
