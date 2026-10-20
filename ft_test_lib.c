/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_test_lib.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhdili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 09:47:07 by hhdili            #+#    #+#             */
/*   Updated: 2026/10/20 09:54:30 by hhdili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ft_test_lib.c - Comprehensive libft tests comparing against libc
 * Compile: cc -Wall -Wextra -Werror ft_test_lib.c libft.a -o ft_test_lib
 * Or:      cc -g -fsanitize=address,undefined ft_test_lib.c libft.a
	-o ft_test_lib
 */

#include "libft.h"
#include <ctype.h>
#include <fcntl.h>
#include <limits.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

static int		g_tests = 0;
static int		g_passed = 0;
static int		g_failed = 0;

#define OK(cond, msg)                                         \
	do                                                        \
	{                                                         \
		g_tests++;                                            \
		if (cond)                                             \
			g_passed++;                                       \
		else                                                  \
		{                                                     \
			g_failed++;                                       \
			printf("  [FAIL] %s (line %d)\n", msg, __LINE__); \
		}                                                     \
	} while (0)

#define SECTION(name) printf("\n=== %s ===\n", name)

/* Fork-based crash isolation for NULL tests.
 * Returns 0 if returned normally, -1 if crashed (signal). */
static int	run_safely(void (*fn)(void))
{
	pid_t	pid;
	int		devnull;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		devnull = open("/dev/null", O_WRONLY);
		if (devnull >= 0)
		{
			dup2(devnull, 2);
			close(devnull);
		}
		fn();
		_exit(0);
	}
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
		return (-1);
	return (WEXITSTATUS(status));
}

/* =====================================================================
 * 1. IS FUNCTIONS
 * ===================================================================== */
static void	test_is_functions(void)
{
	char	msg[128];

	SECTION("ft_isalpha / ft_isdigit / ft_isalnum / ft_isascii / ft_isprint");
	for (int c = 0; c <= 255; c++)
	{
		snprintf(msg, sizeof(msg), "ft_isalpha(%d)", c);
		OK(!!ft_isalpha(c) == !!isalpha(c), msg);
		snprintf(msg, sizeof(msg), "ft_isdigit(%d)", c);
		OK(!!ft_isdigit(c) == !!isdigit(c), msg);
		snprintf(msg, sizeof(msg), "ft_isalnum(%d)", c);
		OK(!!ft_isalnum(c) == !!isalnum(c), msg);
		snprintf(msg, sizeof(msg), "ft_isascii(%d)", c);
		OK(!!ft_isascii(c) == !!isascii(c), msg);
		snprintf(msg, sizeof(msg), "ft_isprint(%d)", c);
		OK(!!ft_isprint(c) == !!isprint(c), msg);
	}
	OK(!!ft_isalpha(EOF) == !!isalpha(EOF), "ft_isalpha(EOF)");
	OK(!!ft_isdigit(EOF) == !!isdigit(EOF), "ft_isdigit(EOF)");
	OK(!!ft_isalnum(EOF) == !!isalnum(EOF), "ft_isalnum(EOF)");
	OK(!!ft_isascii(EOF) == !!isascii(EOF), "ft_isascii(EOF)");
	OK(!!ft_isprint(EOF) == !!isprint(EOF), "ft_isprint(EOF)");
}

/* =====================================================================
 * 2. TOUPPER / TOLOWER
 * ===================================================================== */
static void	test_toupper_tolower(void)
{
	char	msg[128];

	SECTION("ft_toupper / ft_tolower");
	for (int c = 0; c <= 255; c++)
	{
		snprintf(msg, sizeof(msg), "ft_toupper(%d)", c);
		OK(ft_toupper(c) == toupper(c), msg);
		snprintf(msg, sizeof(msg), "ft_tolower(%d)", c);
		OK(ft_tolower(c) == tolower(c), msg);
	}
	OK(ft_toupper(EOF) == toupper(EOF), "ft_toupper(EOF)");
	OK(ft_tolower(EOF) == tolower(EOF), "ft_tolower(EOF)");
}

/* =====================================================================
 * 3. STRLEN
 * ===================================================================== */
static void	test_strlen(void)
{
	char		buf[1000];
	const char	*samples[] = {"", "a", "ab", "abc", "hello",
			"The quick brown fox", "0123456789", "\t\n\v\f\r", "!@#$%^&*()",
			NULL};
	char		msg[128];

	SECTION("ft_strlen");
	OK(ft_strlen("") == 0, "ft_strlen(\"\")");
	OK(ft_strlen("a") == 1, "ft_strlen(\"a\")");
	OK(ft_strlen("hello") == 5, "ft_strlen(\"hello\")");
	OK(ft_strlen("hello world") == 11, "ft_strlen(\"hello world\")");
	OK(ft_strlen("a\0b") == 1, "ft_strlen stops at NUL");
	memset(buf, 'x', 999);
	buf[999] = '\0';
	OK(ft_strlen(buf) == 999, "ft_strlen 999 chars");
	for (int i = 0; samples[i]; i++)
	{
		snprintf(msg, sizeof(msg), "ft_strlen(\"%s\") vs strlen", samples[i]);
		OK(ft_strlen(samples[i]) == strlen(samples[i]), msg);
	}
}

/* =====================================================================
 * 4. MEMSET / BZERO
 * ===================================================================== */
static void	test_memset(void)
{
	char	a[100], b[100];
	size_t	zero;
	char	*ret;

	SECTION("ft_memset");
	for (int i = 0; i < 100; i++)
		a[i] = b[i] = (char)i;
	memset(a, 'x', 50);
	ft_memset(b, 'x', 50);
	OK(memcmp(a, b, 100) == 0, "ft_memset 50 bytes");
	memset(a, 0, 100);
	ft_memset(b, 0, 100);
	OK(memcmp(a, b, 100) == 0, "ft_memset 100 bytes zero");
	memset(a, 'y', 100);
	ft_memset(b, 'y', 100);
	{
		zero = 0;
		memset(a, 'z', zero);
		ft_memset(b, 'z', zero);
	}
	OK(memcmp(a, b, 100) == 0, "ft_memset size 0");
	ret = ft_memset(b, 'q', 10);
	OK(ret == b, "ft_memset returns dst");
	memset(a, 'A', 100);
	ft_memset(b, 'A', 100);
	memset(a, 'B', 1);
	ft_memset(b, 'B', 1);
	OK(memcmp(a, b, 100) == 0, "ft_memset size 1");
}

static void	test_bzero(void)
{
	char	a[100], b[100];
	size_t	zero;

	SECTION("ft_bzero");
	for (int i = 0; i < 100; i++)
		a[i] = b[i] = (char)i;
	bzero(a, 50);
	ft_bzero(b, 50);
	OK(memcmp(a, b, 100) == 0, "ft_bzero 50 bytes");
	bzero(a, 100);
	ft_bzero(b, 100);
	OK(memcmp(a, b, 100) == 0, "ft_bzero 100 bytes");
	{
		zero = 0;
		bzero(a, zero);
		ft_bzero(b, zero);
	}
	OK(memcmp(a, b, 100) == 0, "ft_bzero size 0");
}

/* =====================================================================
 * 5. MEMCPY / MEMMOVE
 * ===================================================================== */
static void	test_memcpy(void)
{
	char	a[100], b[100];
	size_t	zero;
	char	*ret;

	SECTION("ft_memcpy");
	for (int i = 0; i < 100; i++)
		a[i] = b[i] = (char)i;
	memcpy(a, "hello world", 12);
	ft_memcpy(b, "hello world", 12);
	OK(memcmp(a, b, 100) == 0, "ft_memcpy 12 bytes");
	memcpy(a, "x", 1);
	ft_memcpy(b, "x", 1);
	OK(memcmp(a, b, 100) == 0, "ft_memcpy 1 byte");
	{
		zero = 0;
		memcpy(a, "abc", zero);
		ft_memcpy(b, "abc", zero);
	}
	OK(memcmp(a, b, 100) == 0, "ft_memcpy size 0");
	ret = ft_memcpy(b, "test", 4);
	OK(ret == b, "ft_memcpy returns dst");
}

static void	test_memmove(void)
{
	char	a[100], b[100];
	size_t	zero;

	SECTION("ft_memmove");
	memset(a, 'A', 100);
	memset(b, 'A', 100);
	memmove(a + 10, a, 20);
	ft_memmove(b + 10, b, 20);
	OK(memcmp(a, b, 100) == 0, "ft_memmove forward overlap");
	memset(a, 'B', 100);
	memset(b, 'B', 100);
	memmove(a, a + 10, 20);
	ft_memmove(b, b + 10, 20);
	OK(memcmp(a, b, 100) == 0, "ft_memmove backward overlap");
	memset(a, 'C', 100);
	memset(b, 'C', 100);
	memmove(a + 50, a, 20);
	ft_memmove(b + 50, b, 20);
	OK(memcmp(a, b, 100) == 0, "ft_memmove no overlap");
	memset(a, 'D', 100);
	memset(b, 'D', 100);
	memmove(a, a, 20);
	ft_memmove(b, b, 20);
	OK(memcmp(a, b, 100) == 0, "ft_memmove same pointer");
	{
		zero = 0;
		memmove(a, a + 10, zero);
		ft_memmove(b, b + 10, zero);
	}
	OK(memcmp(a, b, 100) == 0, "ft_memmove size 0");
}

/* =====================================================================
 * 6. MEMCHR / MEMCMP
 * ===================================================================== */
static void	test_memchr(void)
{
	const char	*s = "hello world";

	SECTION("ft_memchr");
	OK(ft_memchr(s, 'o', 11) == memchr(s, 'o', 11), "ft_memchr 'o'");
	OK(ft_memchr(s, 'l', 11) == memchr(s, 'l', 11), "ft_memchr 'l'");
	OK(ft_memchr(s, 'z', 11) == memchr(s, 'z', 11), "ft_memchr 'z' not found");
	OK(ft_memchr(s, 'h', 11) == memchr(s, 'h', 11), "ft_memchr 'h' first");
	OK(ft_memchr(s, 'd', 11) == memchr(s, 'd', 11), "ft_memchr 'd' last");
	OK(ft_memchr(s, 'h', 0) == memchr(s, 'h', 0), "ft_memchr n=0");
	OK(ft_memchr(s, '\0', 11) == memchr(s, '\0', 11), "ft_memchr '\\0'");
	OK(ft_memchr(s, '\0', 12) == memchr(s, '\0', 12), "ft_memchr '\\0' n=12");
	OK(ft_memchr(s, 'h', 1) == memchr(s, 'h', 1), "ft_memchr n=1 found");
	OK(ft_memchr(s, 'e', 1) == memchr(s, 'e', 1), "ft_memchr n=1 not found");
}

static void	test_memcmp(void)
{
	const char	*pairs[][2] = {{"", ""}, {"a", "a"}, {"a", "b"}, {"b", "a"},
			{"hello", "hello"}, {"hello", "hellp"}, {"\xff\x00", "\xff\x01"},
			{NULL, NULL}};
	char		msg[128];
	int			r1;
	int			r2;

	SECTION("ft_memcmp");
	OK(ft_memcmp("abc", "abc", 3) == 0, "ft_memcmp equal");
	OK(ft_memcmp("abc", "abd", 3) < 0, "ft_memcmp less");
	OK(ft_memcmp("abd", "abc", 3) > 0, "ft_memcmp greater");
	OK(ft_memcmp("abc", "xyz", 0) == 0, "ft_memcmp n=0");
	OK(ft_memcmp("abc", "abc", 100) == 0, "ft_memcmp n>len");
	OK(ft_memcmp("\x00\x01", "\x00\x02", 2) < 0, "ft_memcmp binary");
	OK(ft_memcmp("\xff", "\x00", 1) > 0, "ft_memcmp unsigned char");
	for (int i = 0; pairs[i][0]; i++)
	{
		for (int n = 0; n <= 5; n++)
		{
			r1 = ft_memcmp(pairs[i][0], pairs[i][1], n);
			r2 = memcmp(pairs[i][0], pairs[i][1], n);
			snprintf(msg, sizeof(msg), "ft_memcmp pair %d n=%d", i, n);
			OK((r1 > 0) - (r1 < 0) == (r2 > 0) - (r2 < 0), msg);
		}
	}
}

/* =====================================================================
 * 7. STRLCPY / STRLCAT
 * ===================================================================== */
static size_t	ref_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	srclen;
	size_t	copylen;

	srclen = strlen(src);
	if (size > 0)
	{
		copylen = srclen < size - 1 ? srclen : size - 1;
		memcpy(dst, src, copylen);
		dst[copylen] = '\0';
	}
	return (srclen);
}

static size_t	ref_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dstlen;
	size_t	srclen;
	size_t	copylen;

	dstlen = 0;
	while (dstlen < size && dst[dstlen])
		dstlen++;
	srclen = strlen(src);
	if (dstlen == size)
		return (size + srclen);
	copylen = srclen < size - dstlen - 1 ? srclen : size - dstlen - 1;
	memcpy(dst + dstlen, src, copylen);
	dst[dstlen + copylen] = '\0';
	return (dstlen + srclen);
}

static void	test_strlcpy(void)
{
	char	a[20], b[20];

	SECTION("ft_strlcpy");
	size_t r1, r2;
	memset(a, 'X', 20);
	memset(b, 'X', 20);
	r1 = ref_strlcpy(a, "abc", 20);
	r2 = ft_strlcpy(b, "abc", 20);
	OK(r1 == r2 && memcmp(a, b, 20) == 0, "ft_strlcpy basic");
	memset(a, 'X', 20);
	memset(b, 'X', 20);
	r1 = ref_strlcpy(a, "abcdef", 4);
	r2 = ft_strlcpy(b, "abcdef", 4);
	OK(r1 == r2 && memcmp(a, b, 20) == 0, "ft_strlcpy truncation");
	memset(a, 'X', 20);
	memset(b, 'X', 20);
	r1 = ref_strlcpy(a, "abc", 0);
	r2 = ft_strlcpy(b, "abc", 0);
	OK(r1 == r2 && memcmp(a, b, 20) == 0, "ft_strlcpy size 0");
	memset(a, 'X', 20);
	memset(b, 'X', 20);
	r1 = ref_strlcpy(a, "", 20);
	r2 = ft_strlcpy(b, "", 20);
	OK(r1 == r2 && memcmp(a, b, 20) == 0, "ft_strlcpy empty src");
	memset(a, 'X', 20);
	memset(b, 'X', 20);
	r1 = ref_strlcpy(a, "abc", 1);
	r2 = ft_strlcpy(b, "abc", 1);
	OK(r1 == r2 && memcmp(a, b, 20) == 0, "ft_strlcpy size 1");
	memset(a, 'X', 20);
	memset(b, 'X', 20);
	r1 = ref_strlcpy(a, "abc", 4);
	r2 = ft_strlcpy(b, "abc", 4);
	OK(r1 == r2 && memcmp(a, b, 20) == 0, "ft_strlcpy exact fit");
}

static void	test_strlcat(void)
{
	char	a[20], b[20];

	SECTION("ft_strlcat");
	size_t r1, r2;
	memset(a, 0, 20);
	memset(b, 0, 20);
	strcpy(a, "abc");
	strcpy(b, "abc");
	r1 = ref_strlcat(a, "def", 20);
	r2 = ft_strlcat(b, "def", 20);
	OK(r1 == r2 && strcmp(a, b) == 0, "ft_strlcat basic");
	memset(a, 0, 20);
	memset(b, 0, 20);
	strcpy(a, "abc");
	strcpy(b, "abc");
	r1 = ref_strlcat(a, "def", 5);
	r2 = ft_strlcat(b, "def", 5);
	OK(r1 == r2 && strcmp(a, b) == 0, "ft_strlcat truncation");
	memset(a, 0, 20);
	memset(b, 0, 20);
	strcpy(a, "abc");
	strcpy(b, "abc");
	r1 = ref_strlcat(a, "def", 3);
	r2 = ft_strlcat(b, "def", 3);
	OK(r1 == r2 && strcmp(a, b) == 0, "ft_strlcat size==dstlen");
	memset(a, 0, 20);
	memset(b, 0, 20);
	strcpy(a, "abc");
	strcpy(b, "abc");
	r1 = ref_strlcat(a, "def", 0);
	r2 = ft_strlcat(b, "def", 0);
	OK(r1 == r2 && strcmp(a, b) == 0, "ft_strlcat size 0");
	memset(a, 0, 20);
	memset(b, 0, 20);
	r1 = ref_strlcat(a, "def", 20);
	r2 = ft_strlcat(b, "def", 20);
	OK(r1 == r2 && strcmp(a, b) == 0, "ft_strlcat empty dst");
	memset(a, 0, 20);
	memset(b, 0, 20);
	strcpy(a, "abc");
	strcpy(b, "abc");
	r1 = ref_strlcat(a, "", 20);
	r2 = ft_strlcat(b, "", 20);
	OK(r1 == r2 && strcmp(a, b) == 0, "ft_strlcat empty src");
}

/* =====================================================================
 * 8. STRCHR / STRRCHR
 * ===================================================================== */
static void	test_strchr(void)
{
	const char	*s = "hello world";

	SECTION("ft_strchr");
	OK(ft_strchr(s, 'o') == strchr(s, 'o'), "ft_strchr 'o'");
	OK(ft_strchr(s, 'l') == strchr(s, 'l'), "ft_strchr 'l'");
	OK(ft_strchr(s, 'z') == strchr(s, 'z'), "ft_strchr 'z' not found");
	OK(ft_strchr(s, 'h') == strchr(s, 'h'), "ft_strchr 'h' first");
	OK(ft_strchr(s, 'd') == strchr(s, 'd'), "ft_strchr 'd' last");
	OK(ft_strchr(s, '\0') == strchr(s, '\0'), "ft_strchr '\\0'");
	OK(ft_strchr("", '\0') == strchr("", '\0'), "ft_strchr empty '\\0'");
	OK(ft_strchr("", 'a') == strchr("", 'a'), "ft_strchr empty 'a'");
	OK(ft_strchr(s, 'H') == strchr(s, 'H'), "ft_strchr case sensitive");
	OK(ft_strchr(s, 0x6f) == strchr(s, 0x6f), "ft_strchr int 0x6f");
}

static void	test_strrchr(void)
{
	const char	*s = "hello world";

	SECTION("ft_strrchr");
	OK(ft_strrchr(s, 'o') == strrchr(s, 'o'), "ft_strrchr 'o'");
	OK(ft_strrchr(s, 'l') == strrchr(s, 'l'), "ft_strrchr 'l'");
	OK(ft_strrchr(s, 'z') == strrchr(s, 'z'), "ft_strrchr 'z' not found");
	OK(ft_strrchr(s, 'h') == strrchr(s, 'h'), "ft_strrchr 'h' first");
	OK(ft_strrchr(s, 'd') == strrchr(s, 'd'), "ft_strrchr 'd' last");
	OK(ft_strrchr(s, '\0') == strrchr(s, '\0'), "ft_strrchr '\\0'");
	OK(ft_strrchr("", '\0') == strrchr("", '\0'), "ft_strrchr empty '\\0'");
	OK(ft_strrchr("", 'a') == strrchr("", 'a'), "ft_strrchr empty 'a'");
	OK(ft_strrchr("aaaa", 'a') == strrchr("aaaa", 'a'), "ft_strrchr all same");
}

/* =====================================================================
 * 9. STRNCMP
 * ===================================================================== */
static void	test_strncmp(void)
{
	const char	*pairs[][2] = {{"", ""}, {"a", "a"}, {"a", "b"}, {"b", "a"},
			{"abc", "abcd"}, {"abcd", "abc"}, {"hello", "hello"}, {"hello",
			"hellp"}, {"\xff", "\x01"}, {NULL, NULL}};
	char		msg[128];
	int			r1;
	int			r2;

	SECTION("ft_strncmp");
	OK(ft_strncmp("abc", "abc", 3) == 0, "ft_strncmp equal");
	OK(ft_strncmp("abc", "abd", 3) < 0, "ft_strncmp less");
	OK(ft_strncmp("abd", "abc", 3) > 0, "ft_strncmp greater");
	OK(ft_strncmp("abc", "xyz", 0) == 0, "ft_strncmp n=0");
	OK(ft_strncmp("abc", "abd", 2) == 0, "ft_strncmp n<diff");
	OK(ft_strncmp("abc", "abc", 100) == 0, "ft_strncmp n>len");
	OK(ft_strncmp("", "", 5) == 0, "ft_strncmp empty");
	OK(ft_strncmp("a", "", 1) > 0, "ft_strncmp vs empty");
	OK(ft_strncmp("", "a", 1) < 0, "ft_strncmp empty vs");
	for (int i = 0; pairs[i][0]; i++)
	{
		for (int n = 0; n <= 6; n++)
		{
			r1 = ft_strncmp(pairs[i][0], pairs[i][1], n);
			r2 = strncmp(pairs[i][0], pairs[i][1], n);
			snprintf(msg, sizeof(msg), "ft_strncmp pair %d n=%d", i, n);
			OK((r1 > 0) - (r1 < 0) == (r2 > 0) - (r2 < 0), msg);
		}
	}
}

/* =====================================================================
 * 10. STRNSTR
 * ===================================================================== */
static void	test_strnstr(void)
{
	const char	*hay = "hello world hello";

	SECTION("ft_strnstr");
	OK(ft_strnstr(hay, "world", 20) == strnstr(hay, "world", 20),
		"ft_strnstr 'world'");
	OK(ft_strnstr(hay, "hello", 20) == strnstr(hay, "hello", 20),
		"ft_strnstr 'hello' first");
	OK(ft_strnstr(hay, "hello", 20) == hay, "ft_strnstr returns first");
	OK(ft_strnstr(hay, "xyz", 20) == strnstr(hay, "xyz", 20),
		"ft_strnstr not found");
	OK(ft_strnstr(hay, "", 20) == strnstr(hay, "", 20),
		"ft_strnstr empty needle");
	OK(ft_strnstr(hay, "", 0) == strnstr(hay, "", 0), "ft_strnstr empty n=0");
	OK(ft_strnstr(hay, "world", 5) == strnstr(hay, "world", 5),
		"ft_strnstr n too small");
	OK(ft_strnstr(hay, "world", 11) == strnstr(hay, "world", 11),
		"ft_strnstr n exact");
	OK(ft_strnstr(hay, "world", 10) == strnstr(hay, "world", 10),
		"ft_strnstr n one short");
	OK(ft_strnstr("", "", 0) == strnstr("", "", 0), "ft_strnstr empty both");
	OK(ft_strnstr("", "a", 5) == strnstr("", "a", 5), "ft_strnstr empty hay");
	OK(ft_strnstr(hay, "hello", 5) == strnstr(hay, "hello", 5),
		"ft_strnstr exact match");
	OK(ft_strnstr(hay, "hello", 4) == strnstr(hay, "hello", 4),
		"ft_strnstr short");
}

/* =====================================================================
 * 11. STRDUP
 * ===================================================================== */
static void	test_strdup(void)
{
	char	*d;

	SECTION("ft_strdup");
	d = ft_strdup("");
	OK(d && strcmp(d, "") == 0, "ft_strdup empty");
	free(d);
	d = ft_strdup("hello");
	OK(d && strcmp(d, "hello") == 0, "ft_strdup hello");
	OK(d != NULL && d != (char *)"hello", "ft_strdup returns new allocation");
	free(d);
	d = ft_strdup("a");
	OK(d && strcmp(d, "a") == 0, "ft_strdup single char");
	free(d);
	/* NULL: must not crash (may return NULL) */
	d = ft_strdup(NULL);
	OK(d == NULL, "ft_strdup(NULL) returns NULL");
	free(d);
}

/* =====================================================================
 * 12. SUBSTR
 * ===================================================================== */
static void	test_substr(void)
{
	char	*s;

	SECTION("ft_substr");
	s = ft_substr("hello world", 0, 5);
	OK(s && strcmp(s, "hello") == 0, "ft_substr start 0 len 5");
	free(s);
	s = ft_substr("hello world", 6, 5);
	OK(s && strcmp(s, "world") == 0, "ft_substr start 6 len 5");
	free(s);
	s = ft_substr("hello", 0, 100);
	OK(s && strcmp(s, "hello") == 0, "ft_substr len > remaining");
	free(s);
	s = ft_substr("hello", 10, 5);
	OK(s && strcmp(s, "") == 0, "ft_substr start past end");
	free(s);
	s = ft_substr("hello", 2, 0);
	OK(s && strcmp(s, "") == 0, "ft_substr len 0");
	free(s);
	s = ft_substr("", 0, 5);
	OK(s && strcmp(s, "") == 0, "ft_substr empty src");
	free(s);
	s = ft_substr("hello", 5, 5);
	OK(s && strcmp(s, "") == 0, "ft_substr start at NUL");
	free(s);
}

/* =====================================================================
 * 13. STRJOIN
 * ===================================================================== */
static void	test_strjoin(void)
{
	char	*s;

	SECTION("ft_strjoin");
	s = ft_strjoin("hello", " world");
	OK(s && strcmp(s, "hello world") == 0, "ft_strjoin basic");
	free(s);
	s = ft_strjoin("", "world");
	OK(s && strcmp(s, "world") == 0, "ft_strjoin empty s1");
	free(s);
	s = ft_strjoin("hello", "");
	OK(s && strcmp(s, "hello") == 0, "ft_strjoin empty s2");
	free(s);
	s = ft_strjoin("", "");
	OK(s && strcmp(s, "") == 0, "ft_strjoin both empty");
	free(s);
	s = ft_strjoin("a", "b");
	OK(s && strcmp(s, "ab") == 0, "ft_strjoin single chars");
	free(s);
}

/* =====================================================================
 * 14. STRTRIM
 * ===================================================================== */
static void	test_strtrim(void)
{
	char	*s;

	SECTION("ft_strtrim");
	s = ft_strtrim("  hello  ", " ");
	OK(s && strcmp(s, "hello") == 0, "ft_strtrim spaces");
	free(s);
	s = ft_strtrim("hello", " ");
	OK(s && strcmp(s, "hello") == 0, "ft_strtrim no trim");
	free(s);
	s = ft_strtrim("", " ");
	OK(s && strcmp(s, "") == 0, "ft_strtrim empty");
	free(s);
	s = ft_strtrim("   ", " ");
	OK(s && strcmp(s, "") == 0, "ft_strtrim all trimmed");
	free(s);
	s = ft_strtrim("xxhelloxx", "x");
	OK(s && strcmp(s, "hello") == 0, "ft_strtrim x");
	free(s);
	s = ft_strtrim("abcba", "ab");
	OK(s && strcmp(s, "c") == 0, "ft_strtrim multiple chars");
	free(s);
	s = ft_strtrim("hello", "");
	OK(s && strcmp(s, "hello") == 0, "ft_strtrim empty set");
	free(s);
	s = ft_strtrim("", "");
	OK(s && strcmp(s, "") == 0, "ft_strtrim empty both");
	free(s);
}

/* =====================================================================
 * 15. SPLIT
 * ===================================================================== */
static void	free_split(char **arr)
{
	if (!arr)
		return ;
	for (int i = 0; arr[i]; i++)
		free(arr[i]);
	free(arr);
}

static void	test_split(void)
{
	char	**arr;

	SECTION("ft_split");
	arr = ft_split("hello world foo", ' ');
	OK(arr && arr[0] && strcmp(arr[0], "hello") == 0, "ft_split word 0");
	OK(arr && arr[1] && strcmp(arr[1], "world") == 0, "ft_split word 1");
	OK(arr && arr[2] && strcmp(arr[2], "foo") == 0, "ft_split word 2");
	OK(arr && arr[3] == NULL, "ft_split NULL terminator");
	free_split(arr);
	arr = ft_split("", ' ');
	OK(arr && arr[0] == NULL, "ft_split empty string");
	free_split(arr);
	arr = ft_split("   ", ' ');
	OK(arr && arr[0] == NULL, "ft_split all delimiters");
	free_split(arr);
	arr = ft_split("  hello  world  ", ' ');
	OK(arr && arr[0] && strcmp(arr[0], "hello") == 0,
		"ft_split leading/trailing");
	OK(arr && arr[1] && strcmp(arr[1], "world") == 0, "ft_split word 1");
	OK(arr && arr[2] == NULL, "ft_split NULL terminator");
	free_split(arr);
	arr = ft_split("a", ' ');
	OK(arr && arr[0] && strcmp(arr[0], "a") == 0, "ft_split single char");
	OK(arr && arr[1] == NULL, "ft_split single NULL");
	free_split(arr);
	arr = ft_split("aaa", 'a');
	OK(arr && arr[0] == NULL, "ft_split all same as delim");
	free_split(arr);
	arr = ft_split("hello", '\0');
	OK(arr && arr[0] && strcmp(arr[0], "hello") == 0, "ft_split delim NUL");
	OK(arr && arr[1] == NULL, "ft_split delim NUL NULL");
	free_split(arr);
}

/* =====================================================================
 * 16. ITOA
 * ===================================================================== */
static void	test_itoa(void)
{
	char	*s;
	char	expected[32];
	char	msg[64];

	SECTION("ft_itoa");
	s = ft_itoa(0);
	OK(s && strcmp(s, "0") == 0, "ft_itoa(0)");
	free(s);
	s = ft_itoa(1);
	OK(s && strcmp(s, "1") == 0, "ft_itoa(1)");
	free(s);
	s = ft_itoa(-1);
	OK(s && strcmp(s, "-1") == 0, "ft_itoa(-1)");
	free(s);
	s = ft_itoa(42);
	OK(s && strcmp(s, "42") == 0, "ft_itoa(42)");
	free(s);
	s = ft_itoa(-42);
	OK(s && strcmp(s, "-42") == 0, "ft_itoa(-42)");
	free(s);
	s = ft_itoa(123456789);
	OK(s && strcmp(s, "123456789") == 0, "ft_itoa(123456789)");
	free(s);
	s = ft_itoa(INT_MAX);
	OK(s && strcmp(s, "2147483647") == 0, "ft_itoa(INT_MAX)");
	free(s);
	s = ft_itoa(INT_MIN);
	OK(s && strcmp(s, "-2147483648") == 0, "ft_itoa(INT_MIN)");
	free(s);
	/* Cross-check with snprintf for a range */
	for (int v = -1000; v <= 1000; v += 7)
	{
		snprintf(expected, sizeof(expected), "%d", v);
		s = ft_itoa(v);
		snprintf(msg, sizeof(msg), "ft_itoa(%d)", v);
		OK(s && strcmp(s, expected) == 0, msg);
		free(s);
	}
}

/* =====================================================================
 * 17. PUT*_FD  (redirect stdout to a pipe and read back)
 * ===================================================================== */
static char	*capture_fd1(void (*fn)(void))
{
	int		pipefd[2];
	int		saved;
	char	*buf;
	ssize_t	n;

	if (pipe(pipefd) < 0)
		return (NULL);
	saved = dup(1);
	dup2(pipefd[1], 1);
	close(pipefd[1]);
	fn();
	fflush(stdout);
	dup2(saved, 1);
	close(saved);
	buf = malloc(4096);
	n = read(pipefd[0], buf, 4095);
	if (n < 0)
		n = 0;
	buf[n] = '\0';
	close(pipefd[0]);
	return (buf);
}

static void	put_char_helper(void)
{
	ft_putchar_fd('X', 1);
}
static void	put_str_helper(void)
{
	ft_putstr_fd("hello", 1);
}
static void	put_endl_helper(void)
{
	ft_putendl_fd("hello", 1);
}
static void	put_nbr_helper(void)
{
	ft_putnbr_fd(42, 1);
}
static void	put_nbr_neg_helper(void)
{
	ft_putnbr_fd(-42, 1);
}
static void	put_nbr_intmin_helper(void)
{
	ft_putnbr_fd(INT_MIN, 1);
}
static void	put_nbr_zero_helper(void)
{
	ft_putnbr_fd(0, 1);
}

static void	test_put_fd(void)
{
	char	*out;
	int		pipefd[2];
	int		saved;
	char	buf[16];
	ssize_t	n;

	SECTION("ft_putchar_fd / ft_putstr_fd / ft_putendl_fd / ft_putnbr_fd");
	out = capture_fd1(put_char_helper);
	OK(out && strcmp(out, "X") == 0, "ft_putchar_fd('X')");
	free(out);
	out = capture_fd1(put_str_helper);
	OK(out && strcmp(out, "hello") == 0, "ft_putstr_fd(\"hello\")");
	free(out);
	out = capture_fd1(put_endl_helper);
	OK(out && strcmp(out, "hello\n") == 0, "ft_putendl_fd(\"hello\")");
	free(out);
	out = capture_fd1(put_nbr_helper);
	OK(out && strcmp(out, "42") == 0, "ft_putnbr_fd(42)");
	free(out);
	out = capture_fd1(put_nbr_neg_helper);
	OK(out && strcmp(out, "-42") == 0, "ft_putnbr_fd(-42)");
	free(out);
	out = capture_fd1(put_nbr_zero_helper);
	OK(out && strcmp(out, "0") == 0, "ft_putnbr_fd(0)");
	free(out);
	out = capture_fd1(put_nbr_intmin_helper);
	OK(out && strcmp(out, "-2147483648") == 0, "ft_putnbr_fd(INT_MIN)");
	free(out);
	/* putstr_fd with empty string */
	{
		pipe(pipefd);
		saved = dup(1);
		dup2(pipefd[1], 1);
		close(pipefd[1]);
		ft_putstr_fd("", 1);
		fflush(stdout);
		dup2(saved, 1);
		close(saved);
		n = read(pipefd[0], buf, 15);
		if (n < 0)
			n = 0;
		buf[n] = '\0';
		close(pipefd[0]);
		OK(strcmp(buf, "") == 0, "ft_putstr_fd(\"\")");
	}
}

/* =====================================================================
 * 18. LINKED LISTS
 * ===================================================================== */
static void	del_content(void *p)
{
	free(p);
}

static void	*dup_content(void *p)
{
	char	*s;
	char	*d;

	s = (char *)p;
	d = malloc(strlen(s) + 1);
	if (d)
		strcpy(d, s);
	return (d);
}

static void	iter_upper(void *p)
{
	char	*s;

	s = (char *)p;
	while (*s)
	{
		*s = toupper((unsigned char)*s);
		s++;
	}
}

static void	test_lstnew(void)
{
	t_list	*n;

	SECTION("ft_lstnew");
	n = ft_lstnew((void *)"hello");
	OK(n != NULL, "ft_lstnew non-NULL");
	OK(n && n->content == (void *)"hello", "ft_lstnew content set");
	OK(n && n->next == NULL, "ft_lstnew next NULL");
	free(n);
	n = ft_lstnew(NULL);
	OK(n != NULL, "ft_lstnew(NULL) non-NULL");
	OK(n && n->content == NULL, "ft_lstnew(NULL) content NULL");
	OK(n && n->next == NULL, "ft_lstnew(NULL) next NULL");
	free(n);
}

static void	test_lstadd_front(void)
{
	t_list	*head;
	t_list	*n1;
	t_list	*n2;

	SECTION("ft_lstadd_front");
	head = NULL;
	n1 = ft_lstnew((void *)"1");
	n2 = ft_lstnew((void *)"2");
	ft_lstadd_front(&head, n1);
	OK(head == n1, "ft_lstadd_front first");
	ft_lstadd_front(&head, n2);
	OK(head == n2, "ft_lstadd_front second");
	OK(head->next == n1, "ft_lstadd_front chain");
	OK(n1->next == NULL, "ft_lstadd_front tail");
	free(n1);
	free(n2);
}

static void	test_lstsize(void)
{
	t_list	*a;
	t_list	*b;
	t_list	*c;

	SECTION("ft_lstsize");
	OK(ft_lstsize(NULL) == 0, "ft_lstsize NULL");
	a = ft_lstnew((void *)"a");
	b = ft_lstnew((void *)"b");
	c = ft_lstnew((void *)"c");
	a->next = b;
	b->next = c;
	OK(ft_lstsize(a) == 3, "ft_lstsize 3");
	OK(ft_lstsize(b) == 2, "ft_lstsize 2");
	OK(ft_lstsize(c) == 1, "ft_lstsize 1");
	free(a);
	free(b);
	free(c);
}

static void	test_lstlast(void)
{
	t_list	*a;
	t_list	*b;
	t_list	*c;

	SECTION("ft_lstlast");
	OK(ft_lstlast(NULL) == NULL, "ft_lstlast NULL");
	a = ft_lstnew((void *)"a");
	b = ft_lstnew((void *)"b");
	c = ft_lstnew((void *)"c");
	a->next = b;
	b->next = c;
	OK(ft_lstlast(a) == c, "ft_lstlast 3 nodes");
	OK(ft_lstlast(c) == c, "ft_lstlast single");
	free(a);
	free(b);
	free(c);
}

static void	test_lstadd_back(void)
{
	t_list	*head;
	t_list	*n1;
	t_list	*n2;
	t_list	*n3;

	SECTION("ft_lstadd_back");
	head = NULL;
	n1 = ft_lstnew((void *)"1");
	n2 = ft_lstnew((void *)"2");
	n3 = ft_lstnew((void *)"3");
	ft_lstadd_back(&head, n1);
	OK(head == n1, "ft_lstadd_back empty list");
	ft_lstadd_back(&head, n2);
	ft_lstadd_back(&head, n3);
	OK(head == n1, "ft_lstadd_back head unchanged");
	OK(n1->next == n2, "ft_lstadd_back n1->n2");
	OK(n2->next == n3, "ft_lstadd_back n2->n3");
	OK(n3->next == NULL, "ft_lstadd_back tail");
	free(n1);
	free(n2);
	free(n3);
}

static void	test_lstdelone(void)
{
	char	*s;
	t_list	*n;
	t_list	*n2;

	SECTION("ft_lstdelone");
	s = malloc(8);
	strcpy(s, "hello");
	n = ft_lstnew(s);
	ft_lstdelone(n, del_content);
	OK(1, "ft_lstdelone no crash");
	/* NULL content */
	n2 = ft_lstnew(NULL);
	ft_lstdelone(n2, del_content);
	OK(1, "ft_lstdelone NULL content no crash");
}

static void	test_lstclear(void)
{
	t_list	*head;
	char	*s;

	SECTION("ft_lstclear");
	head = NULL;
	for (int i = 0; i < 5; i++)
	{
		s = malloc(8);
		snprintf(s, 8, "n%d", i);
		ft_lstadd_back(&head, ft_lstnew(s));
	}
	ft_lstclear(&head, del_content);
	OK(head == NULL, "ft_lstclear sets head NULL");
	ft_lstclear(&head, del_content);
	OK(head == NULL, "ft_lstclear on NULL list");
}

static void	test_lstiter(void)
{
	t_list	*head;
	char	*s1;
	char	*s2;

	SECTION("ft_lstiter");
	head = NULL;
	s1 = strdup("abc");
	s2 = strdup("def");
	ft_lstadd_back(&head, ft_lstnew(s1));
	ft_lstadd_back(&head, ft_lstnew(s2));
	ft_lstiter(head, iter_upper);
	OK(strcmp(s1, "ABC") == 0, "ft_lstiter node 1");
	OK(strcmp(s2, "DEF") == 0, "ft_lstiter node 2");
	ft_lstclear(&head, del_content);
	OK(head == NULL, "ft_lstiter cleanup");
}

static void	test_lstmap(void)
{
	t_list	*head;
	t_list	*mapped;
	t_list	*empty_map;

	SECTION("ft_lstmap");
	head = NULL;
	ft_lstadd_back(&head, ft_lstnew(strdup("abc")));
	ft_lstadd_back(&head, ft_lstnew(strdup("def")));
	mapped = ft_lstmap(head, dup_content, del_content);
	OK(mapped != NULL, "ft_lstmap non-NULL");
	OK(mapped && strcmp((char *)mapped->content, "abc") == 0,
		"ft_lstmap node 1");
	OK(mapped && mapped->next && strcmp((char *)mapped->next->content,
			"def") == 0, "ft_lstmap node 2");
	OK(mapped && mapped->next && mapped->next->next == NULL, "ft_lstmap tail");
	/* Verify it's a deep copy */
	OK(mapped && mapped->content != head->content, "ft_lstmap deep copy");
	ft_lstclear(&mapped, del_content);
	ft_lstclear(&head, del_content);
	OK(mapped == NULL && head == NULL, "ft_lstmap cleanup");
	/* Empty list */
	empty_map = ft_lstmap(NULL, dup_content, del_content);
	OK(empty_map == NULL, "ft_lstmap(NULL)");
}

/* =====================================================================
 * 19. NULL INPUT SAFETY (forked so crashes don't kill the runner)
 * ===================================================================== */

static void	null_strdup(void)
{
	free(ft_strdup(NULL));
}
static void	null_substr(void)
{
	free(ft_substr(NULL, 0, 1));
}
static void	null_strjoin1(void)
{
	free(ft_strjoin(NULL, "a"));
}
static void	null_strjoin2(void)
{
	free(ft_strjoin("a", NULL));
}
static void	null_strtrim1(void)
{
	free(ft_strtrim(NULL, " "));
}
static void	null_strtrim2(void)
{
	free(ft_strtrim("a", NULL));
}
static void	null_split(void)
{
	char	**r;

	r = ft_split(NULL, ' ');
	free_split(r);
}
static void	test_null_safety(void)
{
	SECTION("NULL input safety (allocation functions only)");
	OK(run_safely(null_strdup) == 0, "ft_strdup(NULL) doesn't crash");
	OK(run_safely(null_substr) == 0, "ft_substr(NULL) doesn't crash");
	OK(run_safely(null_strjoin1) == 0, "ft_strjoin(NULL, x) doesn't crash");
	OK(run_safely(null_strjoin2) == 0, "ft_strjoin(x, NULL) doesn't crash");
	OK(run_safely(null_strtrim1) == 0, "ft_strtrim(NULL, x) doesn't crash");
	OK(run_safely(null_strtrim2) == 0, "ft_strtrim(x, NULL) doesn't crash");
	OK(run_safely(null_split) == 0, "ft_split(NULL) doesn't crash");
}

/* =====================================================================
 * MAIN
 * ===================================================================== */
int	main(void)
{
	printf("========== LIBFT TEST SUITE ==========\n");
	test_is_functions();
	test_toupper_tolower();
	test_strlen();
	test_memset();
	test_bzero();
	test_memcpy();
	test_memmove();
	test_memchr();
	test_memcmp();
	test_strlcpy();
	test_strlcat();
	test_strchr();
	test_strrchr();
	test_strncmp();
	test_strnstr();
	test_strdup();
	test_substr();
	test_strjoin();
	test_strtrim();
	test_split();
	test_itoa();
	test_put_fd();
	test_lstnew();
	test_lstadd_front();
	test_lstsize();
	test_lstlast();
	test_lstadd_back();
	test_lstdelone();
	test_lstclear();
	test_lstiter();
	test_lstmap();
	test_null_safety();
	printf("\n======================================\n");
	printf("Total:  %d\n", g_tests);
	printf("Passed: %d\n", g_passed);
	printf("Failed: %d\n", g_failed);
	printf("======================================\n");
	return (g_failed == 0 ? 0 : 1);
}
