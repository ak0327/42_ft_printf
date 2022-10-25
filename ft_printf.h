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

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <limits.h>
# include <stdarg.h>

typedef struct s_pritnf_info
{
	//flag
	unsigned	left; /* - flag */
	unsigned	sign; /* + flag */
	unsigned	space; /* space flag */
	unsigned	prefix; /* # flag */

	// width
	unsigned 	width; /* width */
	unsigned	zero_pad;

	//perc
	unsigned	perc;

	bool		put_minus;
}					t_printf_info;

void	ft_putstr_fd(char *s, int fd);
size_t	ft_strlen(const char *s);

char	*ft_itoa(int n);
char	*ft_uitoa(unsigned int n);
char	*ft_strchr(const char *s, int c);
void	*ft_memset(void *s, int c, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);

int	ft_isdigit(int c);
int ft_printf(const char *fmt, ...);

int	ft_putchar_fd(char c, int fd);
//int	ft_putstr_fd(char *s, int fd);
int	ft_putnbr_fd(int n, int fd);
int	ft_put_unsigned_nbr_fd(unsigned int n, int fd);

size_t	minsize(size_t a, size_t b);
size_t	maxsize(size_t a, size_t b);

#endif

//struct printf_info {
//	/* Mac OS X extensions */
//	void		*context;		/* User context pointer */
//	locale_t	loc;			/* Extended locale */
//	wchar_t		vsep;			/* Vector separator char */
//	/* one of ,:;_ flag or X by default */
//
//	/* GLIBC compatible */
//	int		prec;			/* precision */
//	int		width;			/* Width */
//	wchar_t		spec;			/* Format letter */
//	wchar_t		pad;			/* Padding char */
//	/* 0 if 0 flag set, otherwise space */
//
//	/* FreeBSD extensions */
//	wchar_t		signchar;		/* Sign char */
//
//	/* GLIBC compatible flags */
//	unsigned	is_long_double	:1;	/* L or ll flag */
//	unsigned	is_char		:1;	/* hh flag */
//	unsigned	is_short	:1;	/* h flag */
//	unsigned	is_long		:1;	/* l flag */
//	unsigned	alt		:1;	/* # flag */
//	unsigned	space		:1;	/* Space flag */
//	unsigned	left		:1;	/* - flag */
//	unsigned	showsign	:1;	/* + flag */
//	unsigned	group		:1;	/* ' flag */
//	unsigned	extra		:1;	/* For special use (currently unused) */
//	unsigned	wide		:1;	/* Nonzero for wide character streams (currently unused) */
//
//	/* FreeBSD flags */
//	unsigned	is_quad		:1;	/* q flag */
//	unsigned	is_intmax	:1;	/* j flag */
//	unsigned	is_ptrdiff	:1;	/* t flag */
//	unsigned	is_size		:1;	/* z flag */
//
//	/* Mac OS X flags */
//	unsigned	is_vec		:1;	/* v flag */
//
//	/* private */
//	int		sofar;
//	unsigned	get_width;
//	unsigned	get_prec;
//	const char	*begin;
//	const char	*end;
//	void 		*arg[__PRINTFMAXARG];
//};
