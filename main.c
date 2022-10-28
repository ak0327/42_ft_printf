/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 10:33:30 by takira            #+#    #+#             */
/*   Updated: 2022/10/24 10:33:44 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
#include <limits.h>
#include <string.h>


int main() {
	setvbuf(stdout, (char *)NULL, _IONBF, 0);

	int p1 = 0;
	char *p2 = "123";
	char *p3;
	long long p4 = LONG_MAX;
	char *p5 = NULL;
	char p6;

	ft_putstr_fd("\n##### ft_printf vs printf #####\n", 1);//    1     2   3    4     5
	ft_printf("[c] ft_printf: 1:%c, 2:%c, 3:%c, 4:%c, 5:%c [END]\n", 'a', 'A', '1', ' ', '\0');
	printf(       "    printf   : 1:%c, 2:%c, 3:%c, 4:%c, 5:%c [END]\n", 'a', 'A', '1', ' ', '\0');
	printf("\n");//                                                       1      2     3      4     5     6
	ft_printf("[s] ft_printf: 1:%s, 2:%s, 3:%s, 4:%s, 5:%s, 6:%s [END]\n", "aaa", "bb", "CCC", "4", "555", p5);
	printf(       "    printf   : 1:%s, 2:%s, 3:%s, 4:%s, 5:%s, 6:%s [END]\n", "aaa", "bb", "CCC", "4", "555", p5);
	printf("\n");//                                                       1    2    3    4    5     6
	ft_printf("[p] ft_printf: 1:%p, 2:%p, 3:%p, 4:%p, 5:%p, 6:%p [END]\n", &p1, &p2, &p3, &p4, &p5, &p6);
	printf(       "     printf  : 1:%p, 2:%p, 3:%p, 4:%p, 5:%p, 6:%p [END]\n", &p1, &p2, &p3, &p4, &p5, &p6);
	printf(       "     printflx: 1:  %lx, 2:  %lx, 3:  %lx, 4:  %lx, 5:  %lx, 6:  %lx [END]\n", (long)&p1, (long)&p2, (long)&p3, (long)&p4, (long)&p5, (long)&p6);

	printf("\n");//                                                       1    2    3   4   5          6
	ft_printf("[d] ft_printf: 1:%d, 2:%d, 3:%d, 4:%d, 5:%d, 6:%d, 7:%d, 8:%d, 9:%d [END]\n", 111, 222, -0, -1, INT_MAX, INT_MIN, 0b1010, 012, 0x7fffffff);
	printf(       "    printf   : 1:%d, 2:%d, 3:%d, 4:%d, 5:%d, 6:%d, 7:%d, 8:%d, 9:%d [END]\n", 111, 222, -0, -1, INT_MAX, INT_MIN, 0b1010, 012, 0x7fffffff);
	printf("\n");//                                                       1    2    3   4   5          6
	ft_printf("[i] ft_printf: 1:%i, 2:%i, 3:%i, 4:%i, 5:%i, 6:%i, 7:%i, 8:%i, 9:%i [END]\n", 111, 222, -0, -2, INT_MAX, INT_MIN, 0b1010, 012, 0x7fffffff);
	printf(       "    printf   : 1:%i, 2:%i, 3:%i, 4:%i, 5:%i, 6:%i, 7:%i, 8:%i, 9:%i [END]\n", 111, 222, -0, -2, INT_MAX, INT_MIN, 0b1010, 012, 0x7fffffff);
	printf("\n");//                                                       1    2    3   4   5          6
	ft_printf("[u] ft_printf: 1:%u, 2:%u, 3:%u, 4:%u, 5:%u, 6:%u [END]\n", 111, 222, -0, -1, INT_MAX, INT_MIN);
	printf(       "    printf   : 1:%u, 2:%u, 3:%u, 4:%u, 5:%u, 6:%u [END]\n", 111, 222, -0, -1, INT_MAX, INT_MIN);
	printf("\n");//                                                                         1  2  3   4    5      6      7    8         9
	ft_printf("[x] ft_printf: 1:%x, 2:%x, 3:%x, 4:%x, 5:%x, 6:%x, 7:%x, 8:%x, 9:%x [END]\n", -0, 1, 10, 100, 255, INT_MAX, -1, INT_MIN, (unsigned int)INT_MIN);
	printf(       "    printf   : 1:%x, 2:%x, 3:%x, 4:%x, 5:%x, 6:%x, 7:%x, 8:%x, 9:%x [END]\n", -0, 1, 10, 100, 255, INT_MAX, -1, INT_MIN, (unsigned int)INT_MIN);
	printf("\n");//                                                                         1  2  3   4    5      6      7    8         9
	ft_printf("[X] ft_printf: 1:%X, 2:%X, 3:%X, 4:%X, 5:%X, 6:%X, 7:%X, 8:%X, 9:%X [END]\n", -0, 1, 10, 100, 255, INT_MAX, -1, INT_MIN, (unsigned int)INT_MIN);
	printf(       "    printf   : 1:%X, 2:%X, 3:%X, 4:%X, 5:%X, 6:%X, 7:%X, 8:%X, 9:%X [END]\n", -0, 1, 10, 100, 255, INT_MAX, -1, INT_MIN, (unsigned int)INT_MIN);
	printf("\n");
	ft_printf("[%%] ft_printf: 1:%%, 2:%%, 3:%%%% [END]\n");
	printf(       "    printf   : 1:%%, 2:%%, 3:%%%% [END]\n"); // 奇数はコンパイルエラー
	printf("\n");//                                                                         d         i     p      s       u    x
	ft_printf("[all] ft_printf: abc[%d]efgh[%i]jklmno[%p]qr[%s]t[%u]vw[%x]yz%%%% [END]\n", INT_MAX, INT_MIN, &p1, "TEST%d", 111, 255);
	printf(       "      printf   : abc[%d]efgh[%i]jklmno[%p]qr[%s]t[%u]vw[%x]yz%%%% [END]\n", INT_MAX, INT_MIN, &p1, "TEST%d", 111, 255);
	printf("\n");//                                                                         d         i     p      s       u    x
	ft_printf("[flg] ft_printf: %------++++d [END]\n", 123);
	printf(       "      printf   : %------++++d [END]\n", 123);

	printf("\n\n\n");
	ft_printf("##### flg test #####\n");
/* c */
	ft_printf("[c]\n");
	char c_chr1 = 'f';
	//                                                                                                                                             1    2    3    4        5     6     7      8     9    10    11   12
	ft_printf(" ft_printf: 1:[%c], 2:[%5c], 3:[%-5c], 4:[%*c], 5:[%.c], 6:[%c], 7:[%c], 8:[%.c], 9:[%5c], 10:[%-5c], 11:[%5c], 12:[%-5c]\n", 'a', 'b', 'c', 10, 'd', 'e', c_chr1, '\0', '\0', '\0', '\0', 'a', 'a');
	printf(       " printf   : 1:[%c], 2:[%5c], 3:[%-5c], 4:[%*c], 5:[%.c], 6:[%c], 7:[%c], 8:[%.c], 9:[%5c], 10:[%-5c], 11:[%5c], 12:[%-5c]\n", 'a', 'b', 'c', 10, 'd', 'e', c_chr1, '\0', '\0', '\0', '\0', 'a', 'a');
	printf("\n");
	ft_printf(" ft_printf: 11:[%c], 12:[%c], 13:[%c], 14:[%c], 15:[%c]\n", 0, -0, 1, 300, 65);
	printf(       " printf   : 11:[%c], 12:[%c], 13:[%c], 14:[%c], 15:[%c]\n", 0, -0, 1, 300, 65);

	printf("\n");
	ft_printf(" ft_printf: 21:[%5c], 22:[%-2c], 23:[%-3c]\n", '0', '1', '2');
	printf(       " printf   : 21:[%5c], 22:[%-2c], 23:[%-3c]\n", '0', '1', '2');

	printf("\n\n");

/* s */
	ft_printf("[s]\n");
	char *s_str1 = "hoge";
	char *s_str2 = NULL;
	//                                                                                                                                             1       2     3          4      5      6            7        8        9      10    11
	ft_printf(" ft_printf: 1:[%s], 2:[%5s], 3:[%*s], 4:[%-10s], 5:[%10s], 6:[%.10s], 7:[%s], 8:[%s], 9:[%-2s], 10:[%10.5s], 11:[%10.s]\n", "abc", "def", 5, "ghi", "123%", "456", s_str1, (char *)NULL, s_str2, "ABC", "12345", "12345");
	printf(       " printf   : 1:[%s], 2:[%5s], 3:[%*s], 4:[%-10s], 5:[%10s], 6:[%.10s], 7:[%s], 8:[%s], 9:[%-2s], 10:[%10.5s], 11:[%10.s]\n", "abc", "def", 5, "ghi", "123%", "456", s_str1, (char *)NULL, s_str2, "ABC", "12345", "12345");
	printf("\n");
	ft_printf(" ft_printf: 11:[%-10.s], 12:[%-10.0s], 13:[%-10.1s], 14:[%-10.2s], 15:[%-10.3s], 16:[%-10.4s], 17:[%-10.5s], 18:[%-10.6s], 19:[%-10.7s], 20:[%-10.7s]\n", "hello", "hello", "hello", "hello", "hello", "hello", "hello", "hello", "hello", (char *)NULL);
	printf(       " printf   : 11:[%-10.s], 12:[%-10.0s], 13:[%-10.1s], 14:[%-10.2s], 15:[%-10.3s], 16:[%-10.4s], 17:[%-10.5s], 18:[%-10.6s], 19:[%-10.7s], 20:[%-10.7s]\n", "hello", "hello", "hello", "hello", "hello", "hello", "hello", "hello", "hello", (char *)NULL);
	printf("\n");
	ft_printf(" ft_printf: 21:[%10.s], 22:[%10.0s], 23:[%10.1s], 24:[%10.2s], 25:[%10.3s], 26:[%10.4s], 27:[%10.5s], 28:[%10.6s], 29:[%10.7s], 30:[%10.7s]\n", "hello", "hello", "hello", "hello", "hello", "hello", "hello", "hello", "hello", (char *)NULL);
	printf(       " printf   : 21:[%10.s], 22:[%10.0s], 23:[%10.1s], 24:[%10.2s], 25:[%10.3s], 26:[%10.4s], 27:[%10.5s], 28:[%10.6s], 29:[%10.7s], 30:[%10.7s]\n", "hello", "hello", "hello", "hello", "hello", "hello", "hello", "hello", "hello", (char *)NULL);
	printf("\n");
	ft_printf(" ft_printf: 31:[%10.s], 32:[%10.0s], 33:[%10.1s], 34:[%10.2s], 35:[%10.3s], 36:[%10.4s], 37:[%10.5s], 38:[%10.6s], 39:[%10.7s], 40:[%10.8s]\n", "abc\0de", "abc\0de", "abc\0de", "abc\0de", "abc\0de", "abc\0de", "abc\0de", "abc\0de", "abc\0de", "abc\0de");
	printf(       " printf   : 31:[%10.s], 32:[%10.0s], 33:[%10.1s], 34:[%10.2s], 35:[%10.3s], 36:[%10.4s], 37:[%10.5s], 38:[%10.6s], 39:[%10.7s], 40:[%10.8s]\n", "abc\0de", "abc\0de", "abc\0de", "abc\0de", "abc\0de", "abc\0de", "abc\0de", "abc\0de", "abc\0de", "abc\0de");
	printf("\n");
	ft_printf(" ft_printf: 41:[%-10.s], 42:[%-10.0s], 43:[%-10.1s], 44:[%-10.2s], 45:[%-10.3s], 46:[%-10.4s], 47:[%-10.5s], 48:[%-10.6s], 49:[%-10.7s], 50:[%-10.8s]\n", "abc\0de", "abc\0de", "abc\0de", "abc\0de", "abc\0de", "abc\0de", "abc\0de", "abc\0de", "abc\0de", "abc\0de");
	printf(       " printf   : 41:[%-10.s], 42:[%-10.0s], 43:[%-10.1s], 44:[%-10.2s], 45:[%-10.3s], 46:[%-10.4s], 47:[%-10.5s], 48:[%-10.6s], 49:[%-10.7s], 50:[%-10.8s]\n", "abc\0de", "abc\0de", "abc\0de", "abc\0de", "abc\0de", "abc\0de", "abc\0de", "abc\0de", "abc\0de", "abc\0de");
	printf("\n");
	//                                                     1              2
	ft_printf(" ft_printf: 51:[%-*.*s], 52:[%.*s]\n", -7, -3, "yolo", -3, "hello");
	printf(       " printf   : 51:[%-*.*s], 52:[%.*s]\n", -7, -3, "yolo", -3, "hello");
	printf("\n");
	//                                                    1                2
	ft_printf(" ft_printf: 61:[%*.*s], 62:[%.*s]\n", -7, -3, "yolo", -3, "hello");
	printf(       " printf   : 61:[%*.*s], 62:[%.*s]\n", -7, -3, "yolo", -3, "hello");
	printf("\n");

	ft_printf(" ft_printf: 63:[%*.*s], 64:[%.*s]\n", -7, UINT_MAX - 2, "yolo", UINT_MAX - 2, "hello");
	printf(       " printf   : 63:[%*.*s], 64:[%.*s]\n", -7, UINT_MAX - 2, "yolo", UINT_MAX - 2, "hello");
	printf("\n");

	ft_printf(" ft_printf: 63:[%*.*s], 64:[%.*s]\n", -7, UINT_MAX - 2, "yolo", UINT_MAX - 2, "hello");
	printf(       " printf   : 63:[%*.*s], 64:[%.*s]\n", -7, UINT_MAX - 2, "yolo", UINT_MAX - 2, "hello");
	printf("\n");


	//                                                    1                2
	ft_printf(" ft_printf: 71:[%*.*s], 72:[%.*s]\n", -7, 3, "yolo", 3, "hello");
	printf(       " printf   : 71:[%*.*s], 72:[%.*s]\n", -7, 3, "yolo", 3, "hello");
	printf("\n");
	ft_printf(" ft_printf: 81:[%-7.3s], 82:[%-.3s], 81:[%-7.s], 82:[%-.s], 81:[%-7.0s], 82:[%-.0s]\n", "yolo", "hello", "yolo", "hello", "yolo", "hello");
	printf(       " printf   : 81:[%-7.3s], 82:[%-.3s], 81:[%-7.s], 82:[%-.s], 81:[%-7.0s], 82:[%-.0s]\n", "yolo", "hello", "yolo", "hello", "yolo", "hello");

	printf("\n");
	ft_printf(" ft_printf: 81:[%10.8s]\n", "abcde");
	printf(       " printf   : 81:[%10.8s]\n", "abcde");

	//	ft_printf(" ft_printf: 41:[%2147483648s]\n", "abc");
//	printf(       " printf   : 41:[%2147483648s]\n", "abc");
	printf("\n\n");

/* p */
	ft_printf("[p]\n");
	int p_p1 = 0;
	int *p_p2 = &p_p1;
	int p_p3 = 100;
	char *p_p4 = "123";
	char p_c1 = 'a';
	char *p_p5 = &p_c1;
	//                                                                                              1  2      3       4       5         6     7
	ft_printf(" ft_printf: 1:[%p], 2:[%-5p], 3:[%*p], 4:[%15p], 5:[%*p], 6:[%p], 7:[%10p]\n", &p1, &p1, 0, &p1, &p_p2, 15, &p_p3, NULL, NULL);
	printf(       " printf   : 1:[%p], 2:[%-5p], 3:[%*p], 4:[%15p], 5:[%*p], 6:[%p], 7:[%10p]\n", &p1, &p1, 0, &p1, &p_p2, 15, &p_p3, NULL, NULL);
	printf("\n");
	ft_printf(" ft_printf: 11:[%-20p], 12:[%-20p], 13:[%-20p], 14:[%-20p], 15:[%-20p]\n", &p_p1, &p_p2, &p_p3, &p_p4, &p_p5, NULL);
	printf(       " printf   : 11:[%-20p], 12:[%-20p], 13:[%-20p], 14:[%-20p], 15:[%-20p]\n", &p_p1, &p_p2, &p_p3, &p_p4, &p_p5, NULL);
	printf("\n");
	ft_printf(" ft_printf: 21:[%20p], 22:[%20p], 23:[%20p], 24:[%20p], 25:[%20p]\n", &p_p1, &p_p2, &p_p3, &p_p4, &p_p5, NULL);
	printf(       " printf   : 21:[%20p], 22:[%20p], 23:[%20p], 24:[%20p], 25:[%20p]\n", &p_p1, &p_p2, &p_p3, &p_p4, &p_p5, NULL);

	printf("\n");
	ft_printf(" ft_printf: 31:[%.p], 32:[%*p], 33:[%p], 34:[%20p], 35:[%20p]\n", &p_p1, 0, &p_p2, &p_p3, &p_p4, &p_p5);
	printf(       " printf   : 31:[%.p], 32:[%*p], 33:[%p], 34:[%20p], 35:[%20p]\n", &p_p1, 0, &p_p2, &p_p3, &p_p4, &p_p5);
	printf("\n");
	//                                                                                                                            1        2          3                  4                   5                6                    7             8
	ft_printf(" ft_printf: 41:[%2p], 42:[%-2p], 43:[%-11p], 44:[%-12p], 45:[%-9p], 46:[%-8p], 47:[%-13p], 48:[%-14p]\n", (void *)-1, (void *)-1, (void *)INT_MIN, (void *)INT_MAX, (void *)LONG_MAX, (void *)LONG_MIN, (void *)ULONG_MAX, (void *)-ULONG_MAX);
	printf(       " printf   : 41:[%2p], 42:[%-2p], 43:[%-11p], 44:[%-12p], 45:[%-9p], 46:[%-8p], 47:[%-13p], 48:[%-14p]\n", (void *)-1, (void *)-1, (void *)INT_MIN, (void *)INT_MAX, (void *)LONG_MAX, (void *)LONG_MIN, (void *)ULONG_MAX, (void *)-ULONG_MAX);



	printf("\n\n");

/* d & i */
	ft_printf("[d & i]\n");
	ft_printf(" ft_printf: 1:[%d], 2:[%---d], 3:[% d], 4:[%+d], 5:[%010d], 6:[%10.5d], 7:[%.5d], 8:[%5.5d], 9:[% d], 10:[%d]\n", 123, 123, 123, 123, 123, 123, 123, 123, 0, -123);
	printf(       " printf   : 1:[%d], 2:[%---d], 3:[% d], 4:[%+d], 5:[%010d], 6:[%10.5d], 7:[%.5d], 8:[%5.5d], 9:[% d], 10:[%d]\n", 123, 123, 123, 123, 123, 123, 123, 123, 0, -123);
	printf("\n");
	//                                                                                                                                                    11        12       13     14     15   16   17   18    19   20
	ft_printf(" ft_printf: 11:[%d], 12:[%25d], 13:[%.25d], 14:[%25d], 15:[%010.1d], 16:[%10.d], 17:[%10.1d], 18:[%010.6d], 19:[%.6d], 20:[%06d]\n", 0X123, INT_MAX, INT_MIN, INT_MIN, 123, 123, 123, 123, -123, -123);
	printf(       " printf   : 11:[%d], 12:[%25d], 13:[%.25d], 14:[%25d], 15:[%010.1d], 16:[%10.d], 17:[%10.1d], 18:[%010.6d], 19:[%.6d], 20:[%06d]\n", 0X123, INT_MAX, INT_MIN, INT_MIN, 123, 123, 123, 123, -123, -123);

	printf("\n");
	//                                                                                                                                                    11        12       13     14     15   16   17   18    19   20
	ft_printf(" ft_printf: 21:[%-d], 22:[%-25d], 23:[%-.25d], 24:[%-25d], 25:[%-10.1d], 26:[%-10.d], 27:[%-10.1d], 28:[%-10.6d], 29:[%-.6d], 30:[%-6d]\n", 0X123, INT_MAX, INT_MIN, INT_MIN, 123, 123, 123, 123, -123, -123);
	printf(       " printf   : 21:[%-d], 22:[%-25d], 23:[%-.25d], 24:[%-25d], 25:[%-10.1d], 26:[%-10.d], 27:[%-10.1d], 28:[%-10.6d], 29:[%-.6d], 30:[%-6d]\n", 0X123, INT_MAX, INT_MIN, INT_MIN, 123, 123, 123, 123, -123, -123);
	printf("\n");
	//                                                                                                                                        31      32      33     34 35 36 37 47
	ft_printf(" ft_printf: 31:[%.*d], 32:[%0*d], 33:[%d], 34:[%5.0d], 35:[%.d], 36:[%.0d], 37:[%5.01d], 38:[%00*d], 39:[%d], 40:[%d]\n", -6, -3, -7, -54, 7 -54, 0, 0, 0, 0, -7, -54,  0,0);
	printf(       " printf   : 31:[%.*d], 32:[%0*d], 33:[%d], 34:[%5.0d], 35:[%.d], 36:[%.0d], 37:[%5.01d], 38:[%00*d], 39:[%d], 40:[%d]\n", -6, -3, -7, -54, 7 -54, 0, 0, 0, 0, -7, -54,   0,0);

	printf("\n");
	ft_printf(" ft_printf: 41:[%.01d], 42:[%.d]\n", 0, 0);
	printf(       " printf   : 41:[%.01d], 42:[%.d]\n", 0, 0);

//	printf("\n");
//	ft_printf(" ft_printf: 51:[%.01d], 52:[%.d], 53:[%30000000000000d], 54:[%.30000000000000d], 55:[%4294967284d], 56:[%.4294967284d]\n", 0, 0, 42, 42, 42, 42);
//	printf(       " printf   : 51:[%.01d], 52:[%.d], 53:[%30000000000000d], 54:[%.30000000000000d], 55:[%4294967284d], 56:[%.4294967284d]\n", 0, 0, 42, 42, 42, 42);

	printf("\n\n");

/* u */
	ft_printf("[u]\n");
	//                                                                                                                          1    2    3   4       5    6       7     8    9    10
	ft_printf(" ft_printf: 1:[%u], 2:[%-u], 3:[%5u], 4:[%05u], 5:[%*u], 6:[%.5u], 7:[%u], 8:[%u], 9:[%2u], 10:[%---u]\n", 123, 123, 123, 123, 5, 123, 123, UINT_MAX, -1, 123, 123);
	printf(       " printf   : 1:[%u], 2:[%-u], 3:[%5u], 4:[%05u], 5:[%*u], 6:[%.5u], 7:[%u], 8:[%u], 9:[%2u], 10:[%---u]\n", 123, 123, 123, 123, 5, 123, 123, UINT_MAX, -1, 123, 123);
	printf("\n");
	ft_printf(" ft_printf: 11:[%u], 12:[%.u], 13:[%05.u], 14:[%05u], 15:[%5.u], 16:[%10.5u], 17:[%-10.5u]\n", 0, 0, 0, 0, 0, 0, 0);
	printf(       " printf   : 11:[%u], 12:[%.u], 13:[%05.u], 14:[%05u], 15:[%5.u], 16:[%10.5u], 17:[%-10.5u]\n", 0, 0, 0, 0, 0, 0, 0);
	printf("\n");
	ft_printf(" ft_printf: 21:[%u], 22:[%.u], 23:[%05.u], 24:[%05u], 25:[%5.u], 26:[%10.5u], 27:[%-10.5u]\n", 123, 123, 123, 123, 123, 123, 123);
	printf(       " printf   : 21:[%u], 22:[%.u], 23:[%05.u], 24:[%05u], 25:[%5.u], 26:[%10.5u], 27:[%-10.5u]\n", 123, 123, 123, 123, 123, 123, 123);
	printf("\n\n");

/* x */
	ft_printf("[x]\n");
	//                                                                                                                                                                       1   2   3    4     5    6    7    8    9      10       11     12      13
	ft_printf(" ft_printf: 1:[%x], 2:[%#x], 3:[%5x], 4:[%05x], 5:[%05.1x], 6:[%20.20x], 7:[%5.20x], 8:[%#5.20x], 9:[%x], 10:[#5x], 11:[%#6x], 12:[%#6.5x], 13:[%#x]\n", 123, 123, 123, 123, 123, 123, 123, 123, 0x1234, 0x1234, 0x1234, 0X1234);
	printf(       " printf   : 1:[%x], 2:[%#x], 3:[%5x], 4:[%05x], 5:[%05.1x], 6:[%20.20x], 7:[%5.20x], 8:[%#5.20x], 9:[%x], 10:[#5x], 11:[%#6x], 12:[%#6.5x], 13:[%#x]\n", 123, 123, 123, 123, 123, 123, 123, 123, 0x1234, 0x1234, 0x1234, 0X1234);

	printf("\n");//                                                                                                                              1     2   3    4  5  6  7   8   9
	ft_printf(" ft_printf: 11:[%-20x], 12:[%-8.5x], 13:[%08.5x], 14:[%.x], 15:[%5.0x], 16:[%5.x], 17:[%#5.x], 18:[%#-8.5x], 19:[%08.5x]\n", 123 , 123, 123, 0, 0, 0, 0, 123, 0);
	printf(       " printf   : 11:[%-20x], 12:[%-8.5x], 13:[%08.5x], 14:[%.x], 15:[%5.0x], 16:[%5.x], 17:[%#5.x], 18:[%#-8.5x], 19:[%08.5x]\n", 123 , 123, 123, 0, 0, 0, 0, 123, 0);

	printf("\n");
	ft_printf(" ft_printf: 21:[%-2.7x], 22:[%-3.3x], 23:[%-3x], 24:[%3x], 25:[%x]\n", 3267, 6983, 0, 0, 0);
	printf(       " printf   : 21:[%-2.7x], 22:[%-3.3x], 23:[%-3x], 24:[%3x], 25:[%x]\n", 3267, 6983, 0, 0, 0);

	printf("\n");
	ft_printf(" ft_printf: 31:[%#x], 32:[%.50x], 33:[%.100x]\n", 0, 42, 42);
	printf(       " printf   : 31:[%#x], 32:[%.50x], 33:[%.100x]\n", 0, 42, 42);

	printf("\n\n");

//	ft_printf("[X]\n");
//	//                                                                                                                                                                       1   2   3    4     5    6    7    8    9      10       11     12      13
//	ft_printf(" ft_printf: 1:[%X], 2:[%#X], 3:[%5X], 4:[%05X], 5:[%05.1X], 6:[%20.20X], 7:[%5.20X], 8:[%#5.20X], 9:[%X], 10:[#5X], 11:[%#6X], 12:[%#6.5X], 13:[%#X]\n", 123, 123, 123, 123, 123, 123, 123, 123, 0x1234, 0x1234, 0x1234, 0X1234);
//	printf(       " printf   : 1:[%X], 2:[%#X], 3:[%5X], 4:[%05X], 5:[%05.1X], 6:[%20.20X], 7:[%5.20X], 8:[%#5.20X], 9:[%X], 10:[#5X], 11:[%#6X], 12:[%#6.5X], 13:[%#X]\n", 123, 123, 123, 123, 123, 123, 123, 123, 0x1234, 0x1234, 0x1234, 0X1234);
//	printf("\n\n");

/* % */
	ft_printf("[%%]\n");
	ft_printf(" ft_printf: 1:[%%], 2:[%0%], 3:[%5%], 4:[%05%], 5:[%-05%], 6:[%.5%], 7:[%.05%], 8:[%05.%], 9:[%05.10%], 10:[%05.010%], 11:[%5.010%], 12:[%5.10%], 13:[%+%], 14:[% %], 15:[%+ -05%], 16:[%+ 05%]\n");
	printf(       " printf   : 1:[%%], 2:[%0%], 3:[%5%], 4:[%05%], 5:[%-05%], 6:[%.5%], 7:[%.05%], 8:[%05.%], 9:[%05.10%], 10:[%05.010%], 11:[%5.010%], 12:[%5.10%], 13:[%+%], 14:[% %], 15:[%+ -05%], 16:[%+ 05%]\n");
	printf("\n\n");

/* other */
	ft_printf("[other]\n");

	ft_printf(" ft_printf: [•]\n");
	printf(       " printf   : [•]\n");



//	printf("\n");
//	printf("printf test\n");
//	printf(" 1   : %i, %d, %x\n", 1, 1, 1); // 1 1 1
//	printf(" 0xa : %i, %d, %x\n", 0xa, 0xa, 0xa);// 10 10 a¡
//	printf(" 0xff: %i, %d, %x, (int)%d, (int)d\n", 0xff, 0xff, 0xff, (int)0xff);// 255 255 ff 255
//	printf(" 0xffffffff: %i, %d, %x, (int)%d\n", 0xffffffff, 0xffffffff, 0xffffffff, (int)0xffffffff);// -1 -1 ffffffff -1
//	printf(" 0x7fffffff: %i, %d, %x, (int)%d\n", 0x7fffffff, 0x7fffffff, 0x7fffffff, (int)0x7fffffff);// INT_MAX, INT_MAX, 7fffffff, INT_MAX
//	printf(" 0b101: %i, %d, %x, (int)%d\n", 0b101, 0b101, 0b101, (int)0b101);// 5 5 5 5
//	printf(" 012: %i, %d, %x, (int)%d\n", 012, 012, 012, (int)012);// 10 10 a 10
//	// oct, hex, binも(int)キャストすればdになる
//
//	printf("%d\n", 0xff);

	/*
	ft_putstr_fd("\n---- original printf ----\n", 1);
	printf("[%%c]\n");

	printf("[%%s]\n");

	printf("[%%p]\n");
	int a = 10;
	char b = 'a';
	int *p = &a;
	void *c = NULL;
	printf("  p : a->%p, b->%p, c->%p, p->%p\n", &a, &b, c, p);
	printf("  lx: a->%lx, b->%lx, c->%lx, p->%lx\n", (long)&a, (long)&b, (long)c, (long)p);
	printf("  size : a->%zu, b->%zu, c->%zu, p->%zu\n", sizeof(&a), sizeof(&b), sizeof(c), sizeof(p));

	printf("[%%d]\n");
	printf("  0->%d, 1->%d, -1->%d\n", 0, 1, -1);
	printf("  INT_MAX->%d, INT_MIN->%d\n", INT_MAX, INT_MIN);
//	printf("\t\t(int)(INT_MAX+1)->%d, (int)(INT_MIN-1)->%d\n", (int)(INT_MAX+1), (int)(INT_MIN-1));
	printf("  UINT_MAX->%d\n", UINT_MAX);
	printf("  (int)LONG_MAX->%d, (int)LONG_MIN->%d\n", (int)LONG_MAX, (int)LONG_MIN);

	printf("[%%i]\n");
	printf("  0->%i, 1->%i, -1->%i\n", 0, 1, -1);
	printf("  INT_MAX->%i, INT_MIN->%i\n", INT_MAX, INT_MIN);
//	printf("\t\t(int)(INT_MAX+1)->%d, (int)(INT_MIN-1)->%d\n", (int)(INT_MAX+1), (int)(INT_MIN-1));
	printf("  UINT_MAX->%i\n", UINT_MAX);
	printf("  (int)LONG_MAX->%i, (int)LONG_MIN->%i\n", (int)LONG_MAX, (int)LONG_MIN);

	printf("[%%u]\n");
	printf("  0->%u, 1->%u, -1->%u, INT_MAX->%u, INT_MIN->%u\n", 0, 1, -1, (unsigned int)INT_MAX, (unsigned int)INT_MIN);

	printf("[%%x]\n");
	printf("  0->%x, 1->%x, -1->%x, (unsigned)-1->%x\n", 0, 1, -1, (unsigned int)-1);
	printf("  INT_MAX->%x, INT_MIN->%x, (unsigned)INT_MIN->%x\n", INT_MAX, INT_MIN, (unsigned int)INT_MIN); // LONGはlx

	printf("[%%X]\n");
	printf("  0->%X, 1->%X, -1->%X\n", 0, 1, -1);
	printf("  INT_MAX->%X, INT_MIN->%X\n", INT_MAX, INT_MIN); // LONGはlx


	printf("%%p test\n");
	printf("(char*)&a: %s\n", (char *)&a);
	printf("(char*)p: %s\n", (char*)p);

	char *abc = "abcde";
	printf("%%s  %s\n", abc);
	printf("abc %%p  %p\n", abc); // 0x100453f23 ... A 文字の先頭のアドレス
	printf("&abc[0] %%p %p\n", &abc[0]); // 0x100453f23 ... A
	printf("&abc %%p %p\n", &abc); // 0x16f9af578 ... B 変数のアドレス
	printf("(long)&abc %%lx %lx\n", (long)&abc); // 16f9af578 ... B
	printf("(long)&abc %%ld %ld\n", (long)&abc); // 6167393656(10) -> 16f9af578(16) ... B
	printf("(long long)&abc %%lld %lld\n", (long long)&abc); // 6167393656(10) -> 16f9af578(16) ... B
	printf("sizeof(&abc) %zu\n", sizeof(&abc)); // 8
	printf("sizeof((long)&abc) %zu\n", sizeof(&abc)); // 8
	printf("sizeof((long long)&abc) %zu\n", sizeof((long long)&abc)); // 8

	int p_a = 5;
	printf("sizeof(int) %zu\n", sizeof(int)); //
	printf("sizeof(long) %zu\n", sizeof(long)); //
	printf("sizeof(long) %zu\n", sizeof(long long)); //
	printf("sizeof(p_a) %zu\n", sizeof(p_a)); //
	printf("sizeof(&p_a) %zu\n", sizeof(&p_a)); //
	printf("sizeof((long)&p_a) %zu\n", sizeof((long)&p_a)); //
	printf("sizeof((long long)&p_a) %zu\n", sizeof((long long)&p_a)); //


	int x = 10;
	void *ptr1;
	ptr1 = &x;

	ft_putstr_fd((char*)ptr1, 1);
	*/

//	printf(" -1: signed->%d, (unsigned)->%u\n", -1, (unsigned int)-1);

	//	char *arg1 = "
//	int arg2 = 5;
//	int arg3 = INT_MIN;
//	char arg4 = 'a';
//	int arg5 = 0;

//	ft_printf("1:%s, 2:%d, 3:%d, 4:%c, 5:%d", arg1, arg2, arg3, arg4, arg5);
//	ft_printtf(arg_1, arg_2, arg_3, arg_4, arg_5);


/*
	printf("\n---- test ft_printf_str ----\n");
	char *str1 = "abc";
	ft_printf_str(">>>%s<<<", str1);

	printf("\n");

	char *str2 = "1234567890";
	ft_printf_str(">>> %s <<<", str2);

	printf("\n");

	char *str3 = "1234567890";
	ft_printf_str("% is not in this str!!", str3);

	printf("\n");

	char *str = NULL;
	printf("aaaaa%d%s\n", 0, str);
*/


//	char *arg1 = "abc";
//	int arg2 = 5;
//	char arg3 = 'c';
//
//	ft_printf_chr(arg1, arg2, arg3);


//	va_list	ptr = new char[sizeof(int) + sizeof(char) + sizeof(char*)];
//	char *a_ptr = ptr;
//
//	va_arg(a_ptr, int) = 100;
//	va_arg(a_ptr, char) = 'c';
//	va_arg(a_ptr, char*) = "hoge";
//
//	vprintf("%d %c %s\n", ptr);


//	char c = 'A';
//	ft_printf_chr("%c", c); // 'A'
//	printf("%c", c); // 'A'

/*
	printf("\n1. printf('abc') return: %d\n", printf("abc")); // 3
	printf("\n\n");
	printf("\n2. printf('123\\n') return: %d\n", printf("123\n")); // 4
	printf("\n\n");
	printf("\n3. printf('%%d', INT_MAX) return: %d\n", printf("%d", INT_MAX)); // 10
	printf("\n\n");
	printf("\n4. printf('%%d', INT_MIN) return: %d", printf("%d", INT_MIN)); // 11
	printf("\n\n");
	printf("\n5. printf('%%15d', INT_MIN) return: %d\n", printf("%15d", INT_MIN)); // 15
//	printf("5. printf(NULL), %d, printf: ", printf(NULL)); // segfault
*/
	return (0);
}


/*
void	test_func(char *arg_1, ...)
{
	va_list ptr;
	va_start(ptr, arg_1);
	printf("arg_2: %d\n", va_arg(ptr, int));
	printf("arg_3: %f\n", va_arg(ptr, double));
	// %d -> va_arg(ptr, int), %s -> va_arg(ptr, char*) を渡せば良い？

}
*/


/* printf_test */
/*
static void	putchar_and_increment_i_cnt(const char *arg, size_t *i, size_t *cnt) // func name...
{
	ft_putchar_fd(arg[*i], 1);
	*i += 1;
	*cnt += 1;
}

static void	putstr_and_increment_i_cnt(const char *arg, size_t *i, size_t *cnt) // func name...
{
	ft_putstr_fd((char *)arg, 1);
	*i += 2;
	*cnt += 2;
}

int	ft_printf_str(const char *arg1, const char *arg2)
{
	size_t	i;
	size_t	cnt;

	i = 0;
	cnt = 0;
	while (arg1[i] != '\0')
	{
		while (arg1[i] != '\0' && arg1[i] != '%')
			putchar_and_increment_i_cnt(arg1, &i, &cnt);
		if (arg1[i] != '\0' && arg1[i+1] == 's')
			putstr_and_increment_i_cnt(arg2, &i, &cnt);
		else if (arg1[i] != '\0')
			putchar_and_increment_i_cnt(arg1, &i, &cnt);
	}
	return ((int)cnt);
}
*/

//size_t	ptr_cnt(va_list ptr) // argをstrdupして%* の数を数える　終端不明のため。
//{
//	va_list	cpy;
//	size_t	cnt;
//
//	va_copy(cpy, ptr);
//	cnt = 0;
//	while (va_arg(cpy, int))
//		cnt++;
//	va_end(cpy);
//	return (cnt);
//}


/*
typedef struct s_print_types
{
	char	*name;
	void	*type;
}			t_print_types;
t_print_types	*type;
type = (t_print_types *)malloc(sizeof(t_print_types) * (ft_strlen(types) + 1));
size_t	k;
k = 0;
type[0].name = "c";
type[0].type = char*;
*/

/*
	// cnt test
	printf("count_types_in_fmt: %zu\n", cnt);
	while (i < cnt)
	{
		printf("No.%zu : %s\n", i+1, va_arg(ptr, char*));
		i++;
	}
*/
