#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFFER_SIZE 100
// # include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

char    *get_next_line(int fd);
char	*ft_strjoin(char const *s1, char const *s2);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	*ft_strchr(const char *str, int c);
void	*ft_calloc(size_t nmemb, size_t size);
size_t	ft_strlen(const char	*str);
void	*ft_memset(void *s, int c, size_t n);

#endif