/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongckim <yongckim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 17:35:21 by kankim            #+#    #+#             */
/*   Updated: 2021/05/30 20:59:48 by yongckim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_write(char *buf, int fd)
{
	write(fd, buf, ft_strlen(buf));
}

static int	count_size(char *start, char c)
{
	int cnt;

	cnt = 0;
	while (*start && *++start)
	{
		if (*(start - 1) != c && *start == c)
			++cnt;
		if (*start != c && *(start + 1) == 0)
			++cnt;
	}
	return (cnt);
}

static char	*locate_s(char *start, char *s, char c)
{
	if (start == s && *start != c)
		return (start);
	while (*start && *++start)
		if (*start != c && *(start - 1) == c)
			break ;
	return (start);
}

static char	*locate_e(char *end, char c)
{
	while (*end && *++end)
	{
		if (*end != c && *(end + 1) == 0)
			return (end + 1);
		if (*end == c && *(end - 1) != c)
			break ;
	}
	return (end);
}

void	*ft_calloc(size_t count, size_t size)
{
	void *ret;
	int i;
// static int cnt_alloc;
// cnt_alloc++;
	if (!(ret = malloc(count * size)))
		return (0);
	i = -1;
	while (++i < count * size)
		*(unsigned char *)(ret + i) = 0;
// printf("malloc cnt : %d, adress : %p\n", cnt_alloc, ret);
	return (ret);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	if (!src && !dst)
		return (0);
	while (n--)
		((unsigned char *)dst)[n] = ((const unsigned char *)src)[n];
	return (dst);
}

char		**ft_split(char const *s, char c)
{
	char	**ret;
	char	*start;
	char	*end;
	int		cnt;
	int		i;

	if (!s)
		return (0);
	cnt = count_size((char *)s, c);
	start = locate_s((char *)s, (char *)s, c);
	if (!(ret = (char **)ft_calloc(cnt + 1, sizeof(char *))))
		return (0);
	i = -1;
	while (++i < cnt)
	{
		end = locate_e(start, c);
		if (!(*(ret + i) = (char *)ft_calloc(end - start + 1, sizeof(char))))
			return (0);
		ft_memcpy(*(ret + i), start, end - start);
		start = locate_s(end, (char *)s, c);
	}
	return (ret);
}


void	ft_strtrim(char **str)
{
	char	*tmp;
	int		i;
	int		s;
	int		e;

	s = 0;
	while ((*str)[s] == ' ')
		++s;
	e = ft_strlen(*str) - 1;
	while ((*str)[e] == ' ')
		--e;
	tmp = (char *)ft_calloc(e - s + 2, sizeof(char));
	i = 0;
	while (s <= e)
		tmp[i++] = (*str)[s++];
	free(*str);
	*str = tmp;
}


char	*ft_strdup(const char *s1)
{
	char	*str;
	int		i;

	i = 0;
	if (!(str = (char *)ft_calloc(ft_strlen(s1) + 1, sizeof(char))))
		return (0);
	while (*s1)
	{
		*(str + i) = *s1++;
		++i;
	}
	return (str);
}

void	*ft_memmove(void *dest, const void *src, size_t count)
{
	size_t i;

	if (dest == src || count == 0)
		return (dest);
	i = -1;
	if (dest > src)
		ft_memcpy(dest, src, count);
	else
		while (++i < count)
			*(unsigned char *)(dest + i) = *(const unsigned char *)(src + i);
	return (dest);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	len;
	size_t	size;

	if (!dst || !src)
		return (0);
	len = ft_strlen(src);
	size = len < dstsize - 1 ? len : dstsize - 1;
	if (dstsize)
	{
		ft_memmove(dst, src, size);
		*(dst + size) = 0;
	}
	return (len);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ret;

	if (!s)
		return (0);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (!(ret = (char *)ft_calloc(len + 1, sizeof(char))))
		return (0);
	ft_strlcpy(ret, s + start, len + 1);
	return (ret);
}

int		ft_strncmp(const char *string1, const char *string2, size_t count)
{
	if (!count)
		return (0);
	while (--count && *string1 && *string1 == *string2)
	{
		++string1;
		++string2;
	}
	return (*(unsigned char *)string1 - *(unsigned char *)string2);
}

static int	count_num(long n)
{
	if (n < 10)
		return (1);
	return (count_num(n / 10) + 1);
}

static void	*sol(char *ret, long n, int idx)
{
	if (n < 10)
	{
		*(ret + idx) = n + '0';
		return (0);
	}
	sol(ret, n / 10, --idx);
	*(ret + idx + 1) = n % 10 + '0';
	return (0);
}

char		*ft_itoa(int n)
{
	char	*ret;
	int		len;
	int		sign;
	long	target;

	target = n;
	sign = 1;
	if (target < 0)
	{
		sign = -1;
		target *= -1;
	}
	len = count_num(target);
	if (sign == -1)
		++len;
	if (!(ret = (char *)ft_calloc(1, len + 1)))
		return (0);
	if (sign == -1)
		*ret = '-';
	sol(ret, target, len - 1);
	return (ret);
}

int			ft_atoi(const char *str)
{
	int	sign;
	int num;

	sign = 1;
	num = 0;
	while (*str && ft_isspace(*str))
		++str;
	sign = *str == '-' ? -1 : 1;
	if (*str == '+' || *str == '-')
		++str;
	while (*str && *str >= '0' && *str <= '9')
		num = num * 10 + *str++ - '0';
	return (sign * num);
}


int		ft_putchar(int c)
{
	return (write(1, &c, 1));
}

int		ft_isprint(char c)
{
	return (32 <= c && c <= 126);
}

