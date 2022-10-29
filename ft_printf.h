/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 12:03:20 by takira            #+#    #+#             */
/*   Updated: 2022/10/24 12:03:21 by takira           ###   ########.fr       */
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

typedef struct s_pritnf_info
{
	bool	left;
	bool	sign;
	bool	space;
	bool	prefix;
	bool	zero_pad;
	bool	dot;
	bool	dot_only;
	bool	is_pointer;
	int		width;
	int		perc;
	int		base;
	int		capitals;
	char	*digits;
	char	*head_chr;
	size_t	printsize;
	size_t	strlen;
	size_t	padlen;
	size_t	perclen;
}					t_printf_info;

int		ft_putchar_fd(char c, int fd);
int		ft_putstr_fd(char *s, int fd); // change
int		ft_isdigit(int c);
int		ft_printf(const char *fmt, ...);
int		print_c(char chr, t_printf_info info);
int		print_s(char *str, t_printf_info info);
int		print_percent(t_printf_info info);
int		print_signed(long num, t_printf_info *info);
int		print_hexadecimal(unsigned long u, t_printf_info *info, bool isupper);
int		print_unsigned(unsigned long u, t_printf_info info);

size_t	ft_strlen(const char *s);
size_t	minsize(size_t a, size_t b);
size_t	maxsize(size_t a, size_t b);

char	*ft_strchr(const char *s, int c);

void	*ft_memset(void *s, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	init_print_info(t_printf_info *info);
void	input_flag(char *fmt, size_t *i, t_printf_info *info);

bool	input_width(char *fmt, size_t *i, t_printf_info *info, va_list *ptr);
bool	input_perc(char *fmt, size_t *i, t_printf_info *info, va_list *ptr);
bool	is_flag_valid(char c, t_printf_info *info);

#endif
