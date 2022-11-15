/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 12:03:20 by takira            #+#    #+#             */
/*   Updated: 2022/11/15 09:33:22 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <limits.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>

# define PASS 1
# define FAIL 0

typedef struct s_pritnf_info
{
	bool		flag_left;
	bool		flag_sign;
	bool		flag_space;
	bool		flag_prefix;
	bool		flag_zero_pad;
	bool		prec_dot;
	bool		prec_dot_only;
	bool		is_pointer;
	long long	width_size;
	long long	prec_size;
	int			num_base;
	int			num_capitals;
	size_t		num_padlen;
	size_t		num_preclen;
	char		*num_head_chr;
}				t_printf_info;

int		ft_putchar_fd(char c, int fd);
int		ft_putstr_fd(char *s, int fd);
int		ft_isdigit(int c);
int		ft_printf(const char *fmt, ...);

int		get_width(char *fmt, size_t *i, t_printf_info *info, va_list *p);
int		get_prec(char *fmt, size_t *i, t_printf_info *info, va_list *p);
int		valid_info4fmt(char c, t_printf_info *info);

ssize_t	print_c(char chr, t_printf_info info);
ssize_t	print_s(char *str, t_printf_info info);
ssize_t	print_percent(t_printf_info info);
ssize_t	print_signed(int num, t_printf_info *info);
ssize_t	print_hex(unsigned long u, t_printf_info *info, bool isupper);
ssize_t	print_unsigned(unsigned long u, t_printf_info info);

size_t	ft_strlen(const char *s);
size_t	minsize(size_t a, size_t b);
size_t	maxsize(size_t a, size_t b);

char	*ft_strchr(const char *s, int c);
void	get_flag(char *fmt, size_t *i, t_printf_info *info);

#endif
