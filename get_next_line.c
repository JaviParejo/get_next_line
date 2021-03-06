/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jparejo- <jparejo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 16:33:59 by jparejo-          #+#    #+#             */
/*   Updated: 2021/12/14 19:14:46 by jparejo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	unsigned int	count;

	if (dstsize == 0)
		return (ft_strlen(src));
	count = 0;
	while (dstsize > 1 && *src)
	{
		*dst = *src;
		++dst;
		++src;
		--dstsize;
		++count;
	}
	*dst = '\0';
	while (*dst || *src)
	{
		if (*src)
		{
			++src;
			++count;
		}
	}
	return (count);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	d_len;
	size_t	s_len;
	size_t	count;
	size_t	limit;

	d_len = ft_strlen(dst);
	s_len = ft_strlen(src);
	if (dstsize <= d_len || dstsize == 0)
		return (dstsize + s_len);
	count = 0;
	limit = d_len;
	while (src[count] && count < (dstsize - d_len - 1))
	{
		dst[limit] = src[count];
		count++;
		limit++;
	}
	dst[limit] = '\0';
	return (d_len + s_len);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ret;
	size_t	len;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	ret = malloc(sizeof(char) * (len + 1));
	if (ret == NULL)
		return (NULL);
	ft_strlcpy(ret, s1, ft_strlen(s1) + 1);
	ft_strlcat(ret, s2, len + 1);
	free((char *)s1);
	return (ret);
}

char	*get_next_line(int fd)
{
	char	*buf;
	int		count;
	int 	n;
	static char	*mem;
	
	count = 1;
	n = 0;
	buf = malloc(sizeof(char) * 20);
	mem = malloc(sizeof(char) * 1);
	while(count > 0)
	{	
		count = read(fd, buf, 10);
		buf[count] = '\0';
		mem = ft_strjoin(mem, buf);
		while(n < count || mem[n] == '\n')
		{
			write(1, mem + n, 1);
			n++;
		}
	}
	// printf("%s", mem);
	free(mem);
	return (buf);
}

int		main(void)
{
	int		fd;
	char	*line;
	int		i;

	i = 0;
	fd = open("./data", O_RDONLY);
	while (i < 50)
	{
		line = (char *)malloc(sizeof(*line) * 1);
		get_next_line(fd);
		printf("|%s|\n", line);
		i++;
	}
}

// int 	main(void)
// {	
// 	int		fd;
// 	FILE *f;
// 	int c;
	
// 	f = fopen("./data", "r");
//    	c = getc(f);
// 	fd = open("./data", O_RDONLY);
// 	while (c != EOF)
// 		get_next_line(fd, 10);
// 	// fd = open("./data", O_RDONLY);
// 	// while (!feof(fd))
// 	// 	get_next_line(fd, 10);
// 	close(fd);
// 	// system("leaks a.out");
// }
